#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <QVector2D>
#include <QMap>
#include <QObject>

#include "constants.h"

class PhysicsManager : public QObject
{
    Q_OBJECT
public:
    PhysicsManager(QObject* parent = nullptr);
    void setParticles(QList<QVector<QVector2D>>* particles);
    void update(float dt);
    void addForce(QString name, QVector2D forceToAdd);
    void removeForce(QString name, QVector2D forceToRemove);

private:
    QPair<QVector2D, QVector2D> velocityVerlet(int indexOfParticle, QVector2D acceleration, float dt);
    void integrateVelocityVerlet(float dt); // integrate over all particles applying m_forces to them
    void resolveBoundaries();

    QList<QVector<QVector2D>>* m_particles = nullptr;
    // forces
    QMap<QString, QVector2D> m_forces; // all forces for all particles
    QVector2D m_totalForce; // always carries sum of all forces
};

#endif // PHYSICSMANAGER_H
