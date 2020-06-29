#include <QCoreApplication>
#include "QFile"
#include "QDateTime"
#include "QTextStream"
#include "QtGlobal"
#include "QDebug"
#include "QLibraryInfo"

void messageToFile(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QFile file("protocol.log");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QString strDateTime = QDateTime::currentDateTime().toString("dd.ММ.yy-hh:mm");
    QTextStream out(&file);
    switch (type) {
    case QtDebugMsg:
        out << strDateTime << "Debug: " << msg << ", " << context.file << Qt::endl;
        break;
    case QtWarningMsg:
        out << strDateTime << "Warning: " << msg << ", " << context.file << Qt::endl;
        break;
    case QtCriticalMsg:
        out << strDateTime << "Critical: " << msg << ", " << context.file << Qt::endl;
        break;
    case QtFatalMsg:
        out << strDateTime << "Fatal: " << msg << ", " << context. file << Qt::endl;
        abort ();
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
     * Структура проекта Qt - помимо
     * файлов исходного кода на языке С++ обычно имеется файл проекта с расширением
     * рго. Из него вызовом утилиты qmake и создается mаkе-файл. Этот mаkе-файл содержит
     * в себе все необходимые инструкции для создания готового исполняемого модуля (рис. 3.3).
     * В mаkе-файле содержится вызов МОС для создания дополнительного кода С++ и необходимых
     * заголовочных файлов. Если проект содержит qrс-файл, то будет также создан файл
     * С++, содержащий данные ресурсов. После этого все исходные файлы компилируются С++компилятором
     * в файлы объектного кода, которые объединяются компоновщиком link в готовый
     * исполняемый модуль.
    */

    /*
    // Перенаправление лога в файл
    qInstallMessageHandler(messageToFile);
    qDebug() << "main test log";
    // Вернуть обратно
    qInstallMessageHandler(0);
    qDebug() << "main test";
    */

    qDebug() << "License Products:"
             << QLibraryInfo::licensedProducts();
    qDebug() << "Licensee: "
             << QLibraryInfo::licensee();
    qDebug() << "Is Debug Build:"
             << QLibraryInfo::isDebugBuild();
    qDebug() << "Locations";
    qDebug() << " Headers:"
             << QLibraryInfo::location(QLibraryInfo::HeadersPath);
    qDebug() << " Libraries:"
             << QLibraryInfo::location(QLibraryInfo::LibrariesPath);
    qDebug() << " Binaries:"
             << QLibraryInfo::location(QLibraryInfo::BinariesPath);
    qDebug() << " Prefix:"
             << QLibraryInfo::location(QLibraryInfo::PrefixPath);
    qDebug() << " Documentation: "
             << QLibraryInfo::location(QLibraryInfo::DocumentationPath);
    qDebug() << " Plugins:"
             << QLibraryInfo::location(QLibraryInfo::PluginsPath);
    qDebug() <<" Data:"
             << QLibraryInfo::location(QLibraryInfo::DataPath);
    qDebug() << " Settings:"
             << QLibraryInfo::location(QLibraryInfo::SettingsPath);
    qDebug() << " Examples:"
             << QLibraryInfo::location(QLibraryInfo::ExamplesPath);

    return a.exec();
}
