#include "simulationengine.h"
#include <QQmlComponent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <algorithm>

SimulationEngine::SimulationEngine(QObject* parent)
    : QObject{parent}
{
    // loop
    m_timer = new QTimer(this);
    m_clock = new QElapsedTimer();
    connect(m_timer, &QTimer::timeout, this, &SimulationEngine::onTick);

    // construct properties
    m_physicsManager = new PhysicsManager();
    m_renderer = new ParticleRenderer();
    m_particles = QList<QVector<QVector2D>>();

    // set particles in physicsmanager (renderer particles are set from main.cpp)
    m_physicsManager->setParticles(&m_particles);

    /// TEST ///
    QVector<QVector2D> newParticle(2, QVector2D(0,0)); // index 0 = postion, 1 = velocity
    newParticle[0] = QVector2D(100,100);
    m_particles.push_back(newParticle);
    m_physicsManager->addForce(QString("gravity"), QVector2D(0, GRAVITY_STRENGTH));
    /// TEST END ///
}

void SimulationEngine::start() {
    m_running = true;
    m_timer->start(FIXED_DT_MS);
    m_clock->start();
}

void SimulationEngine::stop() {
    m_running = false;
    m_timer->stop();
}

void SimulationEngine::setRenderer(ParticleRenderer* renderer) {
    m_renderer = renderer;
    m_renderer->setParticles(&m_particles);
}

void SimulationEngine::onTick() {
    if (!m_running) return;

    float msSinceLastTick = m_clock->restart();
    m_accumulator += msSinceLastTick;
    m_accumulator = std::clamp(m_accumulator, 0.0f, 167.0f); // at 60hz 167 ms are 10 steps

    while (m_accumulator >= FIXED_DT_MS) {
        step(FIXED_DT_MS);
        m_simTime += FIXED_DT_MS;
        m_accumulator -= FIXED_DT_MS;
    }

    // update UI
    m_renderer->setParticles(&m_particles);
}

void SimulationEngine::step(double dt) {
    m_physicsManager->integrateVelocityVerlet(dt);
}

void SimulationEngine::spawnParticle(float mouseX, float mouseY) {
    QQmlEngine engine;
    QQmlComponent component(&engine,
                            QUrl::fromLocalFile("Qt_ParticleSystem/presentation/Particle.qml"));

    auto *object = component.create();
    object->setProperty("centered_x", 200);
    object->setProperty("y", 200);
}
