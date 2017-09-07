#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chart.h"
#include "chartview.h"
#include "controlchannel.h"
#include "threadreceiver.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include <QTime>
#include <QSettings>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotAddPoint(const QPointF point);
    void slotAddList(const QList<QPointF> l);
    void slotAddData(const qreal time, const QList<qreal> list_data);
    void slotReceiveUdpPacket(const Packet &packet);

private:
    qreal time_screen;
    QTimer *timer;
    QTime *time;
    Ui::MainWindow *ui;
    QLineSeries *series[8];
    QList<QPointF> *list_point[8];
    ChartView *chartView;
    qreal maxY;
    qreal minY;
    QSettings *settings;

private slots:
    void slotTimeOut();
    void slotStartShow();
    void slotStopShow();
    void slotSetTimeScreen(int value);
    void slotChangeChannelSettings(const QString object_name, const ChannelSettings settings);
    void slotSetSettings();
    void slotGetSettings(QList<ChannelSettings> &list);

signals:
    void signalStart();
    void signalStop();
    void signalChangeSpeed(int speed);
};

#endif // MAINWINDOW_H
