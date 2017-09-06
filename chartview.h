#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QTimer>
#include <QLabel>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    ~ChartView();

protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QTimer *timer;
    bool m_isTouching;
    QLabel *picker_label;

private slots:
    void updateAxis();
    void updateLabel();
    void timeOut();
};

#endif
