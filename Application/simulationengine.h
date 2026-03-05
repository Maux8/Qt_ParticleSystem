#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>
#include <QQmlEngine>
#include <QTimer>

class SimulationEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    SimulationEngine(QObject* parent = nullptr);

    void start();

    void stop();

private slots:
    void onTick();

private:
    void step(double dt);

    Q_INVOKABLE void spawnParticle(float mouseX, float mouseY);

    QTimer* m_timer;
    QTime m_clock;
    bool m_running = false;
    int m_mssecAtLastTick = 0;
    int m_simTime = 0;
    double m_accumulator = 0;

    const double FIXED_DT_MS = 1000 / 60; // 60Hz
};

#endif // SIMULATIONENGINE_H
