#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

class SimulationEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    SimulationEngine(QObject* parent = nullptr);

    void spawnParticle(float mouseX, float mouseY);
};

#endif // SIMULATIONENGINE_H
