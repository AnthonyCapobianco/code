#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPushButton *button = new QPushButton("This is an example");
    button->show();

    w.show();

    return a.exec();
}
