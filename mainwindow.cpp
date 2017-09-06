#include "mainwindow.h"
#include "controlpanel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    maxY(0),minY(0)
{
    ui->setupUi(this);
    for (int i = 0; i<8;i++){
        series[i] = new QLineSeries();
        list_point[i] = new QList<QPointF>();
    }


    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::timeOut);
    timer->start(40);

    Chart *chart = new Chart();
    for (int i = 0; i<8;i++)
        chart->addSeries(series[i]);
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->legend()->hide();
    chart->createDefaultAxes();


    // Get axis pointers
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    chart->setAxisX(axisX,series[0]);
    chart->setAxisY(axisY,series[0]);
    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(Qt::lightGray);
    axisPen.setWidth(1);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::darkGray);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and minor grid lines
    axisX->setGridLineVisible(true);
    axisY->setGridLineVisible(true);
    axisPen.setStyle(Qt::DashLine);
    axisPen.setColor(QColor(75,75,75));
    axisX->setGridLinePen(axisPen);
    axisY->setGridLinePen(axisPen);
    axisPen.setStyle(Qt::DotLine);
    axisPen.setColor(QColor(70,70,70));
    axisX->setMinorGridLinePen(axisPen);
    axisY->setMinorGridLinePen(axisPen);
    axisX->setTickCount(11);
    axisY->setTickCount(7);
    axisX->setMinorTickCount(9);
    axisY->setMinorTickCount(9);

    // Customize background
    QLinearGradient gradient(QPointF(0,0),QPointF(0,1));
    gradient.setColorAt(1.0,Qt::black);
    gradient.setColorAt(0.0,QColor(35,35,35));
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(gradient);

    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::green);
    pen.setWidth(2);
    series[0]->setPen(pen);
    pen.setColor(Qt::red);
    series[1]->setPen(pen);
    pen.setColor(Qt::blue);
    series[2]->setPen(pen);
    pen.setColor(Qt::cyan);
    series[3]->setPen(pen);

    pen.setColor(Qt::black);
    chart->setBackgroundPen(pen);

    ControlPanel *control = new ControlPanel(this);

    ui->centralWidget->setLayout(ui->horizontalLayout);
    ui->horizontalLayout->addWidget(control);
    ui->horizontalLayout->addWidget(chartView);

    QObject::connect(control,&ControlPanel::start,this,&MainWindow::startShow);
    QObject::connect(control,&ControlPanel::stop,this,&MainWindow::stopShow);
    QObject::connect(control,&ControlPanel::changeSpeed,this,&MainWindow::changeSpeed);

    //setCentralWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(const QPointF point)
{
    list_point[0]->append(point);
}

void MainWindow::addList(const QList<QPointF> l)
{
    QPointF p;
    for (int i = 0; i<l.count(); i++){
        p = l.at(i);
        //series->append(p.x(),p.y());
    }
    series[0]->append(l.mid(10));
    chartView->chart()->axisX()->setMax(l.last().x());
}

void MainWindow::addData(const qreal time, const QList<qreal> list_data)
{
    QPointF p(time,0.0);
    for (int i = 0; i<list_data.count();i++){
        p.setY(list_data.at(i));
        list_point[i]->append(p);
    }
}

void MainWindow::timeOut()
{
    if (!list_point[0]->count())return;
    chartView->chart()->axisX()->setMax(list_point[0]->last().x());
    qreal time_min = list_point[0]->last().x()-10.0;
    int index = list_point[0]->count()-1;
    for (;index!=0;index--){
        if (maxY<list_point[0]->at(index).y())
            maxY=list_point[0]->at(index).y();
        if (minY>list_point[0]->at(index).y())
            minY=list_point[0]->at(index).y();
        if (list_point[0]->at(index).x()<=time_min){
            break;
        }
    }
    for (int i =0; i<8;i++){
        if (list_point[i]->isEmpty())continue;
        chartView->chart()->removeSeries(series[i]);
        series[i]->clear();
        if (list_point[0]->last().x()>10.0){
            if (!list_point[i]->count())continue;
            series[i]->append(list_point[i]->mid(index));
            if (!i)chartView->chart()->axisX()->setMin(list_point[i]->last().x()-10.0);
        }
        else{
           series[i]->append(list_point[i]->mid(0));
        }
        chartView->chart()->addSeries(series[i]);
    }



//    if (list_point->last().x()>10.0){
//        series->append(list_point->mid(index));
//        chartView->chart()->axisX()->setMin(list_point->last().x()-10.0);
//    }
//    else{
//       series->append(list_point->mid(0));
//    }

    chartView->chart()->axisY()->setMax(maxY);
    chartView->chart()->axisY()->setMin(minY);

}

void MainWindow::startShow()
{
    for (int i = 0; i<8;i++)
        series[i]->clear();
    minY = maxY = 0;
    chartView->chart()->axisX()->setMax(0.0);
    timer->start(40);
    emit start();
}

void MainWindow::stopShow()
{
    emit stop();
    timer->stop();
    chartView->chart()->axisX()->setMax(list_point[0]->last().x());
    for (int i = 0; i<8;i++){
        if (list_point[i]->isEmpty())continue;
        chartView->chart()->removeSeries(series[i]);
        series[i]->clear();
        series[i]->append(list_point[i]->mid(0));
        chartView->chart()->addSeries(series[i]);
        list_point[i]->clear();
    }
    chartView->chart()->axisX()->setMin(0.0);

    chartView->chart()->axisY()->setMax(maxY);
    chartView->chart()->axisY()->setMin(minY);

}
