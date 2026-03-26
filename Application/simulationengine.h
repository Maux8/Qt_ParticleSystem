#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "particlerenderer.h"
#include "physicsmanager.h"

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>
#include <QQmlEngine>
#include <QTimer>
#include <QElapsedTimer>
#include <QList>
#include <QVector>
#include <QVector2D>

class SimulationEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    SimulationEngine(QObject* parent = nullptr);

    void start();
    void stop();
    void setRenderer(ParticleRenderer* renderer);
    void spawnParticle(float mouseX, float mouseY);

private slots:
    void onTick();

private:
    void step(double dt);

    // simulation properties
    ParticleRenderer* m_renderer = nullptr;
    PhysicsManager* m_physicsManager;
    QTimer* m_timer;
    QElapsedTimer* m_clock;
    bool m_running = false;
    float m_simTime = 0;
    float m_accumulator = 0;

    const float FIXED_DT_MS = 1000 / 60; // 60Hz ~ 16,6 ms interval

    // particles
    QList<QVector<QVector2D>> m_particles; // [particle ID] [0 = position, 1 = velocity]
};

#endif // SIMULATIONENGINE_H
