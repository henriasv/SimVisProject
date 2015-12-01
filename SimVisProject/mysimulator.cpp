#include "mysimulator.h"
#include <SimVis/TriangleCollection>
#include <SimVis/Spheres>
#include <QDebug>
#include <../voronoi-md-analysis/triangle.h>
#include <vector>
#include <QVector3D>

MySimulator::MySimulator()
{

}


bool MySimulator::nextStep() const
{
    return m_nextStep;
}

void MySimulator::setNextStep(bool nextStep)
{
    if (m_nextStep == nextStep)
        return;

    m_nextStep = nextStep;
    emit nextStepChanged(nextStep);
}

SimulatorWorker *MySimulator::createWorker()
{
    return new MyWorker();
}

void MyWorker::synchronizeSimulator(Simulator *simulator)
{
    MySimulator *mySimulator = qobject_cast<MySimulator*>(simulator);
    if(mySimulator) {
        m_nextstep = mySimulator->nextStep();
        m_newstep = mySimulator->newStep();
        mySimulator->setFrameMin(m_framemin);
        mySimulator->setFrameMax(m_framemax);
        mySimulator->setNextStep(false);
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    TriangleCollection* triangleCollection = qobject_cast<TriangleCollection*>(renderableObject);
    QVector3D displacement(140, 140, 75);
    if(triangleCollection) {
        triangleCollection->data.resize(vertices.size());
        triangleCollection->dirty = true;
        for(int i=0; i<vertices.size()/3; i++) {
            QVector3D &p1 = vertices[3*i+0];
            QVector3D &p2 = vertices[3*i+1];
            QVector3D &p3 = vertices[3*i+2];
            QVector3D normal = QVector3D::crossProduct((p1-p2), (p1-p3)).normalized();
            QVector3D color(1.0, 1.0, 1.0);
            for(int j=0; j<3; j++) {
                triangleCollection->data[3*i+j].vertex = vertices[3*i+j]-displacement;
                triangleCollection->data[3*i+j].color = color;
                triangleCollection->data[3*i+j].normal = normal;
            }
        }

    }
//    Spheres* spheres = qobject_cast<Spheres*>(renderableObject);
//    QVector3D displacement(140, 140, 75);
//    Spheres* spheres = qobject_cast<Spheres*>(renderableObject);
//    if(spheres) {
//        spheres->setPositions(m_positions);

//    }
}

void MyWorker::work()
{
    if (m_nextstep)
    {
        vertices.clear();
        std::cout << "In worker" << std::endl;
        timestep = m_newstep;
        if (timestep < 0)
        {
            std::cout << "Negative timestep, setting to 0" << std::endl;
            timestep = 0;
        }
        std::vector<Triangle> triangles = tracer.triangles(timestep);

        for (auto triangle : triangles)
        {
            for (int i = 0; i<3; i++)
            {
                vertices.push_back(QVector3D(triangle.vertices[i].x(), triangle.vertices[i].y(), triangle.vertices[i].z()));
            }
        }
        m_nextstep = false;
    }
}

MyWorker::MyWorker() {
    timestep = 0;
    std::string  filepath("/Users/henriksveinsson/molecular-simulations/lmp_Nthermalize=10000.0_Nerate=10000.0_temperature=260.0_crackRadius=20.0_Nproduction=40000.0_timeStep=10.0_Nx=24_Ny=24_Nz=12_crackHeight=6.0_maxStrain=1.1_seed=000/trajectory.lammpstrj");
    tracer.init(filepath);
    tracer.setParams(0.4, 0.4, 0.2, 100, 0.5);
    std::vector<Triangle> triangles = tracer.triangles(timestep);
    for (auto triangle : triangles)
    {
        for (int i = 0; i<3; i++)
        {
            vertices.push_back(QVector3D(triangle.vertices[i].x(), triangle.vertices[i].y(), triangle.vertices[i].z()));
        }
    }
    std::vector<int> frames = tracer.lammpsIO->availableFrames();
    m_framemin = *std::min_element(frames.begin(), frames.end());
    m_framemax = *std::max_element(frames.begin(), frames.end());
    m_nextstep = false;
}

