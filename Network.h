#ifndef NETWORK_H
#define NETWORK_H
#include "board.h"
#include <QTcpServer>
#include <QTcpSocket>
class Network:  public Board
{
  Q_OBJECT
public:
    Network(bool mess);

    QTcpServer* server;
    QTcpSocket* socket;
private slots:
    void st1();

};

#endif // NETWORK_H
