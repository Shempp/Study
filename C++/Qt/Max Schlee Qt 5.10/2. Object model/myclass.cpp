#include "myclass.h"
#include <QtWidgets>

MyClass::MyClass(QObject *pobj)
   : QObject(pobj), m_bReadOnly(false)
{
    // Пример переопределения сигналов
    QSignalMapper* psigMapper = new QSignalMapper(this);
    connect(psigMapper, SIGNAL(mapped(const QString&)), this, SLOT(slotShowAction(const QString&)));

    QPushButton* pcmdl = new QPushButton("Button1");
    connect(pcmdl, SIGNAL(clicked()), psigMapper, SLOT(map()));
    psigMapper->setMapping(pcmdl, "Button1 Action");

    QPushButton* pcmd2 = new QPushButton("Button2");
    connect(pcmd2, SIGNAL(clicked()), psigMapper, SLOT(map()));
    psigMapper->setMapping(pcmdl, "Button2 Action");
}

void MyClass::setReadOnly(bool bReadOnly)
{
    m_bReadOnly = bReadOnly;
}

bool MyClass::isReadOnly() const
{
    return m_bReadOnly;
}

void MyClass::slotShowAction(const QString& str)
{
    qDebug() << str;
}
