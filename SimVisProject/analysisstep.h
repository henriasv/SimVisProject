#ifndef ANALYSISSTEP_H
#define ANALYSISSTEP_H

#include <vector>
#include <QVector3D>
#include <triangle.h>
#include <QDebug>
#include <../LammpsIO/lammpsio.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/Simple_cartesian.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Fixed_alpha_shape_3.h>
#include <CGAL/Fixed_alpha_shape_vertex_base_3.h>
#include <CGAL/Fixed_alpha_shape_cell_base_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Fixed_alpha_shape_vertex_base_3<K>               Vb;
typedef CGAL::Fixed_alpha_shape_cell_base_3<K>                 Fb;
typedef CGAL::Triangulation_data_structure_3<Vb,Fb>      Tds;
typedef CGAL::Delaunay_triangulation_3<K,Tds,CGAL::Fast_location>  Delaunay;
typedef CGAL::Fixed_alpha_shape_3<Delaunay>                    Alpha_shape_3;
typedef K::Point_3                                  Point;

class AnalysisStep
{
public:
    AnalysisStep(){} //Dummy empty constructor (Hack)
    AnalysisStep(LammpsIO & reader, int timestep, double xfac, double yfac, double zfac, char element);
    std::vector<Triangle> triangleData; // Coordinates of the
    QVector3D boundingBoxLo;
    QVector3D boundingBoxHi;
    QVector3D analysisBoxLo;
    QVector3D analysisBoxHi;
    double m_surfaceArea = 0;
    bool m_isValid = false;

    void addTriangle(Triangle triangle);
    void addTriangle(QVector3D, QVector3D, QVector3D);
    void setBoundingBox(QVector3D, QVector3D);
    void setAnalysisBox(QVector3D, QVector3D);
    double surfaceArea();
    bool isValid();
    static bool inBox(const Point & inPoint, const std::vector<double> & vertices);
    static std::vector<double> contractedBox(const LammpsFrame & frame, double xfac, double yfac, double zfac);
};

#endif // ANALYSISSTEP_H
