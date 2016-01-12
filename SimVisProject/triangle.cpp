#include "triangle.h"
#include <math.h>
#include <iostream>

Triangle::Triangle()
{

}

bool Triangle::addVertex(QVector3D vertex)
{
    if (numVertices<3)
    {
        vertices[numVertices] = vertex;
        numVertices ++;
        return true;
    }
    else
    {
        return false;
    }
}

double Triangle::area()
{
    // Using Herons formula
    double asq = (vertices[2]-vertices[0]).lengthSquared();
    double bsq = (vertices[2]-vertices[1]).lengthSquared();
    double csq = (vertices[1]-vertices[0]).lengthSquared();
    double area = 0.25*sqrt(2*(asq*bsq + asq*csq + bsq*csq)
                     - (asq*asq + bsq*bsq + csq*csq));
    if (area != area)
    {
        std::cout << "Area is NaN" << std::endl;
    }
    return area;
}

bool Triangle::valid()
{
    return numVertices == 3;
}
