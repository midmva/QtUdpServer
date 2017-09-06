#include "mainwindow.h"
#include "threadcalculate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ThreadCalculate *thread = new ThreadCalculate();
    thread->start(QThread::LowPriority);
    thread->moveToThread(thread);

//    QObject::connect(thread,&ThreadCalculate::addPoint,&w,&MainWindow::addPoint,Qt::QueuedConnection);
//    QObject::connect(thread,&ThreadCalculate::addList,&w,&MainWindow::addList,Qt::QueuedConnection);
    QObject::connect(thread,&ThreadCalculate::addData,&w,&MainWindow::addData,Qt::QueuedConnection);
    QObject::connect(&w,&MainWindow::start,thread,&ThreadCalculate::startTimer);
    QObject::connect(&w,&MainWindow::stop,thread,&ThreadCalculate::stopTimer);

    QObject::connect(&w,&MainWindow::changeSpeed,thread,&ThreadCalculate::changeSpeed);

    return a.exec();
}
