#include "counter.h"

Counter::Counter(QObject *parent) : QObject(parent),
                                    m_nValue(0)
{

}

void Counter::slotInc()
{
    emit counterChanged(++m_nValue);

    if (m_nValue == 5) {
        emit goodbye();
    }
}
