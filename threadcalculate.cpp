#include "threadcalculate.h"
#include <QDebug>
#include <QtCore/QtMath>

void ThreadCalculate::run()
{
    time = new QTime();

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&ThreadCalculate::timeOut);
    speed_ms = 40;
    list = new QList<QPointF>();
//    timer->start(100);
    exec();
}

ThreadCalculate::~ThreadCalculate()
{
    timer->stop();
    timer->deleteLater();
}

void ThreadCalculate::startTimer()
{
    timer->start(speed_ms);
    time->restart();
}

void ThreadCalculate::stopTimer()
{
    timer->stop();
}

void ThreadCalculate::changeSpeed(int speed)
{
    if (speed<1)return;
    speed_ms = speed;
    timer->setInterval(speed_ms);
}


void ThreadCalculate::timeOut()
{
    static int i = 0;
    //for (int j = 0; j<3; j++)
    QList<qreal> list_data;
    list_data.append((qreal)qSin(M_PI / 50 * (i)) * 100);
    list_data.append((qreal)qCos(M_PI / 50 * (i++)) * 100);
    list_data.append((qreal)qCos(M_PI / 50 * (i++)+M_PI/4) * 100);
    list_data.append((qreal)qCos(M_PI / 50 * (i++)+3*M_PI/4) * 100);
    emit addData(time->elapsed()*0.001,list_data);
//        emit addPoint(QPointF((qreal)time->elapsed()/1000,(qreal)qSin(M_PI / 50 * (++i)) * 100));
}
