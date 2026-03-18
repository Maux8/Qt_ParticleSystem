#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>
#include <QtQmlIntegration>
#include <qvectornd.h>

namespace AppConstants
{
inline constexpr int WindowWidth = 1280;
inline constexpr int WindowHeight = 720;
inline constexpr float Gravity = 0.001f;
inline constexpr float ParticleMass = 30.0f;
inline constexpr float ParticleRadius = 20.0f;
}

class Constants : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int windowHeight READ windowHeight CONSTANT)
    Q_PROPERTY(int windowWidth READ windowWidth CONSTANT)

public:
    Constants(QObject *parent = nullptr);

    // get constant values in QML
    int windowWidth() const { return AppConstants::WindowWidth; }
    int windowHeight() const { return AppConstants::WindowHeight; }
};

#endif // CONSTANTS_H
