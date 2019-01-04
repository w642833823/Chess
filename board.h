#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
//#include <QMouseEvent>
#include "stone.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent*);  //painter
    void drawStone(QPainter&painter,int id);  //画棋子棋盘
    QPoint center(int hang,int lie);//返回棋子像素坐标
    QPoint center(int id);
   // virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    bool getHL(QPoint pt,int &hang,int &lie);
    bool canMove(int moveid,int hang,int lie,int killid);
    bool canMove1(int moveid,int hang,int lie,int killid);
    bool canMove2(int moveid,int hang,int lie,int killid);
    bool canMove3(int moveid,int hang,int lie,int killid);
    bool canMove4(int moveid,int hang,int lie,int killid);
    bool canMove5(int moveid,int hang,int lie,int killid);
    bool canMove6(int moveid,int hang,int lie,int killid);
    bool canMove7(int moveid,int hang,int lie,int killid);
    bool isIn(int hang,int lie);
    Stone _s[32];
    int _r;  //棋子半径
    int seclected;
    bool turn;    //轮到谁走
signals:

public slots:
};

#endif // BOARD_H
