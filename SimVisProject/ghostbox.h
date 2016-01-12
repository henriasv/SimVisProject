#ifndef GHOSTBOX_H
#define GHOSTBOX_H

#include <QVector>
#include <QVector3D>

class GhostBox
{
public:
    GhostBox();
    double xlo, xhi, ylo, yhi, zlo, zhi;
    double sxlo, sxhi, sylo, syhi, szlo, szhi;
    QVector<QVector3D> particles;
    void addParticle(QVector3D);

    int numParticles(){return particles.length();}
};

#endif // GHOSTBOX_H
