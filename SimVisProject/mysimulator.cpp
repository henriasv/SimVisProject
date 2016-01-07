#include "mysimulator.h"
#include <SimVis/TriangleCollection>
#include <SimVis/Spheres>
#include <QDebug>
#include <vector>
#include <QVector3D>
#include <QObject>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Alpha_shape_3.h>
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
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    TriangleCollection* triangleCollection = qobject_cast<TriangleCollection*>(renderableObject);
    QVector3D displacement(75, 75, 75);
    if(triangleCollection) {
        //std::cout << "Synchronizing vertices" << std::endl;
        triangleCollection->data.resize(vertices.size());
        triangleCollection->dirty = true;
        for(int i=0; i<vertices.size()/3; i++) {
            QVector3D &p1 = vertices[3*i+0];
            QVector3D &p2 = vertices[3*i+1];
            QVector3D &p3 = vertices[3*i+2];
            QVector3D normal = QVector3D::crossProduct((p1-p2), (p1-p3)).normalized();
            QColor colorTmp;
            //colorTmp.setRedF(intensities[i]);
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

    Spheres *qspheres = qobject_cast<Spheres*>(renderableObject);
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

//    if (m_nextstep)
//    {
//        vertices.clear();
//        spheres.clear();
//        timestep = m_newstep;
//        if (timestep < 0)
//        {
//            std::cout << "Negative timestep, setting to 0" << std::endl;
//            timestep = 0;
//        }

//        if (m_isplottriangles)
//        {
//        std::vector<Triangle> triangles = tracer.triangles(timestep);
//        for (auto triangle : triangles)
//        {
//            if ((triangle.max_rsq>m_rsq_threshold) && (triangle.min_skew>m_skewfactor))
//            {
//                for (int i = 0; i<3; i++)
//                {
//                    vertices.push_back(QVector3D(triangle.vertices[i].x(), triangle.vertices[i].y(), triangle.vertices[i].z()));
//                }
//            }
//        }
//        }
//        if (m_isplotspheres)
//        {
//        std::vector<Sphere> tmpSpheres = tracer.spheres(timestep);
//        for (auto sphere : tmpSpheres)
//        {
//            if ((sphere.max_rsq>m_rsq_threshold) && (true))// (sphere.min_skew>m_skewfactor))
//            {
//                spheres.push_back(sphere);
//            }
//        }
//        }
//        m_nextstep = false;
//    }
}

MyWorker::MyWorker() {
    std::string  filepath("/media/henrik/IcyBox/phd_methane_hydrates/pennyshaped_cracks/systematic_mw_pennycracks-2016-01-05-194103/lmp_Nthermalize=2000.0_Nerate=10000.0_temperature=260.0_crackRadius=20.0_Nproduction=40000.0_timeStep=10.0_Nx=12_Ny=12_Nz=12_crackHeight=6.0_maxStrain=1.072_seed=000/trajectory.lammpstrj");
    lammpsIO = new LammpsIO(filepath);
    std::vector<int> frames = lammpsIO->availableFrames();
    m_framemin = *std::min_element(frames.begin(), frames.end());
    m_framemax = *std::max_element(frames.begin(), frames.end());


    LammpsFrame frame;
    lammpsIO->readFrame(frame, 25000);
    std::vector<vec3> positions = frame.getPositionsType(lammpsIO->elementCharToType('O'));



    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef CGAL::Alpha_shape_vertex_base_3<K>               Vb;
    typedef CGAL::Alpha_shape_cell_base_3<K>                 Fb;
    typedef CGAL::Triangulation_data_structure_3<Vb,Fb>      Tds;
    typedef CGAL::Delaunay_triangulation_3<K,Tds,CGAL::Fast_location>  Delaunay;
    typedef CGAL::Alpha_shape_3<Delaunay>                    Alpha_shape_3;
    typedef K::Point_3                                  Point;
    typedef Alpha_shape_3::Alpha_iterator               Alpha_iterator;
    typedef Alpha_shape_3::NT                           NT;

      Delaunay dt;

      for (auto position : positions)
      {
              dt.insert(Point(position.x(), position.y(), position.z()));
      }


      std::cout << "Delaunay computed." << std::endl;
      // compute alpha shape
      Alpha_shape_3 as(dt);
      std::cout << "Alpha shape computed in REGULARIZED mode by defaut."
            << std::endl;
       // find optimal alpha values
      Alpha_shape_3::NT alpha_solid = as.find_alpha_solid();
      Alpha_iterator opt = as.find_optimal_alpha(1);
      std::cout << "Smallest alpha value to get a solid through data points is "
            << alpha_solid << std::endl;
      std::cout << "Optimal alpha value to get one connected component is "
            <<  *opt    << std::endl;
      as.set_alpha(*opt);
      assert(as.number_of_solid_components() == 1);


    m_nextstep = false;
}

