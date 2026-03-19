#include "physicsmanager.h"
#include "constants.h"

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
    resolveOverlap();
}

void PhysicsManager::integrateVelocityVerlet(float dt) {
    QVector2D acceleration = m_totalForce / AppConstants::ParticleMass;
    // for each particle
    for (int i = 0; i < m_particles->count(); i++) {
        // calculate new values
        QPair<QVector2D, QVector2D> newValues = velocityVerlet(i, acceleration, dt); // QPair<Pos,Vel>
        // check for out of bounds condition
        // right side
        if (newValues.first.x() + AppConstants::ParticleRadius >= AppConstants::WindowWidth) {
            newValues.first.setX(AppConstants::WindowWidth - AppConstants::ParticleRadius); // set particle back
            newValues.second.setX(newValues.second.x() * -1 * AppConstants::Damping); // revert velocity and apply damping
        }
        // left side
        else if (newValues.first.x() - AppConstants::ParticleRadius <= 0) {
            newValues.first.setX(AppConstants::ParticleRadius);
            newValues.second.setX(newValues.second.x() * -1 * AppConstants::Damping);
        }
        // top
        if (newValues.first.y() - AppConstants::ParticleRadius <= 0) {
            newValues.first.setY(AppConstants::ParticleRadius);
            newValues.second.setY(newValues.second.y() * -1 * AppConstants::Damping);
        }
        // bottom
        else if (newValues.first.y() + AppConstants::ParticleRadius >= AppConstants::WindowHeight) {
            newValues.first.setY(AppConstants::WindowHeight - AppConstants::ParticleRadius);
            newValues.second.setY(newValues.second.y() * -1 * AppConstants::Damping);
        }
        // set new position / velocity
        (*m_particles)[i][0] = newValues.first;
        (*m_particles)[i][1] = newValues.second;
    }
}

void PhysicsManager::resolveOverlap() {
    // for each particle
    for (int i = 0; i < m_particles->count(); i++) {
        for (int j = i + 1; j < m_particles->count(); j++) {
            float minDistance = AppConstants::ParticleRadius * 2;
            QVector2D difference = m_particles->at(j)[0] - m_particles->at(i)[0]; // points from i to j
            // overlap
            if (difference.length() < minDistance) {
                // calculate collion response
                QVector2D differenceNorm = difference.normalized();
                QVector2D relativeVel = m_particles->at(j)[1] - m_particles->at(i)[1];
                QVector2D impulse = differenceNorm * (QVector2D::dotProduct(relativeVel, differenceNorm)) / (AppConstants::ParticleMass * 2); // *2 because both particles have the same mass

                // apply repulsion force to prevent sticking
                QVector2D repulsion = differenceNorm * (minDistance - difference.length());

                // update velocities
                (*m_particles)[i][1] += impulse / AppConstants::ParticleMass;
                (*m_particles)[j][1] -= impulse / AppConstants::ParticleMass;

                // apply repulsion force
                (*m_particles)[i][1] -= repulsion / AppConstants::ParticleMass;
                (*m_particles)[j][1] += repulsion / AppConstants::ParticleMass;
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
    QVector2D position = m_particles->at(indexOfParticle)[0];
    QVector2D velocity = m_particles->at(indexOfParticle)[1];

    // velocity verlet integration
    position += m_particles->at(indexOfParticle)[1] * dt + 0.5 * acceleration * dt * dt;
    velocity += acceleration * dt;

    return QPair<QVector2D, QVector2D>(position, velocity);
}
