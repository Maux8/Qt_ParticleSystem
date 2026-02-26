#include "simulationengine.h"
#include <QDebug>

SimulationEngine::SimulationEngine(QObject* parent)
    : QObject{parent}
{}

void SimulationEngine::spawnParticle(float mouseX, float mouseY) {
    qDebug() << "mouse clicked!";
}
