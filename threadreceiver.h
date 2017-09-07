#ifndef THREADRECEIVER_H
#define THREADRECEIVER_H

#include <QThread>
#include <QUdpSocket>
#include <QMetaType>

typedef struct {
    int time_ms;
    qreal value_ch[8];
}__attribute__((packed, aligned(4))) Packet;

Q_DECLARE_METATYPE(Packet);

class ThreadReceiver : public QThread
{
    Q_OBJECT
public:
    void run();
    ~ThreadReceiver();

public slots:
    void slotStartReceive();
    void slotStopReceive();

private slots:
    void slotReceiveDatagramm();

private:
    QUdpSocket *udp_client;
    int time_start_ms;
    Packet packet;

signals:
    void signalReceivePacket(const Packet &packet);
};

#endif // THREADRECEIVER_H
