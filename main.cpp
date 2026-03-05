#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <simulationengine.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Qt_ParticleSystem", "Main");
    SimulationEngine simEngine = new SimulationEngine();
    simEngine.start();

    return app.exec();
}
