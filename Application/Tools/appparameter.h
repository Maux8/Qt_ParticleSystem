#ifndef APPPARAMETER_H
#define APPPARAMETER_H

#include <QObject>

class AppParameter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int windowWidth READ windowWidth CONSTANT)
    Q_PROPERTY(int windowHeight READ windowHeight CONSTANT)

    Q_PROPERTY(float gravity READ gravity WRITE setGravity NOTIFY gravityChanged FINAL)
    Q_PROPERTY(float damping READ damping WRITE setDamping NOTIFY dampingChanged FINAL)
    Q_PROPERTY(float particleRadius READ particleRadius WRITE setParticleRadius NOTIFY particleRadiusChanged FINAL)
    Q_PROPERTY(float particleMass READ particleMass WRITE setParticleMass NOTIFY particleMassChanged FINAL)

public:
    explicit AppParameter(QObject *parent = nullptr);

    int windowWidth() const { return m_windowWidth; }
    int windowHeight() const { return m_windowHeight; }

    float gravity() const { return m_gravity; }
    float damping() const { return m_damping; }
    float particleRadius() const { return m_particleRadius; }
    float particleMass() const { return m_particleMass; }

    void setGravity(float value);
    void setDamping(float value);
    void setParticleRadius(float value);
    void setParticleMass(float value);

signals:
    void gravityChanged();
    void dampingChanged();
    void particleRadiusChanged();
    void particleMassChanged();
private:
    static constexpr int m_windowHeight = 720;
    static constexpr int m_windowWidth = 1280;

    float m_gravity = 0.04f;
    float m_damping = 0.90f;
    float m_particleRadius = 20.0f;
    float m_particleMass = 30.0f;

};

#endif // APPPARAMETER_H
