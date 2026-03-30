#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Models/Particle.h"
#include "Tools/appparameter.h"

#include <QVector2D>
#include <QMap>
#include <QObject>

class PhysicsManager : public QObject
{
    Q_OBJECT
public:
    PhysicsManager(QObject* parent = nullptr);
    void setParticles(QList<Particle>* particles);
    void setAppParameter(const AppParameter* appParameter);
    void update(float dt);
    void addForce(QString name, QVector2D forceToAdd);
    void removeForce(QString name, QVector2D forceToRemove);

private:
    QPair<QVector2D, QVector2D> velocityVerlet(int indexOfParticle, QVector2D acceleration, float dt);
    void integrateVelocityVerlet(float dt); // integrate over all particles applying m_forces to them + resolve boundaries
    void resolveOverlap();

    QList<Particle>* m_particles = nullptr;
    const AppParameter* m_appParameter  = nullptr;
    // forces
    QMap<QString, QVector2D> m_forces; // all forces for all particles
    QVector2D m_totalForce; // always carries sum of all forces
};

#endif // PHYSICSMANAGER_H
