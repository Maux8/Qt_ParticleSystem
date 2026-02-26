#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QQuickPaintedItem>

class Particle : public QQuickPaintedItem
{
    //Q_OBJECT
    //QML_ELEMENT
public:
    Particle(QQuickItem *parent = nullptr);
};

#endif // PARTICLE_H
