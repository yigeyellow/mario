#include "obstacle.h"
#include<QPainter>
obstacle::obstacle(QObject *parent,int moneytype) : QObject(parent)
{

}
QRectF obstacle::boundingRect()const
{
    return QRectF(pos().x(),pos().y(),obWidth,obHeight);
}
void obstacle::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    switch (type) {
    case 0://地
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Ground);
        break;
    case 1://砖块
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Brick);
        if(!collidingItems().isEmpty())
                {
                    for(int i = 0; i < collidingItems().length(); i++)
                    {
                        if(collidingItems().at(i)->data(1).toInt()==1)
                        {
                            if(collidingItems().at(i)->data(1).toInt()==1)
                            {

                                emit GetBrick();
                            }
                        }
                    }
                }
        break;
    case 2://金币
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Coin);
        if(!collidingItems().isEmpty())
        {
            for(int i = 0; i < collidingItems().length(); i++)
            {
                if(collidingItems().at(i)->data(1).toInt()==1)
                {
                    if(collidingItems().at(i)->data(1).toInt()==1)
                    {
                        emit GetCoin();
                        delete this;
                    }
                }
            }
        }
        break;
    case 3://胜利旗帜
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,WinFlag);
        break;
    case 4://快速蘑菇2
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Mushroom2);
        if(!collidingItems().isEmpty())
        {
            for(int i = 0; i < collidingItems().length(); i++)
            {
                if(collidingItems().at(i)->data(1).toInt()==1)
                {
                    emit GetMushroom2();
                    delete this;
                }
            }
        }
        break;
    case 5://飞行蘑菇1
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Mushroom1);
        if(!collidingItems().isEmpty())
        {
            for(int i = 0; i < collidingItems().length(); i++)
            {
                if(collidingItems().at(i)->data(1).toInt()==1)
                {
                    emit GetMushroom1();
                    delete this;
                }
            }
        }
        break;
    case 6://mario状态
        switch (situation) {
        case 0:
           painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Situation_Stand);
            break;
        case 1:
           painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Situation_Fly);
            break;
        case 2:
           painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Situation_Slide);
            break;
        default:
            break;
        }
        break;
    case 7://fire资源

        switch (firetype) {
        case 1:
            painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Fire_Source1);
            break;
        case 2:
            painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Fire_Source2);
            break;
        default:
            break;
        }

        if(!collidingItems().isEmpty())
        {
            for(int i = 0; i < collidingItems().length(); i++)
            {
                if(collidingItems().at(i)->data(1).toInt()==1)
                {
                    emit GetFireSource();
                    delete this;
                }
            }
        }
        break;
    case 8://fire图标
        switch (firetype) {
        case 1:
            painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Fire_Source1);
            break;
        case 2:
            painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Fire_Source2);
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}
void obstacle::setType(int num)
{
    type=num;
}
void obstacle::setWidthHeight(int w, int h)
{
    obWidth=w;
    obHeight=h;
}
void obstacle::setShowFlag(int num)
{
    showflag=num;
}
void obstacle::setSituation(int situation_mario)
{
    situation=situation_mario;
}
void obstacle::situation_delete()
{
    delete this;
}
int obstacle::getHeight()
{
    return obHeight;
}
int obstacle::getY()
{
    return pos().y();
}

