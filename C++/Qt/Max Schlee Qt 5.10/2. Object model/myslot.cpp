#include "myslot.h"
#include <QDebug>

MySlot::MySlot(QObject *parent) : QObject(parent)
{

}

void MySlot::slot()
{
    qDebug() << "I'm а slot";

    // Узнать, от какого объекта был выслан сигнал
    qDebug() << sender()->objectName();
}
