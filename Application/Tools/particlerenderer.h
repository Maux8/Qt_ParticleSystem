#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "Models/Particle.h"

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>

class ParticleRenderer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ParticleRenderer(QQuickItem* parent = nullptr);
    void setParticles(const QList<Particle>* particles);
    void paint(QPainter* painter) override;

private:
    const QList<Particle>* m_particles = nullptr;
};

#endif // PARTICLERENDERER_H
