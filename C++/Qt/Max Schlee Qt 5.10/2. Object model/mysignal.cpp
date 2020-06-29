#include "mysignal.h"

MySignal::MySignal(QObject *parent) : QObject(parent)
{

}

void MySignal::sendSignal()
{
    // Ключевое слово emit необходимо для отправки сигнала
    emit sendString("Call signal");
}
