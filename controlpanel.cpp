#include "controlpanel.h"
#include "ui_controlpanel.h"

#include <QColorDialog>

ControlPanel::ControlPanel(QWidget *parent,QList<ChannelSettings> *list) :
    QWidget(parent),
    speed_ms(40),
    ui(new Ui::ControlPanel)

{
    ui->setupUi(this);
    ui->label->setText(QString("Time/screen, %1s").arg(ui->horizontalSlider->value()*0.1));
    setFixedWidth(200);
    setLayout(ui->verticalLayout);
    ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    if (list!=nullptr)
        for (int i = 0;i<8;i++){
            ControlChannel *control = new ControlChannel(this,list->at(i).enable,
                                                         list->at(i).color,
                                                         list->at(i).name);
            connect(control, &ControlChannel::signalChangeChannelSettings,this, &ControlPanel::signalChangeSettings);
            ui->verticalLayout->addWidget(control);
        }
    ui->verticalLayout->addStretch();
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::slotUpdateLabel(int number)
{
}

void ControlPanel::on_pushButton_clicked()
{
    if (ui->pushButton->text().contains("Start")){
        ui->pushButton->setText("Stop");
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        emit signalStart();
    }
    else{
        ui->pushButton->setText("Start");
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        emit signalStop();
    }
}

void ControlPanel::on_horizontalSlider_valueChanged(int value)
{
    ui->label->setText(QString("Time/screen, %1s").arg(value*0.1));
    emit signalChangeSpeed(value);
}
