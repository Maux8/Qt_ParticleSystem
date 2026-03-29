#include "particlerenderer.h"
#include "Tools/constants.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <algorithm>

ParticleRenderer::ParticleRenderer(QQuickItem* parent)
    : QQuickPaintedItem{parent}
{
    setAntialiasing(false); // cheaper
}

void ParticleRenderer::setParticles(const QList<Particle>* particles) {
    m_particles = particles;
    update(); // repaint
}

void ParticleRenderer::paint(QPainter* painter) {
    if (!m_particles) return;

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::NoPen); // cheaper
    painter->setBrush(Qt::white); // cheaper if all particles have the same color

    float maxSpeed = 1.0f;

    for (const Particle& particle : *m_particles) {
        float speed = particle.velocity.length();
        speed = std::clamp(speed / maxSpeed, 0.0f, 1.0f);
        int offSet = (1 - speed) * 255;
        painter->setBrush(QColor(255, offSet, offSet));
        painter->drawEllipse(particle.position.toPointF(), AppConstants::ParticleRadius, AppConstants::ParticleRadius);
    }
}
