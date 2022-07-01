#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("MapleTracker");
    QCoreApplication::setApplicationName("MapleDailyTracker");

    QSettings settings;
    QString theme = settings.value("theme", "teal").toString();

    QFile styleFile(QString(":/styles/dark_%1.qss").arg(theme));
    styleFile.open(QFile::ReadOnly);

    QString style { styleFile.readAll() };
    a.setStyleSheet(style);

    MainWindow w;

    w.setWindowTitle("Maple Tracker");
    w.show();

    return a.exec();
}
