#include "constants.h"

Constants::Constants(QObject *parent)
    : QObject{parent}
{}

double Constants::particle_radius() {
    return m_particle_radius;
}

void Constants::setParticle_radius(double radius_to_set) {
    if (radius_to_set != m_particle_radius) {
        m_particle_radius = radius_to_set;
        emit particle_radiusChanged();
    }
}
