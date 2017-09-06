#include "controlpanel.h"
#include "ui_controlpanel.h"

#include <QColorDialog>

ControlPanel::ControlPanel(QWidget *parent,QList<ChannelSettings> *list) :
    QWidget(parent),
    speed_ms(40),
    ui(new Ui::ControlPanel)

{
    //TODO color settings
    ui->setupUi(this);
    setFixedWidth(200);
    setLayout(ui->verticalLayout);
    ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->timeout_label->setText(QString("Timeout: %1ms").arg(speed_ms));
    if (list!=nullptr)
        for (int i = 0;i<8;i++){
            ControlChannel *control = new ControlChannel(this,list->at(i).enable,
                                                         list->at(i).color,
                                                         list->at(i).name);
            connect(control, &ControlChannel::changeChannelSettings,this, &ControlPanel::changeSettings);
            ui->verticalLayout->addWidget(control);
        }
    ui->verticalLayout->addStretch();
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::updateLabel(int number)
{
    ui->timeout_label->setText(QString("Timeout: %1ms").arg(number));
}

void ControlPanel::on_pushButton_clicked()
{
    if (ui->pushButton->text().contains("Start")){
        ui->pushButton->setText("Stop");
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
        emit start();
    }
    else{
        ui->pushButton->setText("Start");
        ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        emit stop();
    }
}

void ControlPanel::on_pushButton_2_clicked()
{
    speed_ms-=10;
    updateLabel(speed_ms);
    emit changeSpeed(speed_ms);
}

void ControlPanel::on_pushButton_3_clicked()
{
    speed_ms+=10;
    updateLabel(speed_ms);
    emit changeSpeed(speed_ms);
}

void ControlPanel::on_pushButton_5_clicked()
{
    speed_ms+=1;
    updateLabel(speed_ms);
    emit changeSpeed(speed_ms);
}

void ControlPanel::on_pushButton_4_clicked()
{
    speed_ms-=1;
    updateLabel(speed_ms);
    emit changeSpeed(speed_ms);
}


