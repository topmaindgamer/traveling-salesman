#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Traveling Salesman Problem");
    w.setWindowIcon(QIcon("C:/Users/savvi/Documents/ic.jpg"));
    return a.exec();
}
