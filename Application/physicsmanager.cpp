#include "physicsmanager.h"

PhysicsManager::PhysicsManager(QObject* parent)
    : QObject{parent}
{}

void PhysicsManager::setParticles( QList<Particle>* particles) {
    m_particles = particles;
    m_totalForce = QVector2D(0,0);
}

void PhysicsManager::setAppParameter(const AppParameter* appParameter) {
    m_appParameter = appParameter;
}

void PhysicsManager::update(float dt) {
    // apply forces
    integrateVelocityVerlet(dt);
    // resolve collision
    resolveOverlap();
}

void PhysicsManager::integrateVelocityVerlet(float dt) {
    QVector2D acceleration = m_totalForce / m_appParameter->particleMass();
    // for each particle
    for (int i = 0; i < m_particles->count(); i++) {
        // calculate new values
        QPair<QVector2D, QVector2D> newValues = velocityVerlet(i, acceleration, dt); // QPair<Pos,Vel>
        // check for out of bounds condition
        // right side
        if (newValues.first.x() + m_appParameter->particleRadius() >= m_appParameter->windowWidth()) {
            newValues.first.setX(m_appParameter->windowWidth() - m_appParameter->particleRadius()); // set particle back
            newValues.second.setX(newValues.second.x() * -1 * m_appParameter->damping()); // revert velocity and apply damping
        }
        // left side
        else if (newValues.first.x() - m_appParameter->particleRadius() <= 0) {
            newValues.first.setX(m_appParameter->particleRadius());
            newValues.second.setX(newValues.second.x() * -1 * m_appParameter->damping());
        }
        // top
        if (newValues.first.y() - m_appParameter->particleRadius() <= 0) {
            newValues.first.setY(m_appParameter->particleRadius());
            newValues.second.setY(newValues.second.y() * -1 * m_appParameter->damping());
        }
        // bottom
        else if (newValues.first.y() + m_appParameter->particleRadius() >= m_appParameter->windowHeight()) {
            newValues.first.setY(m_appParameter->windowHeight() - m_appParameter->particleRadius());
            newValues.second.setY(newValues.second.y() * -1 * m_appParameter->damping());
        }
        // set new position / velocity
        (*m_particles)[i].position = newValues.first;
        (*m_particles)[i].velocity = newValues.second;
    }
}

void PhysicsManager::resolveOverlap() {
    // for each particle
    for (int i = 0; i < m_particles->count(); i++) {
        for (int j = i + 1; j < m_particles->count(); j++) {
            float minDistance = m_appParameter->particleRadius() * 2;
            QVector2D difference = m_particles->at(j).position - m_particles->at(i).position; // points from i to j
            // overlap
            if (difference.length() < minDistance) {
                // calculate collion response
                QVector2D differenceNorm = difference.normalized();
                QVector2D relativeVel = m_particles->at(j).velocity - m_particles->at(i).velocity;
                QVector2D impulse = differenceNorm * (QVector2D::dotProduct(relativeVel, differenceNorm)) / (m_appParameter->particleMass() * 2); // *2 because both particles have the same mass

                // apply repulsion force to prevent sticking
                QVector2D repulsion = differenceNorm * (minDistance - difference.length());

                // update velocities
                (*m_particles)[i].velocity += impulse / m_appParameter->particleMass();
                (*m_particles)[i].velocity *= m_appParameter->damping();
                (*m_particles)[j].velocity -= impulse / m_appParameter->particleMass();
                (*m_particles)[j].velocity *= m_appParameter->damping();

                // apply repulsion force
                (*m_particles)[i].velocity -= repulsion / m_appParameter->particleMass();
                (*m_particles)[j].velocity += repulsion / m_appParameter->particleMass();
            }
        }
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
    QVector2D position = m_particles->at(indexOfParticle).position;
    QVector2D velocity = m_particles->at(indexOfParticle).velocity;

    // velocity verlet integration
    position += m_particles->at(indexOfParticle).velocity * dt + 0.5 * acceleration * dt * dt;
    velocity += acceleration * dt;

    return QPair<QVector2D, QVector2D>(position, velocity);
}
