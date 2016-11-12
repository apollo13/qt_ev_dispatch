#include "mainwindow.h"
#include "eventdispatcher.h"

#include <QApplication>
#include <QAbstractEventDispatcher>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::setEventDispatcher(new EventDispatcher);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
