#include "controlchannel.h"
#include "ui_controlchannel.h"
#include <QMouseEvent>
#include <QInputDialog>
#include <QColorDialog>
#include <QDebug>

ControlChannel::ControlChannel(QWidget *parent, bool enable, QString color, QString name):
    QWidget(parent),
    ui(new Ui::ControlChannel)
{
    ui->setupUi(this);
    setLayout(ui->horizontalLayout);
    ui->enable_ch->setChecked(enable);
    ui->color_ch->setStyleSheet(QString("QLabel { background-color: %1 }").arg(color));
    ui->name_ch->setText(name);
    settings.enable = enable;
    settings.color = color;
    settings.name = name;
    setObjectName(name);
}

ChannelSettings ControlChannel::getSettings() const
{
    return settings;
}

ControlChannel::~ControlChannel()
{
    delete ui;
}

void ControlChannel::on_change_name_button_clicked()
{
    bool ok;
    QString new_name = QInputDialog::getText(this,"Change name","Input new channel name here",QLineEdit::Normal,ui->name_ch->text(),&ok);
    if (!ok || new_name.isEmpty())return;
    ui->name_ch->setText(new_name);
    settings.name = new_name;
}

void ControlChannel::mousePressEvent(QMouseEvent *event)
{
    if (ui->color_ch->geometry().contains(event->pos())){
        QColor color(QColorDialog::getColor(ui->color_ch->palette().background().color(),this,"Choose the color of curve"));
        settings.color = color.name();
        ui->color_ch->setStyleSheet(QString("QLabel { background-color: %1 }").arg(settings.color));
        emit signalChangeChannelSettings(objectName(),settings);
    }
}

void ControlChannel::on_enable_ch_clicked(bool checked)
{
    settings.enable = checked;
    emit signalChangeChannelSettings(objectName(),settings);
}
