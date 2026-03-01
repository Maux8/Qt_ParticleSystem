#include "cppinterface.h"
#include <QDebug>

CppInterface::CppInterface(QObject* parent)
    : QObject{parent}
{}

void CppInterface::test() {
    qDebug() << "Mouse clicked!";
}
