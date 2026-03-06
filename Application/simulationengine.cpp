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
    m_timer = new QTimer(this);
    m_clock = new QElapsedTimer();
    m_renderer = new ParticleRenderer();
    connect(m_timer, &QTimer::timeout, this, &SimulationEngine::onTick);


    /// TEST ///
    QVector<QVector2D> newParticle(2, QVector2D(0,0)); // index 0 = postion, 1 = velocity
    newParticle[0] = QVector2D(100,100);
    m_particles.push_back(newParticle);
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
    // calculate total force


}

void SimulationEngine::spawnParticle(float mouseX, float mouseY) {
    QQmlEngine engine;
    QQmlComponent component(&engine,
                            QUrl::fromLocalFile("Qt_ParticleSystem/presentation/Particle.qml"));

    auto *object = component.create();
    object->setProperty("centered_x", 200);
    object->setProperty("y", 200);
}
