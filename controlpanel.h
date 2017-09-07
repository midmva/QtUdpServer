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
    void slotUpdateLabel(int number);
    void on_pushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);

private:
    int speed_ms;
    Ui::ControlPanel *ui;


signals:
    void signalStart();
    void signalStop();
    void signalChangeSpeed(int speed);
    void signalChangeSettings(const QString object_name, const ChannelSettings settings);
};

#endif // CONTROLPANEL_H
