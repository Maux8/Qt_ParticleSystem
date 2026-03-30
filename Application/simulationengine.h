#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "Tools/particlerenderer.h"
#include "Tools/appparameter.h"
#include "physicsmanager.h"
#include "Models/Particle.h"

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
    SimulationEngine(QObject* parent = nullptr, AppParameter* appParameter = nullptr);

    void start();
    void stop();
    void setRenderer(ParticleRenderer* renderer);
    void setAppParemeter(AppParameter* appParameter);
    void spawnParticle(float mouseX, float mouseY);

private slots:
    void onTick();

private:
    void step(double dt);

    // simulation propertiers
    AppParameter*       m_appParameter = nullptr;
    ParticleRenderer*   m_renderer = nullptr;
    PhysicsManager*     m_physicsManager;
    QTimer*             m_timer;
    QElapsedTimer*      m_clock;
    bool                m_running = false;
    float               m_simTime = 0.0f;
    float               m_accumulator = 0.0f;

    const float FIXED_DT_MS = 1000 / 60; // 60Hz ~ 16,6 ms interval

    // particles
    QList<Particle> m_particles;
};

#endif // SIMULATIONENGINE_H
