#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Maple Tracker");
    w.show();

    QFile styleFile(":/styles/dark_teal.qss");
    styleFile.open(QFile::ReadOnly);

    QString style { styleFile.readAll() };
    a.setStyleSheet(style);

    return a.exec();
}
