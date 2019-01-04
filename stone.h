#ifndef STONE_H
#define STONE_H
#include<QString>

class Stone
{
public:
    Stone();
    enum TYPE{JIANG,CHE,MA,PAO,BING,SHI,XIANG};
    int hang;
    int lie;
    int id;
    bool _dead;
    bool _red;
    TYPE  _type;
    QString getText()
    {
        switch(this->_type)
        {
        case CHE:return "车";
        case MA: return "马";
         case PAO:return "炮";
         case BING:return "兵";
         case JIANG:return "将";
         case SHI:return "士";
        case XIANG: return "相";
         default:return "错误！";
        }
    }
    void init(int id){
        struct {
            int hang,lie;
            Stone::TYPE type;
        }pos[16]={
        {0,0,Stone::CHE},
         {0,1,Stone::MA},
          {0,2,Stone::XIANG},
           {0,3,Stone::SHI},
            {0,4,Stone::JIANG},
             {0,5,Stone::SHI},
              {0,6,Stone::XIANG},
               {0,7,Stone::MA},
                {0,8,Stone::CHE}
                ,
                 {2,1,Stone::PAO},
                  {2,7,Stone::PAO},
                   {3,0,Stone::BING},
                     {3,2,Stone::BING},
                       {3,4,Stone::BING},
                         {3,6,Stone::BING},
                           {3,8,Stone::BING},
        };
        id=id;
        _dead=false;
        _red=id<16;   //0-15号为红，红就一定在上方
        if(id<16)
        {
            hang=pos[id].hang;
            lie=pos[id].lie;
            _type=pos[id].type;
        }//对应的车行相加等于9，列相加等于8；
        else{
            hang=9-pos[id-16].hang;
            lie=8-pos[id-16].lie;
              _type=pos[id-16].type;
        }
    }
};

#endif // STONE_H
