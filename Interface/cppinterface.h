#ifndef CPPINTERFACE_H
#define CPPINTERFACE_H

#include "simulationengine.h"

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

class CppInterface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    CppInterface(QObject* parent = nullptr);

    void setSimEngine(SimulationEngine* simEngine);

    Q_INVOKABLE void test();
    Q_INVOKABLE void screenClicked(float mouseX, float mouseY);

private:
    SimulationEngine* m_simEngine = nullptr;
};

#endif // CPPINTERFACE_H
