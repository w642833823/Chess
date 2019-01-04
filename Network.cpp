#include "Network.h"
#include <QDebug>
Network::Network(bool mess)
{
     server=NULL;
     socket=NULL;
     qDebug()<<"连接1!";
     if(mess)
     {
         qDebug()<<"连接2!";
         server=new QTcpServer(this);
         server->listen(QHostAddress::Any,9999);
         connect(server,SIGNAL(newConnection()),this,SLOT(st1()));
     }
     else {
         qDebug()<<"连接3!";
         socket=new QTcpSocket(this);
         socket->connectToHost(QHostAddress("127.0.0.1"),127);
     }
}
void Network::st1()
{
    if(socket)return ;
    qDebug()<<"连接4!";
    socket=server->nextPendingConnection();
    qDebug()<<"连接5!";
}
