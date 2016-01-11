#include "analysisstep.h"


AnalysisStep::AnalysisStep(LammpsIO & reader, int timestep, double xfac, double yfac, double zfac, char element)
{
    LammpsFrame frame;
    reader.readFrame(frame, timestep);
    std::vector<vec3> positions = frame.getPositionsType(reader.elementCharToType(element));

    std::vector<Point> points;
    std::vector<double> myVertices = contractedBox(frame, xfac, yfac, zfac);
    std::vector<double> myVerticesViz = myVertices;
    myVerticesViz[0] += 3;
    myVerticesViz[1] -= 3;
    myVerticesViz[2] += 3;
    myVerticesViz[3] -= 3;
    myVerticesViz[4] += 3;
    myVerticesViz[5] -= 3;

    for (auto position : positions)
    {
        Point myPoint(position.x(), position.y(), position.z());
        if (inBox(myPoint, myVertices))
            points.push_back(myPoint);
    }

    Alpha_shape_3 as(points.begin(), points.end(), 30.0);
    std::cout << "Alpha shape completed." << std::endl;

    std::vector<Alpha_shape_3::Facet> facets;
    as.get_alpha_shape_facets(std::back_inserter(facets), Alpha_shape_3::REGULAR);
    std::cout << facets.size() << std::endl;

    for (auto p : facets)
    {
      auto myFacet = p;
      auto myCell = *std::get<0>(myFacet);
      int facetInd = std::get<1>(myFacet);

      bool isPlot = true;

      for (int i = 0; i<4; i++)
      {
          auto myVertex = *myCell.vertex(i);
          Point myPoint = myVertex.point();
          if (!inBox(myPoint, myVerticesViz))
          {
              isPlot = false;
          }
      }

      if (isPlot)
      {
          Triangle triangle;
          for (int i = 0; i<4; i++)
          {
              if (i != facetInd)
              {
                auto myVertex = *myCell.vertex(i);
                Point myPoint = myVertex.point();
                triangle.addVertex(QVector3D(myPoint.x(), myPoint.y(), myPoint.z()));
              }
          }
          if (triangle.valid())
          {
            this->addTriangle(triangle);
          }
          else
          {
              std::cout << "Invalid triangle was not inserted" << std::endl;
          }
      }
    }
    this->setBoundingBox(QVector3D(frame.xlo, frame.ylo, frame.zlo),
                              QVector3D(frame.xhi, frame.yhi, frame.zhi));
    this->setAnalysisBox(QVector3D(myVertices[0], myVertices[2], myVertices[4]),
                              QVector3D(myVertices[1], myVertices[3], myVertices[5]));
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
        area += triangle.area();
    }
    return area;
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

