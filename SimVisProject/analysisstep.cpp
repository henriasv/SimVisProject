#include "analysisstep.h"
#include "ghostbox.h"

AnalysisStep::AnalysisStep(LammpsIO & reader, int timestep, double xfac, double yfac, double zfac, char element)
{
    LammpsFrame frame;
    m_isValid = reader.readFrame(frame, timestep);
    std::vector<vec3> positions = frame.getPositionsType(reader.elementCharToType(element));


    std::vector<double> myVertices = contractedBox(frame, xfac, yfac, zfac);
    std::vector<double> myVerticesViz = myVertices;
    double periodicGhostWidth = 6.0; // Region of ghost particles to mimic periodic triangulation.
    myVerticesViz[0] -= periodicGhostWidth;
    myVerticesViz[1] += periodicGhostWidth;
    myVerticesViz[2] -= periodicGhostWidth;
    myVerticesViz[3] += periodicGhostWidth;
    myVerticesViz[4] -= periodicGhostWidth;
    myVerticesViz[5] += periodicGhostWidth;

    GhostBox myGhostBox(myVerticesViz[0], myVerticesViz[1], myVerticesViz[2], myVerticesViz[3], myVerticesViz[4], myVerticesViz[5], frame.xlo, frame.xhi, frame.ylo, frame.yhi, frame.zlo, frame.zhi);
    for (auto & position : positions)
    {
        myGhostBox.addParticle(QVector3D(position.x(), position.y(), position.z()));
    }

    std::vector<Point> points;
    for (auto & position : myGhostBox.m_particles)
    {
        Point myPoint(position.x(), position.y(), position.z());
        points.push_back(myPoint);
    }

    Alpha_shape_3 as(points.begin(), points.end(), 25.0);
    std::cout << "Alpha shape completed." << std::endl;

    std::vector<Alpha_shape_3::Facet> facets;
    as.get_alpha_shape_facets(std::back_inserter(facets), Alpha_shape_3::REGULAR);
    std::cout << facets.size() << std::endl;

    for (auto p : facets)
    {
      auto myFacet = p;
      auto myCell = *std::get<0>(myFacet);
      int facetInd = std::get<1>(myFacet);

      int isPlot = 0;

//      for (int i = 0; i<4; i++)
//      {
//          auto myVertex = *myCell.vertex(i);
//          Point myPoint = myVertex.point();
//          if (inBox(myPoint, myVertices))
//          {
//              isPlot ++;
//          }
//      }

      if (true)
      {
          Triangle triangle;
          for (int i = 0; i<4; i++)
          {
              if (i != facetInd)
              {
                auto myVertex = *myCell.vertex(i);
                Point myPoint = myVertex.point();
                if (inBox(myPoint, myVertices))
                {
                    isPlot ++;
                }
                triangle.addVertex(QVector3D(myPoint.x(), myPoint.y(), myPoint.z()));
              }
          }
          if (isPlot >= 2)
          {
              if (triangle.valid())
              {
                  this->addTriangle(triangle);
              }
              else
              {
                  qDebug() << QString("Invalid triangle was not inserted");
              }
          }

      }
    }
    this->setBoundingBox(QVector3D(frame.xlo, frame.ylo, frame.zlo),
                              QVector3D(frame.xhi, frame.yhi, frame.zhi));
    this->setAnalysisBox(QVector3D(myVerticesViz[0], myVerticesViz[2], myVerticesViz[4]),
                              QVector3D(myVerticesViz[1], myVerticesViz[3], myVerticesViz[5]));
}

void AnalysisStep::addTriangle(Triangle triangle)
{
    triangleData.push_back(triangle);
}

void AnalysisStep::setBoundingBox(QVector3D lo, QVector3D hi)
{
    boundingBoxLo = lo;
    boundingBoxHi = hi;
}

void AnalysisStep::setAnalysisBox(QVector3D lo, QVector3D hi)
{
    analysisBoxLo = lo;
    analysisBoxHi = hi;
}

double AnalysisStep::surfaceArea()
{
    double area = 0;
    for (Triangle & triangle : triangleData)
    {
        if (triangle.valid())
        {
            area += triangle.area();
        }
        else
        {
            qDebug() << QString("Invalid triangle in area calculation");
        }
    }
    return area;
}

bool AnalysisStep::isValid()
{
    return m_isValid;
}

bool AnalysisStep::inBox(const Point & inPoint, const std::vector<double> & vertices)
{
    return ((vertices[0] < inPoint.x()) && (inPoint.x() < vertices[1])
            && (vertices[2] < inPoint.y()) && (inPoint.y() < vertices[3])
            && (vertices[4] < inPoint.z()) && (inPoint.z() < vertices[5]));
}

std::vector<double> AnalysisStep::contractedBox(const LammpsFrame & frame, double xfac, double yfac, double zfac)
{
    double xdiff = frame.xhi - frame.xlo;
    double ydiff = frame.yhi - frame.ylo;
    double zdiff = frame.zhi - frame.zlo;

    const double xmin = frame.xlo + 0.5*(1-xfac)*xdiff;
    const double xmax = frame.xhi - 0.5*(1-xfac)*xdiff;
    const double ymin = frame.ylo + 0.5*(1-yfac)*ydiff;
    const double ymax = frame.yhi - 0.5*(1-yfac)*ydiff;
    const double zmin = frame.zlo + 0.5*(1-zfac)*zdiff;
    const double zmax = frame.zhi - 0.5*(1-zfac)*zdiff;

    std::vector<double> vertices;
    vertices.push_back(xmin);
    vertices.push_back(xmax);
    vertices.push_back(ymin);
    vertices.push_back(ymax);
    vertices.push_back(zmin);
    vertices.push_back(zmax);
    return vertices;
}

