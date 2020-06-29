#include <QCoreApplication>
#include <QDebug>
#include <QByteArray>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
     * Последовательные контейнеры (вектор, список, стек, очередь):
     * QVector<T> - вектор
     * QList<T> - список;
     * QLinkedList<T> - двусвязный список;
     * QStack<T> - стек;
     * QQueue<T> - очередь.
    */

    /*
     * Ассоциативные контейнеры (множество, словарь, хэш):
     * QSet<T> - множество;
     * QМар<К, Т> - словарь;
     * QМultiMap<K, Т> - мультисловарь;
     * QHash<K, Т> - хэш;
     * QМultiHash<K, Т> - мультихэш.
    */

    /*
     * Итераторы в стиле Java
     * Они указывают не на сам элемент, а на двух его соседей (на самом деле объекты, а не указатели)
    */
    QList<QString> list;
    list << "Within Temptation" << "Anubis" << "Mantus";
    // Неизменяется
    QListIterator<QString> it(list);
    while (it.hasNext()) {
        qDebug() << "Element:" << it.next() ;
    }
    // Для изменения использовать QMutableListIterator
    QList<QString> list2;
    list2 << "Beatles" << "АВВА" << "Boney М";
    QMutableListIterator<QString> it2(list2);
    while (it2.hasNext()) {
        if (it2.next() == "Boney М") {
            it2.setValue("Rolling Stones");
            qDebug() << it2.peekPrevious();
        }
    }

    /*
     * Итераторы в стиле STL
     * Указатели на элементы контейнера
    */
    QVector<QString> vec;
    vec << "In Extremo" << "Blackmore's Night" << "Cultus Ferox";
    // Можно использовать константные итераторы, например:
    // QVector<QString>::const_iterator it = vec.constBegin();
    QVector<QString>::iterator iter = vec.begin();
    // Преинкрементация - позволяет избежать на каждом витке цикла сохранения старого значения,
    // как скрытно осуществляется в инкрементации, и это делает цикл более эффективным.
    for (; iter != vec.end(); ++iter) {
        qDebug() << "Element:" << *iter;
    }

    // Эти итераторы можно использовать со стандартными алгоритмами STL
    std::sort(vec.begin(), vec.end());
    qDebug () << vec;

    // Итерация с помощью foreach (макрос)
    QList<QString> list3;
    list3 << "Subway to sally" << "Rammstein" << "After E'orever";
    foreach(QString str, list3) {
        // Копия
        qDebug() << "Element:" << str;
    }

    /*
     * Вектор - вставка и удаление, добавление в начало - медленные
     * Список - вставка и удаление - медленные
     * Двусвязный список - медленный доступ
     * Стек -  медленное добавление в начало
     * Очередь - медленная вставка/удаление
    */

    // Base64 - формат передачи бинарных данных в текстовой форме
    QByteArray arr = "Test Data";
    QByteArray aBase64 = arr.toBase64();
    qDebug() << aBase64;
    qDebug() << QByteArray::fromBase64(aBase64);

    /*
     * Мультисловарь - допускает дубликаты
     * Задание ключа с помощью [] может привести к созданию элемента (проверить с помощью contains)
    */

    // Сортировка
    // qSort(list);

    // Поиск
    // qFind(list.begin(), list.end(), "AnuЬis");

    // Сравнение контейнеров различных типов
    // qEqual(list.begin(), list.end(), vec.begin());

    // Копирование значений элементов
    // qCopy(list.begin(), list.end(), vec.begin());

    // Подсчет значений
    // qCount (list, "mantus", n);

    /*
     * Произвольный тип QVariant
    */
    QVariant v1(34);
    QVariant v2(true);
    qDebug() << QVariant::typeToName(v1.type());
    int number = v1.toInt() + 5;

    /*
     * Модель общего использования данных
    */
    QString str1; // Ссылается на shared null
    QString str2; // Ссылается на shared null
    str1 = "Новая строка"; //Ссылается на данные, счетчик ссылок = 1
    str2 = str1; // strl и str2 указывают на одни и те же данные, счетчик ссылок = 2
    str1 += " добавление"; // Производится копирование данных для str1, счетчик ссылок = 1 для обоих объектов

    return a.exec();
}
