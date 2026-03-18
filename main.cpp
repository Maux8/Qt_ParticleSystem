#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <simulationengine.h>
#include <particlerenderer.h>
#include "constants.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ParticleRenderer>("Qt_ParticleSystem", 1, 0, "ParticleRenderer");
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    Constants constants;
    engine.rootContext()->setContextProperty("Constants", &constants);
    engine.loadFromModule("Qt_ParticleSystem", "Main");
    // get renderer
    QObject* root = engine.rootObjects().first();
    ParticleRenderer* renderer = root->findChild<ParticleRenderer*>("renderer");
    // start simulation
    SimulationEngine simEngine = new SimulationEngine();
    simEngine.setRenderer(renderer);
    simEngine.start();

    return app.exec();
}
