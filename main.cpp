
#include <QApplication>
#include "Board.h"
#include <QPushButton>
#include <QMessageBox>
#include "Network.h"

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     QMessageBox::StandardButton rt;  //注意这里有两个StandarButton,选下边一个
     bool mess=false;
     rt=QMessageBox::question(NULL,"server or client","作为服务器启动");
     if(rt==QMessageBox::Yes)
     {
         mess=true;
     }

     Network wk(mess);
     wk.show();

    return a.exec();
}
