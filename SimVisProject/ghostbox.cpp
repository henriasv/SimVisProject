#include "ghostbox.h"
#include "iostream"
#include "QDebug"

GhostBox::GhostBox(double xlo, double xhi, double ylo, double yhi, double zlo, double zhi, double sxlo, double sxhi, double sylo, double syhi, double szlo, double szhi)
{
    m_xlo = xlo; m_xhi = xhi; m_ylo = ylo; m_yhi = yhi; m_zlo = zlo; m_zhi = zhi; m_sxlo = sxlo; m_sxhi = sxhi; m_sylo= sylo; m_syhi = syhi; m_szlo = szlo; m_szhi = szhi;
}

bool GhostBox::addParticle(QVector3D position)
{
    if (position.x()<m_sxhi && position.x()>m_sxlo && position.y()<m_syhi && position.y()>m_sylo && position.z()<m_szhi && position.z()>m_szlo)
    {
        m_particles.append(position);
        bool xUpMask = position.x()<(m_sxlo+m_xhi-m_sxhi);
        bool xDownMask = position.x()>(m_sxhi+m_xlo-m_sxlo);
        bool yUpMask = position.y()<(m_sylo+m_yhi-m_syhi);
        bool yDownMask = position.y()>(m_syhi+m_ylo-m_sylo);
        bool zUpMask = position.z()<(m_szlo+m_zhi-m_szhi);
        bool zDownMask = position.z()>(m_szhi+m_zlo-m_szlo);

        std::vector<int> options = {xUpMask-xDownMask, yUpMask-yDownMask, zUpMask-zDownMask};

        // There are 27 possible cases in (-1, 0, 1) (-1, 0, 1) (-1, 0, 1)
        for (int i = -1; i<2; i++)
        {
            for (int j = -1; j<2; j++)
            {
                for (int k = -1; k<2; k++)
                {
                    if ((options[0]==i || i==0) && (options[1] == j || j==0) && (options[2] == k || k==0))
                    {
                        if (!(!i && !j && !k))
                        {
                            double x_offset = i*(m_sxhi-m_sxlo);
                            double y_offset = j*(m_syhi-m_sylo);
                            double z_offset = k*(m_szhi-m_szlo);
                            m_particles.append(position+QVector3D(x_offset, y_offset, z_offset));
                        }
                    }
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
