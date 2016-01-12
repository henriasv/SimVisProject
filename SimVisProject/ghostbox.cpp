#include "ghostbox.h"

GhostBox::GhostBox()
{

}

void GhostBox::addParticle(QVector3D position)
{
    if (position.x()<xhi && position.x()>xlo && position.y()<yhi && position.y()>ylo && position.z()<zhi && position.z()>zlo)
    {
        particles.append(position);
        bool xUpMask = position.x()<(sxlo+xhi-sxhi);
        bool xDownMask = position.x()>(sxhi+xlo-sxlo);
        bool yUpMask = position.y()<(sylo+yhi-syhi);
        bool yDownMask = position.y()>(syhi+ylo-sylo);
        bool zUpMask = position.z()<(szlo+zhi-szhi);
        bool zDownMask = position.z()>(szhi+zlo-szlo);

        std::vector<int> options = {xUpMask-xDownMask, yUpMask-yDownMask, zUpMask-zDownMask};

    }
}
