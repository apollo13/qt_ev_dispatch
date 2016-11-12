#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventdispatcher.h"

#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QAbstractEventDispatcher>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->disable_input, &QPushButton::clicked, [this]() {
        EventDispatcher::instance()->enableUserInput(false, false);
        qDebug() << QTime::currentTime().toString() << "disable user input";
        QTimer::singleShot(5000, [this]() {
           qDebug() << QTime::currentTime().toString() << "timer done";
           EventDispatcher::instance()->enableUserInput(true, false);
           qDebug() << QTime::currentTime().toString() << "enable user input";
        });
    });

    connect(ui->test, &QPushButton::clicked, [this]() {
        qDebug() << QTime::currentTime().toString() << "clicked" << this->counter;
        this->counter++;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
