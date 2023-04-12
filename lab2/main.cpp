#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("Dream Team");
    QApplication::setApplicationName("lab2");
    MainWindow w;
    w.show();
    return a.exec();
}
