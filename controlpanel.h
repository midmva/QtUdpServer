#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H


#include "controlchannel.h"
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0, QList<ChannelSettings> *list = nullptr);
    ~ControlPanel();

private slots:
    void updateLabel(int number);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();


private:
    int speed_ms;
    Ui::ControlPanel *ui;


signals:
    void start();
    void stop();
    void changeSpeed(int speed);
    void changeSettings(const QString object_name, const ChannelSettings settings);
};

#endif // CONTROLPANEL_H
