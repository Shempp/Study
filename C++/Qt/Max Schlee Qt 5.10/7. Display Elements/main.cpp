#include <QApplication>
#include <QtWidgets>
#include "Progress.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Label с HTML5
    */
    QLabel lbl("<H1><CENTER>QLabel - HTML Demo</CENTER></H1>"
               "<H2><CENTER>List</CENTER><H2>"
               "<OL><LI>One</LI>"
               "    <LI>Two</LI>"
               "    <LI>Three</LI>"
               "</OL>"
               "<H2><CENTER>Font Style</CENTER><H2>"
               "<CENTER><FONT COLOR=RED>"
               "    <B>Bold</B>, <I>Italic</I>, <U>Underline</U>"
               "</FONT></CENTER>"
               "<H2><CENTER>Table</CENTER></H2>"
               "<CENTER> <TABLE>"
               "    <TR BGCOLOR=#ff00ff>"
               "        <TD>1,1</TD><TD>1,2</TD><TD>1,3</TD><TD>1,4</TD>"
               "    </TR>"
               "    <TR BGCOLOR=YELLOW>"
               "        <TD>2,1</TD><TD>2,2</TD><TD>2,3</TD><TD>2,4</TD>"
               "    </TR>"
               "    <TR BGCOLOR=#00f000>"
               "        <TD>3,1</TD><TD>3,2</TD><TD>3,3</TD><TD>3,4</TD>"
               "    </TR>"
               "</TABLE> </CENTER>"
              );

    lbl.show();

    /*
     * Если текст надписи содержит знак & (амперсанд), то символ, перед которым он
     * стоит, будет подчеркнутым. При нажатии клавиши этого символа совместно с клавишей\
     * <Alt> фокус перейдет к виджету, установленному методом setBuddy()
    */
    QWidget    wgt;
    QLabel*    plblName = new QLabel("&Name:");
    QLineEdit* ptxtName = new QLineEdit;
    // Связь label с полем ввода
    plblName->setBuddy(ptxtName);

    QLabel*    plblAge = new QLabel("&Age:");
    QSpinBox*  pspbAge = new QSpinBox;
    // Связь label со спинбоксом
    plblAge->setBuddy(pspbAge);

    // Layout
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(plblName);
    pvbxLayout->addWidget(ptxtName);
    pvbxLayout->addWidget(plblAge);
    pvbxLayout->addWidget(pspbAge);
    wgt.setLayout(pvbxLayout);

    wgt.show();

    /*
     * Вызов HTML страницы
    */
    QLabel* plblHTML = new QLabel("<A HREF=\"http://qt-book.com\"> qt-book.com </А>");
    plblHTML->setOpenExternalLinks(true);
    plblHTML->show();

    /*
     * Пример работы прогресс бара
    */
    Progress progress;
    progress.show();

    /*
     * Электронный индикатор
    */
    QWidget     wgt2;
    QLCDNumber* plcd = new QLCDNumber;
    QSpinBox*   pspb = new QSpinBox;

    plcd->setSegmentStyle(QLCDNumber::Filled);
    plcd->setMode(QLCDNumber::Hex);

    pspb->setFixedHeight(30);

    QObject::connect(pspb, SIGNAL(valueChanged(int)), plcd, SLOT(display(int)));

    //Layout setup
    QVBoxLayout* pvbxLayout2 = new QVBoxLayout;
    pvbxLayout2->addWidget(plcd);
    pvbxLayout2->addWidget(pspb);
    wgt2.setLayout(pvbxLayout2);

    wgt2.resize(250, 150);
    wgt2.show();

    return a.exec();
}
