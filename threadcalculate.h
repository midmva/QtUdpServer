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
    void slotStartTimer();
    void slotStopTimer();
    void slotChangeSpeed(int speed);

private:
    QTimer *timer;
    QTime *time;
    int speed_ms;
    QList<QPointF> *list;

private slots:
    void slotTimeOut();

signals:
    void signalAddPoint(const QPointF point);
    void signalAddData(const qreal time, const QList<qreal> list_data);
    void signalAddList(const QList<QPointF> l);


};

#endif // THREADCALCULATE_H
