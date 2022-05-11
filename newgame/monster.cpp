#include "monster.h"
#include <QPainter>

monster::monster(QObject *parent) : QObject(parent)
{
    connect(HurtTimer,&QTimer::timeout,[=](){
        work=1;
    });
    HurtTimer->start(2000);

}
QRectF monster::boundingRect()const
{
    return QRectF(pos().x(),pos().y(),moWidth,moHeight);
}
void monster::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    switch (type) {
    case 1://飞怪物
        painter->drawPixmap(pos().x(),pos().y(),moWidth,moHeight,monster_fly);
        if(!collidingItems().isEmpty()&&work)
        {
            for(int i = 0;i < collidingItems().length(); i++)
            {
                if(collidingItems().at(i)->data(1).toInt()==1)
                {
                    emit GetMonster_Fly();
                }
            }
        }

        break;
    case 2://地上的怪物
        painter->drawPixmap(pos().x(),pos().y(),moWidth,moHeight,monster_ground);
        break;
    default:
        break;
    }
}
void monster::setType(int num)
{
    type=num;
}
void monster::setWidthHeight(int w, int h)
{
    moWidth=w;
    moHeight=h;
}
