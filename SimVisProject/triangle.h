#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector3D>

class Triangle
{
public:
    Triangle();
    QVector3D vertices[3];
    bool addVertex(QVector3D);
    double area();
    bool valid();
private:
    int numVertices = 0;
};

#endif // TRIANGLE_H
