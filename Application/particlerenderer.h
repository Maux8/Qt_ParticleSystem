#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include <constants.h>

#include <QObject>
#include <QQuickItem>
#include <QQuickPaintedItem>

class ParticleRenderer : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ParticleRenderer(QQuickItem* parent = nullptr);
    void setParticles(const QList<QVector<QVector2D>>* particles);
    void paint(QPainter* painter) override;

private:
    const QList<QVector<QVector2D>>* m_particles = nullptr;
};

#endif // PARTICLERENDERER_H
