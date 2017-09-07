#include "mainwindow.h"
#include "threadcalculate.h"
#include "threadreceiver.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qRegisterMetaType<Packet>("My");
    MainWindow w;
    w.show();

//    ThreadCalculate *thread = new ThreadCalculate();
//    thread->start(QThread::LowPriority);
//    thread->moveToThread(thread);

    //QObject::connect(thread,&ThreadCalculate::signalAddData,&w,&MainWindow::slotAddData,Qt::QueuedConnection);

    //QObject::connect(&w,&MainWindow::signalChangeSpeed,thread,&ThreadCalculate::slotChangeSpeed);

    ThreadReceiver *receiver = new ThreadReceiver();
    receiver->start(QThread::NormalPriority);
    receiver->moveToThread(receiver);

    QObject::connect(receiver,&ThreadReceiver::signalReceivePacket,&w,&MainWindow::slotReceiveUdpPacket,Qt::QueuedConnection);
    QObject::connect(&w,&MainWindow::signalStart,receiver,&ThreadReceiver::slotStartReceive);
    QObject::connect(&w,&MainWindow::signalStop,receiver,&ThreadReceiver::slotStopReceive);

    return a.exec();
}
