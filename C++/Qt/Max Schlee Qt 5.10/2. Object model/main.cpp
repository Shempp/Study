#include <QtWidgets>

#include "myclass.h"
#include "mysignal.h"
#include "myslot.h"
#include "counter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyClass obj;
    bool bIsReadOnly = obj.isReadOnly();
    obj.setReadOnly(true);
    bIsReadOnly = obj.isReadOnly();

    MyClass *pobj = new MyClass();
    // Изменение свойства
    pobj->setProperty("readOnly", true);
    // Получение свойства
    bool bReadOnly = pobj->property("readOnly").toBool();
    qDebug() << "bReadOnly:" << bReadOnly;

    // Получение всех свойств объекта
    const QMetaObject* pmo = pobj->metaObject();
    for (int i = 0; i < pmo->propertyCount(); ++i)
    {
        const QMetaProperty mp = pmo->property(i);
        qDebug() << "Property#:" << i;
        qDebug() << "Туре:" << mp.typeName();
        qDebug() << "Name:" << mp.name();

        // QVariant - является универсальным классом, предназначенным для хранения любых типов
        qDebug() << "Value:" << pobj->property(mp.name());
    }

    // Пример вызова сигнала
    MySignal signObj;
    signObj.sendSignal();


    // Примеры связи сигнал-слот
    QLabel lbl("0");
    QPushButton cmd("ADD");
    Counter counter;
    lbl.show();
    cmd.show();

    /*
     * Можно вызывать следующим способом:
     * QObject::connect(pSender, &SenderClass::signalMethod, pReceiver, &ReceiverClass::slotMethod);
     *
     * Проверка соединения:
     * bool bOk = true;
     * bOk &= QObject::connect(&cmd, SIGNAL(clicked()), &counter, SLOT(slotlnc()));
     * Q_ASSERT(bOk);
     *
     * Передать сигнал дальше:
     * connect(pSender, SIGNAL(signalMethod()), SIGNAL(mySignal()));
     *
     * blockSignals(true) - блокировать сигналы
     * signalsBlocked() - узнать заблокированы ли сигналы
     *
     * Соединение с лямбой-функцией напрямую:
     * connect (pcmd, &QPushButton::clicked, [=](){pwgt->hide();});
     *
     * Дисконнект - либо при разрушении объекта, либо QObject::disconnect
    */

    QObject::connect(&cmd, SIGNAL(clicked()), &counter, SLOT(slotInc()));
    QObject::connect(&counter, SIGNAL(counterChanged(int)), &lbl, SLOT(setNum(int)));
    QObject::connect(&counter, SIGNAL(goodbye()), &app, SLOT(quit()));

    /*
     * Все объекты Qt (иерархия с QObject) должны создаваться
     * в памяти динамически, с помощью оператора new. Исключение из этого правила
     * могут составлять только объекты, не имеющие предков. Освобождение памяти автоматическое
    */
    // Объект без предка
    QObject* pobj1 = new QObject;
    // Объект с наследованием от объекта 1
    QObject* pobj2 = new QObject(pobj1);
    QObject* pobj4 = new QObject(pobj2);
    QObject* pobj3 = new QObject(pobj1);
    pobj2->setObjectName("the first child of pobj1");
    pobj3->setObjectName("the second child of pobj1");
    pobj4->setObjectName("the first child of pobj2");

    for (QObject* pobj = pobj4; pobj; pobj = pobj->parent()) {
        qDebug() << pobj->objectName();
    }

    // Поиск нужного объекта-потомка
    QObject* pobjFind = pobj1->findChild<QObject*>("the first child of pobj2");
    if (pobjFind) {
        qDebug() << pobjFind->objectName();
    }

    // Расширенный поиск (рекурсивный) с регуляркой
    QList<QObject*> plist = pobj1->findChildren<QObject*>(QRegExp("th*"));
    // Поиск всех потомков
    // QList<QObject*> plist = pobj1->findChildren<QObject*>();
    // Для отладки также можно использовать dumpObjectinfo() и dumpObjectTree()

    /*
     * Каждый объект, созданный от класса QObject или от унаследованного от него класса, располагает
     * структурой данных, называемой метаобъектной информацией (класс QMetaObject).
     * В ней хранится информация о сигналах, слотах (включая указатели на них), о самом классе
     * и о наследовании.
    */
    qDebug() << pobj1->metaObject()->className();

    // Информация о наследовании классов
    if (pobj1->inherits("QWidget")) {
        QWidget* pwgt = static_cast<QWidget*>(pobj1);
    }
    // или
    QWidget* pwgt = qobject_cast<QWidget*>(pobj1);
    if (pwgt) {

    }


    return app.exec();
}
