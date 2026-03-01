#ifndef CPPINTERFACE_H
#define CPPINTERFACE_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

class CppInterface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    CppInterface(QObject* parent = nullptr);

    Q_INVOKABLE void test();
};

#endif // CPPINTERFACE_H
