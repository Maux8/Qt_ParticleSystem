#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>
#include <QQmlEngine>
#include <QTimer>
#include <QElapsedTimer>

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
    QElapsedTimer m_clock;
    bool m_running = false;
    float m_simTime = 0;
    float m_accumulator = 0;

    const double FIXED_DT_MS = 1000 / 60; // 60Hz ~ 16,6 ms intera
};

#endif // SIMULATIONENGINE_H
