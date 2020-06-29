#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
private:
    int m_nValue;
public:
    explicit Counter(QObject *parent = nullptr);

public slots:
    void slotInc();

signals:
    void goodbye();
    void counterChanged(int);
};

#endif // COUNTER_H
