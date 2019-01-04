#include "board.h"
#include <QMouseEvent>
#include<QDebug>
Board::Board(QWidget *parent) : QWidget(parent)
{
   for(int i=0;i<32;i++)
   {
          _s[i].init(i);
   }
   seclected=-1;
   turn=true;

}
QPoint Board::center(int hang,int lie)
{
    QPoint ret;
    ret.rx() = (1+lie)*_r*2;
    ret.ry() = (1+hang)*_r*2;

    return ret;
}
QPoint Board::center(int id)
{
    return center(_s[id].hang,_s[id].lie);
}
void Board::drawStone(QPainter& painter,int id)//绘制棋子名字
{
    if(_s[id]._dead)
        return ;

    QPoint c=center(id);
    QRect rect(c.x()-_r,c.y()-_r,_r*2,_r*2);
    if(id==seclected)
        painter.setBrush(QBrush(Qt::gray));
    else
    painter.setBrush(QBrush(Qt::yellow));

    painter.setPen(Qt::black);
    painter.drawEllipse(center(id),_r,_r);
   if(_s[id]._red)
   {
       painter.setPen(Qt::red);
   }
   painter.setFont(QFont("system",_r,700));
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}
void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //画10条直线
    int d=60;
      _r=d/2;
    //10横线
    for(int i=1;i<=10;i++)
    {
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }
    //画10竖线
    for(int i=1;i<=9;i++)
    {
        if(i==1||i==9)
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        }
        else {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }
    //画9宫格
    painter.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));
    //绘制棋子
    for(int i=0;i<32;i++)
    {
        drawStone(painter,i);
    }
}
bool Board::getHL(QPoint pt,int &hang,int &lie)//
{
    for(hang=0;hang<=9;hang++)
        for(lie=0;lie<=8;lie++)
        {
            QPoint c=center(hang,lie);
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int jl=dx*dx+dy*dy;
            if(jl<_r*_r)
                return true;
        }
    return false;
}
bool Board::canMove(int moveid,int hang,int lie,int killid)
{
    qDebug()<<"进入move函数";
    if(_s[moveid]._red==_s[killid]._red&&killid!=-1)
    {
        qDebug()<<"进入if!";
      seclected=killid;
      update();

    return false;
    }
    qDebug()<<"switch";
    switch(_s[moveid]._type)
    {
     case Stone::CHE:
          return canMove1(moveid,hang,lie,killid);break;
     case Stone::MA:
         return canMove2(moveid, hang, lie,killid);break;
     case Stone::PAO:
          return canMove3(moveid,hang,lie, killid);break;
     case Stone::BING:
         return canMove4(moveid, hang, lie, killid);break;
     case Stone::JIANG:
         return canMove5(moveid,hang,lie, killid);break;
     case Stone::SHI:
        return  canMove6(moveid, hang, lie, killid);break;
     case Stone::XIANG:
        return  canMove7(moveid,hang,lie,killid);break;
     default:qDebug()<<"错误！";
    }
     return true;
}
bool Board::canMove1(int moveid,int hang,int lie,int killid)
{
    qDebug()<<"进入move1函数";
    int dh=_s[moveid].hang-hang;
    int dl=_s[moveid].lie-lie;
   if(dh==0||dl==0)
      return true;
   else
      return false;
}
bool Board::isIn(int hang,int lie)  //马角是否右障碍
{
    bool at=false;
    for(int i=0;i<32;i++)
    {
        if(hang==_s[i].hang&&lie==_s[i].lie&&_s[i]._dead==false)
        {
            at=true;
            break;
        }
    }
    return at;
}
bool Board::canMove2(int moveid,int hang,int lie,int killid)
{
    qDebug()<<"进入move2函数";
    int dh=_s[moveid].hang-hang;
    int dl=_s[moveid].lie-lie;
    dh=abs(dh);dl=abs(dl);
     qDebug()<<"行："; qDebug()<<hang;
      qDebug()<<"列:"; qDebug()<<lie;
   if(dh==2&&dl==1)
   {
       qDebug()<<"行2！";
       if(hang-_s[moveid].hang==2)  //向下走
           {
          if(isIn(_s[moveid].hang+1,_s[moveid].lie))
              return false;
          else return true;
       }
       if(_s[moveid].hang-hang==2)//向上走
          { if(isIn(_s[moveid].hang-1,_s[moveid].lie))
               return false;
           else return true;
       }
   }
   else if(dh==1&&dl==2)
      {
        qDebug()<<"列2！";
       if(lie-_s[moveid].lie==2)//向右走
           {
           if(isIn(_s[moveid].hang,_s[moveid].lie+1))
               return false;
           else return true;
       }
       if(_s[moveid].lie-lie==2)  //向左走
       {
           if(isIn(_s[moveid].hang,_s[moveid].lie-1))
               return false;
           else return true;
       }
   }
   else
      return false;
}
bool Board::canMove3(int moveid,int hang,int lie,int killid)
{
    qDebug()<<"进入move3函数";
    //1.走直线
    //2.翻山炮
    int dh=abs(_s[moveid].hang-hang);
    int dl=abs(_s[moveid].lie-lie);
     if(dh==0||dl==0)  //走直线
     {
         if(!isIn(hang,lie))  //走的位置有没有棋子，有的话检查中间是不是仅有一个棋子
             return true;
         else
        {
            qDebug()<<"中间有棋子";
           if(dh==0)
           {
               qDebug()<<"同一行";
              int min=lie<_s[moveid].lie?lie:_s[moveid].lie;
              int max=lie>_s[moveid].lie?lie:_s[moveid].lie;
              int num=0;
              for(int i=min+1;i<=max-1;i++)
              {
                  if(isIn(hang,i))num++;
                  if(num>1){num=1000;break;}
              }
              qDebug()<<num;
              if(num==1)return true;
              else return false;
           }
           if(dl==0)
           {
               qDebug()<<"同一列";
               int min=hang<_s[moveid].hang?hang:_s[moveid].hang;
               int max=hang>_s[moveid].hang?hang:_s[moveid].hang;
               int num=0;
               for(int i=min+1;i<=max-1;i++)
               {
                   if(isIn(i,lie))num++;
                   if(num>1){num=1000;break;}
               }
               qDebug()<<num;
               if(num==1)return true;
               else return false;
           }
        }
     }
     return false;
}
bool Board::canMove4(int moveid,int hang,int lie,int killid)//BING
{
    qDebug()<<"进入move4函数";
    /*
       1.没过界之前只能向前走
       2.过界后不能后退
       3.一次走一步
    */
    int dh=abs(_s[moveid].hang-hang);
    int dl=abs(_s[moveid].lie-lie);
    if((dh==1&&dl==0)||(dh==0&&dl==1))  //一次一步
    {
        //分过界与否讨论
         if(_s[moveid]._red)  //如果红棋
         {
             qDebug()<<"走红棋";
             if(_s[moveid].hang>4)   //过界
             {
                  qDebug()<<"过界";
                 if(dl==0&&dh==1&&hang<_s[moveid].hang)   //往后走就false
                     return false;
                 else return true;
             }
             else
             {
                 qDebug()<<"未过界";
                 if(dh==1&&dl==0&&hang>_s[moveid].hang)
                     return true;
                  else return false;
             }
         }
         else   //黑棋
         {
              qDebug()<<"走黑棋";
             if(_s[moveid].hang<=4)//过界
             {
                 qDebug()<<"过界";
                 if(dl==0&&dh==1&&hang>_s[moveid].hang)
                     return false;
                 else return true;
             }
             else
             {
                 qDebug()<<"未过界";
                 if(dl==0&&dh==1&&hang<_s[moveid].hang)
                     return true;
                 else return false;
             }
         }
    }
    return false;
}
bool Board::canMove5(int moveid,int hang,int lie,int killid)
{
    qDebug()<<"进入move5!";
    //1.在九宫内
    //2.步长一个格子
     qDebug()<<hang;
     //如果两边都只有将，中间没有其他棋子，则将可以吃将
     if(moveid<16&&_s[moveid].lie==_s[moveid+16].lie)
     {
          qDebug()<<"红方吃姜";
         int num=0;
         for(int i=_s[moveid].hang+1;i<_s[moveid+16].hang;i++)
         {
             if(isIn(i,_s[moveid].lie))num++;
             if(num>0){num=1000;break;}

         }
         if(num!=0)return false;
         else return true;
     }
     else if(moveid>16&&_s[moveid].lie==_s[moveid-16].lie)
     {
         qDebug()<<"黑方吃姜";
         int num=0;
         for(int i=_s[moveid-16].hang+1;i<_s[moveid].hang;i++)
         {
             if(isIn(i,_s[moveid].lie))num++;
             if(num>0){num=1000;break;}

         }
         qDebug()<<num;
         if(num!=0)return false;
         else return true;
     }
    if(_s[moveid]._red)
    {
        if(hang>2)return false;
        if(lie<3||lie>5)return false;
    }
   else
        {
            if(hang<7)return false;
            if(lie<3||lie>5)return false;
        }
     qDebug()<<"行没问题！";
                qDebug()<<lie;
    int dh=_s[moveid].hang-hang;
    int dl=_s[moveid].lie-lie;
    int d=abs(dh)*10+abs(dl);
    if(d==1||d==10)return true;



    return false;
}
bool Board::canMove6(int moveid,int hang,int lie,int killid)//SHI
{
    qDebug()<<"进入move6函数";
    /*
        1.走斜线，只走一步
    */
    int dh=abs(_s[moveid].hang-hang);
    int dl=abs(_s[moveid].lie-lie);
    if(dl==1&&dh==1)
    {
        if(_s[moveid]._red)
        {
            if((lie>=3&&lie<=5)&&(hang>=0&&hang<=2))
                return true;
            else return false;

        }
        else{
            if((lie>=3&&lie<=5)&&(hang>=7&&hang<=9))
                return true;
            else return false;
        }
    }
    return false;
}
bool Board::canMove7(int moveid,int hang,int lie,int killid) //XIANG
{
    qDebug()<<"进入move7函数";
    /*
     1.走田即可
     2.象心堵住则不能走
      */
    int dh=abs(_s[moveid].hang-hang);
    int dl=abs(_s[moveid].lie-lie);
    if(dh==2&&dl==2&&(isIn((hang+_s[moveid].hang)/2,(lie+_s[moveid].lie)/2))==false)
    return true;
    else return false;
}
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();
    //将pt转化成象棋的行列值，再去判断行列上有无棋子
    int hang,lie;
    bool bret=getHL(pt,hang,lie);//获取点中的行和列
    if(bret==false)
        return ;
//求目标位置
    int i;
    int click=-1;
    for(i=0;i<32;i++)
    {
        if(_s[i].hang==hang&&_s[i].lie==lie&&_s[i]._dead==false)
            break;
    }
    if(i<32)
    {
        click=i;            //判断点中的是哪个棋子，click=-1即说明该处没有棋子，不为-1说明该处有棋子
    }
//点中棋子和吃掉棋子
    if(seclected==-1)         //第一次click为鼠标点击棋子位置，然后赋值给seclected，然后变成鼠标点
    {                         //click第二次如果点击的是空白位置就走棋，如果是对方棋子位置就吃
    if(click!=-1)
    {
        if(turn==_s[click]._red){  //该红走
        seclected=click;
        update();                  //点中后变颜色所以更新
        }
    }
    }
    else
    {
         qDebug()<<"seclected:";
        qDebug()<<seclected;
        qDebug()<<"click:";
         qDebug()<<click;
        if(canMove(seclected,hang,lie,click)){
            qDebug()<<"---hsy--test--showtable---";
        _s[seclected].hang=hang;
        _s[seclected].lie=lie;
        if(click!=-1)  //有棋子吃
        {
            _s[click]._dead=true;
        }
        seclected=-1;
        turn =!turn;
        update();
    }
    }

}
