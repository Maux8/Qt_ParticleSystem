#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <simulationengine.h>
#include "Tools/particlerenderer.h"
#include "cppinterface.h"
#include "Tools/appparameter.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    AppParameter appParameter;
    qmlRegisterType<ParticleRenderer>("Qt_ParticleSystem", 1, 0, "ParticleRenderer");
    qmlRegisterType<CppInterface>("Qt_ParticleSystem", 1, 0, "CppInterface");
    qmlRegisterSingletonInstance<AppParameter>("Qt_ParticleSystem", 1, 0, "AppParameter", &appParameter);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Qt_ParticleSystem", "Main");
    // get renderer
    QObject* root = engine.rootObjects().first();
    ParticleRenderer* renderer = root->findChild<ParticleRenderer*>("renderer");
    // get interface
    CppInterface* interface = root->findChild<CppInterface*>("cppInterface");
    // start simulation
    SimulationEngine simEngine(nullptr, &appParameter);
    interface->setSimEngine(&simEngine);
    simEngine.setRenderer(renderer); // must be set befor parameters
    simEngine.start();

    return app.exec();
}
