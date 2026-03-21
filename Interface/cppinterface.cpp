#include "cppinterface.h"
#include <QDebug>

CppInterface::CppInterface(QObject* parent)
    : QObject{parent}
{}

void CppInterface::setSimEngine(SimulationEngine* simEngine) {
    if (simEngine != nullptr && simEngine != m_simEngine) {
        m_simEngine = simEngine;
    }
}

void CppInterface::test() {
    qDebug() << "Mouse clicked!";
}

void CppInterface::screenClicked(float mouseX, float mouseY) {
    for (int i = 0; i < 30; i++) {
        m_simEngine->spawnParticle(mouseX + 5 * i, mouseY);
    }
}
