#include "threadreceiver.h"
#include <QDebug>

void ThreadReceiver::run()
{

    memset(reinterpret_cast<void *>(&packet),0,sizeof(Packet));
    time_start_ms = 0;
    udp_client = new QUdpSocket(this);
    //udp_client->bind(48660);

    QObject::connect(udp_client,&QUdpSocket::readyRead,this,&ThreadReceiver::slotReceiveDatagramm);
    exec();
}

ThreadReceiver::~ThreadReceiver()
{
    udp_client->deleteLater();
}

void ThreadReceiver::slotStartReceive()
{
    udp_client->bind(48660);
    time_start_ms = 0;
}

void ThreadReceiver::slotStopReceive()
{
        udp_client->abort();
}

void ThreadReceiver::slotReceiveDatagramm()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(udp_client->pendingDatagramSize());
        udp_client->readDatagram(baDatagram.data(), baDatagram.size());
    }
    while(udp_client->hasPendingDatagrams());

    memcpy(reinterpret_cast<void*>(&packet),reinterpret_cast<const void*>(baDatagram.data()),sizeof(Packet));
    if (!time_start_ms)
        time_start_ms = packet.time_ms;
    packet.time_ms-=time_start_ms;
    emit signalReceivePacket(packet);
}
