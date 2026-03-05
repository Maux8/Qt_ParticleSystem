#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>
#include <QtQmlIntegration>

class Constants : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double particle_radius READ particle_radius WRITE setParticle_radius NOTIFY particle_radiusChanged FINAL)
public:
    Constants(QObject *parent = nullptr);

    // get constant values
    double particle_radius();

    // set constant values
    void setParticle_radius(double radius_to_set);

signals:
    void particle_radiusChanged();

private:
    double m_particle_radius = 40; // radius for all particles
};

#endif // CONSTANTS_H
