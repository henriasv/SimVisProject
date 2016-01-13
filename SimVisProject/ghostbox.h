#ifndef GHOSTBOX_H
#define GHOSTBOX_H

#include <QVector>
#include <QVector3D>

class GhostBox
{
public:
    GhostBox(double xlo, double xhi, double ylo, double yhi, double zlo, double zhi, double sxlo, double sxhi, double sylo, double syhi, double szlo, double szhi);
    double m_xlo, m_xhi, m_ylo, m_yhi, m_zlo, m_zhi;
    double m_sxlo, m_sxhi, m_sylo, m_syhi, m_szlo, m_szhi;
    QVector<QVector3D> m_particles;
    bool addParticle(QVector3D);

    int numParticles(){return m_particles.length();}
};

#endif // GHOSTBOX_H
