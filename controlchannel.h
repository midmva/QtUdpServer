#ifndef CONTROLCHANNEL_H
#define CONTROLCHANNEL_H

#include <QWidget>

namespace Ui {
class ControlChannel;
}
struct ChannelSettings{
    bool enable;
    QString color;
    QString name;
};

class ControlChannel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlChannel(QWidget *parent = 0,bool enable = true,QString color = QColor(Qt::white).name(),QString name = "channel");
    ChannelSettings getSettings() const;
    ~ControlChannel();

private slots:
    void on_change_name_button_clicked();

    void on_enable_ch_clicked(bool checked);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::ControlChannel *ui;
    ChannelSettings settings;

signals:
    void changeChannelSettings(const QString object_name, const ChannelSettings settings);

};

#endif // CONTROLCHANNEL_H
