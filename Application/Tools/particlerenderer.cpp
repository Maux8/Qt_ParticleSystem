#include "particlerenderer.h"
#include "Tools/constants.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

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

    for (const Particle& particle : *m_particles) {
        painter->drawEllipse(particle.position.toPointF(), AppConstants::ParticleRadius, AppConstants::ParticleRadius);
    }
}
