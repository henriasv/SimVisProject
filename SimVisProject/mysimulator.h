#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include <QVector>
#include <QVector3D>
#include <SimVis/Simulator>
#include <../LammpsIO/lammpsio.h>

#include <analysisstep.h>
#include <map>



class MyWorker : public SimulatorWorker
{
    Q_OBJECT
public:
    MyWorker();
    QVector<QVector3D> vertices;
    std::vector<double> intensities;
    LammpsIO* lammpsIO;
    std::map<int, AnalysisStep> stepData;
    int timestep;

private:
    virtual void synchronizeSimulator(Simulator *simulator) override;
    virtual void synchronizeRenderer(Renderable *renderableObject) override;
    virtual void work() override;
    bool m_nextstep = false;
    bool m_ispreload = false;
    int m_framestep = 0;
    int m_newstep = 0;
    int m_framemin = 0;
    int m_framemax = 0;
    double m_skewfactor = 0;
    double m_rsq_threshold = 0;
    bool m_isplottriangles = true;
    bool m_isplotspheres = true;
    double m_xfac = 1.0;
    double m_yfac = 1.0;
    double m_zfac = 1.0;
};

class MySimulator : public Simulator
{
    Q_OBJECT
    Q_PROPERTY(bool nextStep READ nextStep WRITE setNextStep NOTIFY nextStepChanged)
    Q_PROPERTY(int frameMin READ frameMin WRITE setFrameMin NOTIFY frameMinChanged)
    Q_PROPERTY(int frameMax READ frameMax WRITE setFrameMax NOTIFY frameMaxChanged)
    Q_PROPERTY(int newStep READ newStep WRITE setNewStep NOTIFY newStepChanged)
    Q_PROPERTY(int frameStep READ frameStep WRITE setFrameStep NOTIFY frameStepChanged)
    Q_PROPERTY(double rSqThreshold READ rSqThreshold WRITE setRSqThreshold NOTIFY rSqThresholdChanged)
    Q_PROPERTY(double skewFactor READ skewFactor WRITE setSkewFactor NOTIFY skewFactorChanged)
    Q_PROPERTY(double xfac READ xfac WRITE setXfac NOTIFY xfacChanged)
    Q_PROPERTY(double yfac READ yfac WRITE setYfac NOTIFY yfacChanged)
    Q_PROPERTY(double zfac READ zfac WRITE setZfac NOTIFY zfacChanged)
    Q_PROPERTY(bool isPreload READ isPreload WRITE setIsPreload NOTIFY isPreloadChanged)
    Q_PROPERTY(bool isPlotSpheres READ isPlotSpheres WRITE setIsPlotSpheres NOTIFY isPlotSpheresChanged)
    Q_PROPERTY(bool isPlotTriangles READ isPlotTriangles WRITE setIsPlotTriangles NOTIFY isPlotTrianglesChanged)

    bool m_nextStep = false;
    int m_frameMin = 0;
    int m_frameMax = 0;
    int m_newStep = 0;
    double m_rSqThreshold = 100;
    double m_skewFactor = 0.5;
    double m_xfac = 0.3;
    double m_yfac = 0.3;
    double m_zfac = 0.3;
    bool m_isPreload = false;
    int m_frameStep;
    bool m_isPlotSpheres = true;
    bool m_isPlotTriangles = true;

public:
    MySimulator();
    void nextstep();
    // Simulator interface
    bool nextStep() const;

    int frameMin() const
    {
        return m_frameMin;
    }

    int frameMax() const
    {
        return m_frameMax;
    }

    int newStep() const
    {
        return m_newStep;
    }

    double rSqThreshold() const
    {
        return m_rSqThreshold;
    }

    double skewFactor() const
    {
        return m_skewFactor;
    }

    double xfac() const
    {
        return m_xfac;
    }

    double yfac() const
    {
        return m_yfac;
    }

    double zfac() const
    {
        return m_zfac;
    }

    bool isPreload() const
    {
        return m_isPreload;
    }

    int frameStep() const
    {
        return m_frameStep;
    }

    bool isPlotSpheres() const
    {
        return m_isPlotSpheres;
    }

    bool isPlotTriangles() const
    {
        return m_isPlotTriangles;
    }

public slots:
    void setNextStep(bool nextStep);

    void setFrameMin(int frameMin)
    {
        if (m_frameMin == frameMin)
            return;

        m_frameMin = frameMin;
        emit frameMinChanged(frameMin);
    }

    void setFrameMax(int frameMax)
    {
        if (m_frameMax == frameMax)
            return;

        m_frameMax = frameMax;
        emit frameMaxChanged(frameMax);
    }

    void setNewStep(int newStep)
    {
        if (m_newStep == newStep)
            return;

        m_newStep = newStep;
        emit newStepChanged(newStep);
    }

    void setRSqThreshold(double rSqThreshold)
    {
        if (m_rSqThreshold == rSqThreshold)
            return;

        m_rSqThreshold = rSqThreshold;
        emit rSqThresholdChanged(rSqThreshold);
    }

    void setSkewFactor(double skewFactor)
    {
        if (m_skewFactor == skewFactor)
            return;

        m_skewFactor = skewFactor;
        emit skewFactorChanged(skewFactor);
    }

    void setXfac(double xfac)
    {
        if (m_xfac == xfac)
            return;

        m_xfac = xfac;
        emit xfacChanged(xfac);
    }

    void setYfac(double yfac)
    {
        if (m_yfac == yfac)
            return;

        m_yfac = yfac;
        emit yfacChanged(yfac);
    }

    void setZfac(double zfac)
    {
        if (m_zfac == zfac)
            return;

        m_zfac = zfac;
        emit zfacChanged(zfac);
    }

    void setIsPreload(bool isPreload)
    {
        if (m_isPreload == isPreload)
            return;

        m_isPreload = isPreload;
        emit isPreloadChanged(isPreload);
    }

    void setFrameStep(int frameStep)
    {
        if (m_frameStep == frameStep)
            return;

        m_frameStep = frameStep;
        emit frameStepChanged(frameStep);
    }

    void setIsPlotSpheres(bool isPlotSpheres)
    {
        if (m_isPlotSpheres == isPlotSpheres)
            return;

        m_isPlotSpheres = isPlotSpheres;
        emit isPlotSpheresChanged(isPlotSpheres);
    }

    void setIsPlotTriangles(bool isPlotTriangles)
    {
        if (m_isPlotTriangles == isPlotTriangles)
            return;

        m_isPlotTriangles = isPlotTriangles;
        emit isPlotTrianglesChanged(isPlotTriangles);
    }

signals:
    void nextStepChanged(bool nextStep);
    void frameMinChanged(int frameMin);
    void frameMaxChanged(int frameMax);
    void newStepChanged(int newStep);
    void rSqThresholdChanged(double rSqThreshold);
    void skewFactorChanged(double skewFactor);
    void xfacChanged(double xfac);
    void yfacChanged(double yfac);
    void zfacChanged(double zfac);
    void isPreloadChanged(bool isPreload);
    void frameStepChanged(int frameStep);

    void isPlotSpheresChanged(bool isPlotSpheres);

    void isPlotTrianglesChanged(bool isPlotTriangles);

protected:
    virtual SimulatorWorker *createWorker() override;
};

#endif // MYSIMULATOR_H
