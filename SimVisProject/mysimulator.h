#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include <QVector>
#include <QVector3D>
#include <SimVis/Simulator>
#include <../voronoi-md-analysis/LammpsIO/lammpsio.h>
#include <../voronoi-md-analysis/voronoifracturetracer.h>


class MyWorker : public SimulatorWorker
{
    Q_OBJECT
public:
    MyWorker();
    QVector<QVector3D> vertices;
    VoronoiFractureTracer tracer;
    int timestep;

private:
    virtual void synchronizeSimulator(Simulator *simulator);
    virtual void synchronizeRenderer(Renderable *renderableObject);
    virtual void work() override;
    bool m_nextstep = false;
    int m_stepchange = 100;
    int m_newstep = 100;
    int m_framemin = 0;
    int m_framemax = 200;
};

class MySimulator : public Simulator
{
    Q_OBJECT
    Q_PROPERTY(bool nextStep READ nextStep WRITE setNextStep NOTIFY nextStepChanged)
    Q_PROPERTY(int frameMin READ frameMin WRITE setFrameMin NOTIFY frameMinChanged)
    Q_PROPERTY(int frameMax READ frameMax WRITE setFrameMax NOTIFY frameMaxChanged)
    Q_PROPERTY(int newStep READ newStep WRITE setNewStep NOTIFY newStepChanged)

    bool m_nextStep = false;

    int m_frameMin = 0;
    int m_frameMax = 200;

    int m_newStep = 0;

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

signals:
    void nextStepChanged(bool nextStep);

    void frameMinChanged(int frameMin);

    void frameMaxChanged(int frameMax);

    void newStepChanged(int newStep);

protected:
    virtual SimulatorWorker *createWorker() override;
};

#endif // MYSIMULATOR_H
