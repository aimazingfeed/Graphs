#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Graphs");
    w.setFixedSize(1205,625);
    w.show();
    return a.exec();
}
