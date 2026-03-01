#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>
#include <QQmlEngine>

class SimulationEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    SimulationEngine(QObject* parent = nullptr);

    Q_INVOKABLE void spawnParticle(float mouseX, float mouseY);
};

#endif // SIMULATIONENGINE_H
