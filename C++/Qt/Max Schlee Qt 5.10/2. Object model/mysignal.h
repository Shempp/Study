#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <QObject>

/* При использовании механизма сигнала/слотов необходимо наследование от QObject */
class MySignal : public QObject
{
    Q_OBJECT
public:
    explicit MySignal(QObject *parent = nullptr);

    void sendSignal();

/* Сигналы */
signals:
    void sendString(const QString&);
};

#endif // MYSIGNAL_H

