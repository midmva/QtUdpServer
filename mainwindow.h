#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chart.h"
#include "chartview.h"
#include "controlchannel.h"
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
    void addPoint(const QPointF point);
    void addList(const QList<QPointF> l);
    void addData(const qreal time, const QList<qreal> list_data);

private:
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
    void timeOut();
    void startShow();
    void stopShow();
    void changeChannelSettings(const QString object_name, const ChannelSettings settings);
    void setSettings();
    void getSettings(QList<ChannelSettings> &list);

signals:
    void start();
    void stop();
    void changeSpeed(int speed);
};

#endif // MAINWINDOW_H
