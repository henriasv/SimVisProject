#include "mysimulator.h"
#include <SimVis/TriangleCollection>
#include <SimVis/Spheres>
#include <QDebug>
#include <vector>
#include <QVector3D>
#include <QObject>
#include <list>


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
        m_rsq_threshold = mySimulator->rSqThreshold();
        m_skewfactor = mySimulator->skewFactor();
        m_framestep = mySimulator->frameStep();
        m_framemin = mySimulator->frameMin();
        m_framemax = mySimulator->frameMax();
        mySimulator->setFrameMin(m_framemin);
        mySimulator->setFrameMax(m_framemax);
        mySimulator->setNextStep(false);
        m_ispreload = mySimulator->isPreload();
        mySimulator->setIsPreload(false);
        m_isplotspheres = mySimulator->isPlotSpheres();
        m_isplottriangles = mySimulator->isPlotTriangles();
        m_xfac = mySimulator->xfac();
        m_yfac = mySimulator->yfac();
        m_zfac = mySimulator->zfac();
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
            QColor colorTmp;
            //colorTmp.setRe    dF(intensities[i]);
            //colorTmp.setGreenF(intensities[i]);
            //colorTmp.setBlueF(intensities[i]);
            //QVector3D color(colorTmp.redF(), colorTmp.greenF(), colorTmp.blueF());
            QVector3D color(0.5, 0.5, 0.5);
            for(int j=0; j<3; j++) {
                triangleCollection->data[3*i+j].vertex = vertices[3*i+j]-displacement;
                triangleCollection->data[3*i+j].color = color;
                triangleCollection->data[3*i+j].normal = normal;
            }
        }

    }

//  Spheres *qspheres = qobject_cast<Spheres*>(renderableObject);
//    if(qspheres) {
//        qspheres->positions().resize(spheres.size());
//        qspheres->colors().resize(spheres.size());
//        qspheres->scales().resize(spheres.size());
//        for(uint i=0; i<spheres.size(); i++) {
//            qspheres->positions()[i] = QVector3D(spheres[i].position.x(), spheres[i].position.y(), spheres[i].position.z())-displacement;
//            qspheres->colors()[i] = QColor("red");
//            qspheres->scales()[i] = 1.0;
//        }

//        qspheres->setDirty(true);
//    }
}

void MyWorker::work()
{
//    if (m_ispreload)
//    {
//        tracer.preload(m_framemin, m_framemax, m_framestep);
//    }

    if (m_nextstep)
    {
        vertices.clear();
        //spheres.clear();
        timestep = m_newstep;
        if (timestep < 0)
        {
            std::cout << "Negative timestep, setting to 0" << std::endl;
            timestep = 0;
        }

        if (m_isplottriangles)
        {
            if (stepData.count(timestep)>0)
            {
                AnalysisStep currentStep = stepData[timestep];
                for (Triangle & triangle : currentStep.triangleData)
                {
                    vertices.push_back(triangle.vertices[0]);
                    vertices.push_back(triangle.vertices[1]);
                    vertices.push_back(triangle.vertices[2]);
                }
            }
            else
            {
                AnalysisStep currentStep(*lammpsIO, timestep, m_xfac, m_yfac, m_zfac, 'O');
                stepData[timestep] = currentStep;
                for (Triangle & triangle : stepData[timestep].triangleData)
                {
                    vertices.push_back(triangle.vertices[0]);
                    vertices.push_back(triangle.vertices[1]);
                    vertices.push_back(triangle.vertices[2]);
                }
            }

        }
        std::cout << "Surface Area " << std::setprecision(6) <<  stepData[timestep].surfaceArea() << std::endl;
        m_nextstep = false;
    }
}

MyWorker::MyWorker() {
    std::string  filepath("/Users/henriksveinsson/molecular-simulations/lmp_Nthermalize=10000.0_Nerate=10000.0_temperature=260.0_crackRadius=20.0_Nproduction=40000.0_timeStep=10.0_Nx=24_Ny=24_Nz=12_crackHeight=6.0_maxStrain=1.1_seed=000/trajectory.lammpstrj");
    lammpsIO = new LammpsIO(filepath);
    std::vector<int> frames = lammpsIO->availableFrames();
    m_framemin = *std::min_element(frames.begin(), frames.end());
    m_framemax = *std::max_element(frames.begin(), frames.end());

    m_nextstep = false;
}


