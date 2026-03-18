#include "physicsmanager.h"

PhysicsManager::PhysicsManager(QObject* parent)
    : QObject{parent}
{}

void PhysicsManager::setParticles( QList<QVector<QVector2D>>* particles) {
    m_particles = particles;
    m_totalForce = QVector2D(0,0);
}

void PhysicsManager::update(float dt) {
    // apply forces
    integrateVelocityVerlet(dt);
    // resolve collision
    // resolve boundaries
}

void PhysicsManager::integrateVelocityVerlet(float dt) {
    QVector2D acceleration = m_totalForce / AppConstants::ParticleMass;
    // for each particle
    for (int i = 0; i < m_particles->count(); i++) {
        // calculate new values
        QPair<QVector2D, QVector2D> newValues = velocityVerlet(i, acceleration, dt); // QPair<Pos,Vel>
        // check for out of bounds condition
        if (newValues.first.x() + AppConstants::ParticleRadius) {

        }




        // set new position / velocity




        (*m_particles)[i][0] = newValues.first;
        (*m_particles)[i][1] = newValues.second;
    }
}

void PhysicsManager::resolveBoundaries() {
    // for each particle
    for (int i = 0; i < m_particles->count(); i++) {

    }
}

void PhysicsManager::addForce(QString name, QVector2D forceToAdd) {
    m_forces.insert(name, forceToAdd);
    m_totalForce += forceToAdd;
}

void PhysicsManager::removeForce(QString name, QVector2D forceToRemove) {
    m_forces.insert(name, forceToRemove);
    m_totalForce -= forceToRemove;
}

QPair<QVector2D, QVector2D> PhysicsManager::velocityVerlet(int indexOfParticle, QVector2D acceleration, float dt) {
    // retrieve particle values
    QVector2D position = m_particles->at(indexOfParticle)[0];
    QVector2D velocity = m_particles->at(indexOfParticle)[1];

    // velocity verlet integration
    position += m_particles->at(indexOfParticle)[1] * dt + 0.5 * acceleration * dt * dt;
    velocity += acceleration * dt;

    return QPair<QVector2D, QVector2D>(position, velocity);
}
