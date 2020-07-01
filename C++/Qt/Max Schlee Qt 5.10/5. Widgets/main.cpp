#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget wgt;

    /*
     * Установка фона виджета
    */
    QWidget* pwgt1 = new QWidget(&wgt);
    // Объект палитры
    QPalette pal1;
    pal1.setColor(pwgt1->backgroundRole(), Qt::blue);
    pwgt1->setPalette(pal1);
    pwgt1->resize(100, 100);
    pwgt1->move(25, 25);
    // Заполнение фона виджета
    pwgt1->setAutoFillBackground(true);

    /*
    QWidget* pwgt2 = new QWidget(&wgt);
    QPalette pal2;
    pal2.setBrush(pwgt2->backgroundRole(), QBrush(QPixmap("C:\\Users\\gogds\\Study\\C++\\Qt\\Max Schlee Qt 5.10\\5. Widgets\\stone.jpg")));
    pwgt2->setPalette(pal2);
    pwgt2->resize(100, 100);
    pwgt2->move(75, 75);
    pwgt2->setAutoFillBackground(true);
    */


    /*
     * Установка кастомного курсора
    */
    /*
    QPixmap pix("C:\\Users\\gogds\\Study\\C++\\Qt\\Max Schlee Qt 5.10\\5. Widgets\\clock.png");
    QCursor cur(pix);
    wgt.setCursor(cur);
    */

    wgt.resize(200, 200);
    wgt.show();

    /*
     * Установка указателя мыши для всего приложения (например, момент  загрузки)
    */
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    Sleep(1500);
    QGuiApplication::restoreOverrideCursor();

    /*
     * Виджет рамки
    */
    QFrame* pfnn = new QFrame;
    // Стиль рамки
    pfnn->setFrameStyle(QFrame::Box | QFrame::Sunken);
    // Толщина
    pfnn->setLineWidth(3);
    pfnn->show();

    /*
     * Виджет видовой прокрутки
    */
    QScrollArea sa;
    // Прокрутка будет видна всегда
    sa.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    sa.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    /*
     * Пример использования виджета видовой прокрутки
    */
    // Обычный виджет
    QWidget* pwgt3 = new QWidget;
    // Объект растрового изображения
    QPixmap pix ("C:\\Users\\gogds\\Study\\C++\\Qt\\Max Schlee Qt 5.10\\5. Widgets\\img.jpg");
    QPalette pal3;
    pal3.setBrush(pwgt3->backgroundRole(), QBrush(pix));
    // Фон виджета
    pwgt3->setPalette(pal3);
    pwgt3->setAutoFillBackground(true);
    pwgt3->setFixedSize(pix.width(), pix.height());

    // pwgt3 становится потомкой виджета sa
    sa.setWidget(pwgt3);
    sa.resize(350, 150);
    sa.show();

    return a.exec();
}
