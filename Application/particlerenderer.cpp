#include "particlerenderer.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

ParticleRenderer::ParticleRenderer(QQuickItem* parent)
    : QQuickPaintedItem{parent}
{
    setAntialiasing(false); // cheaper
}

void ParticleRenderer::setParticles(const QList<QVector<QVector2D>>* particles) {
    m_particles = particles;
    update(); // repaint
}

void ParticleRenderer::paint(QPainter* painter) {
    if (!m_particles) return;

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::NoPen); // cheaper
    painter->setBrush(Qt::white); // cheaper if all particles have the same color

    for (const QVector<QVector2D>& particle : *m_particles) {
        painter->drawEllipse(particle[0].toPointF(), AppConstants::ParticleRadius, AppConstants::ParticleRadius);
    }
}
