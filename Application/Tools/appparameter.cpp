#include "appparameter.h"

AppParameter::AppParameter(QObject *parent)
    : QObject{parent}
{}

void AppParameter::setParticleRadius(float value) {
    if (m_particleRadius != value) {
        m_particleRadius = value;
        emit particleRadiusChanged();
    }
}

void AppParameter::setDamping(float value) {
    if (m_damping != value) {
        m_damping = value;
        emit dampingChanged();
    }
}

void AppParameter::setGravity(float value) {
    if (m_gravity != value) {
        m_gravity = value;
        emit gravityChanged();
    }
}

void AppParameter::setParticleMass(float value) {
    if (m_particleMass != value ) {
        m_particleMass = value;
        emit particleMassChanged();
    }
}
