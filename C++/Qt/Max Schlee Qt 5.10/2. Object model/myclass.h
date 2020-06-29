#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    /*
     * Макрос Q_OBJECT необходим для механихма
     * сигнала/слотов или когда необходима информация о свойствах
    */
    Q_OBJECT
    /*
     * Макрос Q_PROPERTY задает свойство readOnly
     * тип свойства, методы READ и WRITE
     * К этому свойству можно обращаться из QtDesigner, например
    */
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
private:
    bool m_bReadOnly;

public:
    MyClass(QObject *pobj = nullptr);

    void setReadOnly(bool bReadOnly);

    bool isReadOnly() const;

public slots:
    void slotShowAction(const QString &str);
};

#endif // MYCLASS_H
