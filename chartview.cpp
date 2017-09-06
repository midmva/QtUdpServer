#include "chartview.h"
#include <QtGui/QMouseEvent>
#include <QtCharts/QValueAxis>
#include <QDebug>

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
    picker_label = new QLabel(this);
    picker_label->setStyleSheet("QLabel { background-color : transparent; color : green; }");
    picker_label->setFixedSize(100,20);
    picker_label->setText("picker");
    picker_label->hide();
    timer = new QTimer(this);
    QObject::connect(timer,&QTimer::timeout,this,&ChartView::timeOut);
    timer->start(40);
}

ChartView::~ChartView()
{
    picker_label->deleteLater();
    timer->stop();
    timer->deleteLater();
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    if (event->button() == Qt::RightButton){
        if (chart()->isZoomed()){
            chart()->zoomReset();
            updateAxis();
        }
        return;
    }
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    //updateLabel();
    QChartView::mouseMoveEvent(event);
    updateAxis();
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart()->setAnimationOptions(QChart::NoAnimation);
    //updateLabel();
    if (event->button() == Qt::RightButton)
        return;

    QChartView::mouseReleaseEvent(event);
    updateAxis();
}

void ChartView::wheelEvent(QWheelEvent *event)
{


    if (event->delta()>0)
        chart()->zoom(2.0);
    else
        chart()->zoom(0.5);

    updateAxis();
    QChartView::wheelEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    case Qt::Key_Escape:
        chart()->zoomReset();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
    //updateLabel();
    updateAxis();
}

void ChartView::updateAxis()
{
    QValueAxis *axisX = (QValueAxis *)chart()->axisX();
    QValueAxis *axisY = (QValueAxis *)chart()->axisY();
    QPointF top_left = chart()->mapToValue(chart()->plotArea().topLeft());
    QPointF bottom_right = chart()->mapToValue(chart()->plotArea().bottomRight());
    axisX->setMin(top_left.x());
    axisX->setMax(bottom_right.x());
    axisY->setMax(top_left.y());
    axisY->setMin(bottom_right.y());
}

void ChartView::updateLabel()
{
    if (picker_label->isVisible()){
        qreal x = chart()->mapToValue(cursor().pos()).x();
        qreal y = chart()->mapToValue(cursor().pos()).y();
        picker_label->setText(QString("%1,%2").arg(x).arg(y));
        QPoint point = mapFromGlobal(cursor().pos());
        point+=QPoint(10,-15);
        picker_label->move(point);
    }
}

void ChartView::timeOut()
{
    if (geometry().contains(cursor().pos())&&picker_label->isHidden())
        picker_label->show();
    else if (!geometry().contains(cursor().pos())&&picker_label->isVisible())
        picker_label->hide();
    updateLabel();
}

