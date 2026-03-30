#include "simulationengine.h"
#include <QQmlComponent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <algorithm>

SimulationEngine::SimulationEngine(QObject* parent, AppParameter* appParameter)
    : QObject{parent}, m_appParameter(appParameter)
{
    // loop
    m_timer = new QTimer(this);
    m_clock = new QElapsedTimer();
    connect(m_timer, &QTimer::timeout, this, &SimulationEngine::onTick);

    // construct properties
    m_physicsManager = new PhysicsManager();
    m_particles = QList<Particle>();

    // set particles in physicsmanager (renderer particles are set from main.cpp)
    m_physicsManager->setParticles(&m_particles);
    m_physicsManager->setAppParameter(m_appParameter);

    /// TEST ///
    m_physicsManager->addForce(QString("gravity"), QVector2D(0, m_appParameter->gravity()));
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
    m_physicsManager->update(dt);
}

void SimulationEngine::setRenderer(ParticleRenderer* renderer) {
    m_renderer = renderer;
    m_renderer->setParticles(&m_particles);
    m_renderer->setAppParameter(m_appParameter);
}

void SimulationEngine::setAppParemeter(AppParameter* appParameter) {
    m_appParameter = appParameter;
}

void SimulationEngine::spawnParticle(float mouseX, float mouseY) {
    Particle newParticle;
    newParticle.position = QVector2D(mouseX, mouseY);
    newParticle.velocity = QVector2D(0,0);
    m_particles.push_back(newParticle);
}
