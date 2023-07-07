#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QCoreApplication::setApplicationName(QString("Calculator"));



    MainWindow w;

    w.setWindowTitle(QCoreApplication::applicationName());

    //w.setWindowIcon(QIcon("/171352_calculator_icon.png"));

    w.show();
    return a.exec();
}
