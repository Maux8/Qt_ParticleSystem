#include "simulationengine.h"
#include <QQmlComponent>
#include <QDebug>
#include <QFile>
#include <QDir>

SimulationEngine::SimulationEngine(QObject* parent)
    : QObject{parent}
{

}

void SimulationEngine::spawnParticle(float mouseX, float mouseY) {
    QQmlEngine engine;
    QQmlComponent component(&engine,
                            QUrl::fromLocalFile("Qt_ParticleSystem/presentation/Particle.qml"));

    auto *object = component.create();
    object->setProperty("centered_x", 200);
    object->setProperty("y", 200);
}
