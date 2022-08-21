#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QtAwesome.h>
#include "logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtAwesome* awesome = new QtAwesome(qApp);
    awesome->initFontAwesome();

    QCoreApplication::setOrganizationName("MapleTracker");
    QCoreApplication::setApplicationName("MapleDailyTracker");

    Logger::init();
    auto logger = Logger::getLogger();

    QSettings settings;
    QString theme = settings.value("theme", "teal").toString();
    logger->info("Loading theme: {}", theme.toStdString());

    QFile styleFile(QString(":/styles/dark_%1.qss").arg(theme));
    styleFile.open(QFile::ReadOnly);

    QString style { styleFile.readAll() };
    a.setStyleSheet(style);

    MainWindow w;

    w.setWindowTitle("Maple Tracker");
    w.show();

    return a.exec();
}
