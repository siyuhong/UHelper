#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("UHelper");
    w.show();

    //Start Message&Even loop
    return a.exec();
}
