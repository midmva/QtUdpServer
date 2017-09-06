#ifndef THREADCALCULATE_H
#define THREADCALCULATE_H

#include <QThread>
#include <QTimer>
#include <QTime>
#include <QList>
#include <QPointF>




class ThreadCalculate : public QThread
{

    Q_OBJECT
public:
    void run();
    ~ThreadCalculate();

public slots:
    void startTimer();
    void stopTimer();
    void changeSpeed(int speed);

private:
    QTimer *timer;
    QTime *time;
    int speed_ms;
    QList<QPointF> *list;

private slots:
    void timeOut();

signals:
    void addPoint(const QPointF point);
    void addData(const qreal time, const QList<qreal> list_data);
    void addList(const QList<QPointF> l);


};

#endif // THREADCALCULATE_H
