#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Компновока виджетов (layouts)
    */
    QWidget      wgt;

    QPushButton* pcmdA = new QPushButton("A");
    QPushButton* pcmdB = new QPushButton("B");
    QPushButton* pcmdC = new QPushButton("C");

    // Горизонтальное размещение слева направо
    QBoxLayout* pbxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    // Добавление кнопок в компановку
    pbxLayout->addWidget(pcmdA, 1);
    // Добавление фактора растяжения (stretch) между виджетами
    pbxLayout->addStretch(1);
    pbxLayout->addWidget(pcmdB, 2);
    pbxLayout->addWidget(pcmdC, 3);
    // Всем объектам (кнопки) присваивается предок wgt (не будет утечки памяти)
    wgt.setLayout(pbxLayout);

    // Порядок табуляции
    QWidget::setTabOrder(pcmdB, pcmdA);

    wgt.resize(450, 40);
    wgt.show();

    /*
     * Горизонтальное размещение
    */
    QWidget      wgt2;
    QPushButton* pcmdA2 = new QPushButton("A");
    QPushButton* pcmdB2 = new QPushButton("B");
    QPushButton* pcmdC2 = new QPushButton("C");

    QHBoxLayout* phbxLayout2 = new QHBoxLayout;
    // Толщина рамки (в пикселях)
    phbxLayout2->setContentsMargins(10, 10, 10, 10);
    // Расстояние между виджетами (в пикселях)
    phbxLayout2->setSpacing(20);
    phbxLayout2->addWidget(pcmdA2);
    phbxLayout2->addWidget(pcmdB2);
    phbxLayout2->addWidget(pcmdC2);
    wgt2.setLayout(phbxLayout2);

    wgt2.show();

    /*
     * Вложенные размещения
    */
    QWidget      wgt3;

    QPushButton* pcmdA3 = new QPushButton("A");
    QPushButton* pcmdB3 = new QPushButton("B");
    QPushButton* pcmdC3 = new QPushButton("C");
    QPushButton* pcmdD3 = new QPushButton("D");

    QHBoxLayout* phbxLayout3 = new QHBoxLayout;
    phbxLayout3->setContentsMargins(5, 5, 5, 5);
    phbxLayout3->setSpacing(15);
    phbxLayout3->addWidget(pcmdC3);
    phbxLayout3->addWidget(pcmdD3);

    QVBoxLayout* pvbxLayout3 = new QVBoxLayout;
    pvbxLayout3->setMargin(5);
    pvbxLayout3->setSpacing(15);
    pvbxLayout3->addWidget(pcmdA3);
    pvbxLayout3->addWidget(pcmdB3);
    // Горизонтальная компоновка в вертикальной компоновке
    pvbxLayout3->addLayout(phbxLayout3);
    wgt3.setLayout(pvbxLayout3);

    wgt3.show();

    /*
     * Табличное размещение GridLayout
    */
    // Для двух столбцов использовать QFormLayout
    QWidget      wgt4;

    QPushButton* pcmdA4 = new QPushButton("A");
    QPushButton* pcmdB4 = new QPushButton("B");
    QPushButton* pcmdC4 = new QPushButton("C");
    QPushButton* pcmdD4 = new QPushButton("D");

    QGridLayout* pgrdLayout = new QGridLayout;
    pgrdLayout->setContentsMargins(5, 5, 5, 5);
    pgrdLayout->setSpacing(15);
    pgrdLayout->addWidget(pcmdA4, 0, 0);
    pgrdLayout->addWidget(pcmdB4, 0, 1);
    pgrdLayout->addWidget(pcmdC4, 1, 0);
    pgrdLayout->addWidget(pcmdD4, 1, 1);
    wgt4.setLayout(pgrdLayout);

    wgt4.show();

    /*
     * Калькулятор
    */
    Calculator calculator;
    calculator.setWindowTitle("Calculator");
    calculator.resize(230, 200);
    calculator.show();

    /*
     * Сплиттер
    */
    QSplitter  spl(Qt::Vertical);
    QTextEdit* ptxt1 = new QTextEdit;
    QTextEdit* ptxt2 = new QTextEdit;
    spl.addWidget(ptxt1);
    spl.addWidget(ptxt2);

    ptxt1->setPlainText("Line1\n"
                        "Line2\n"
                        "Line3\n"
                        "Line4\n"
                        "Line5\n"
                        "Line6\n"
                        "Line7\n"
                       );
    ptxt2->setPlainText(ptxt1->toPlainText());

    spl.resize(200, 220);
    spl.show();

    return a.exec();
}
