#include "fire.h"
#include <QPainter>

fire::fire(QObject *parent):QObject(parent)
{

    firedistance=0;
    connect(FireMoveTimer,&QTimer::timeout,[=](){
        if(fireDir==1)
        {
            setPos(pos().x()+10,pos().y());
            firedistance+=10;
            if(firedistance>=300)
            {
                //emit FireEnd();
                FireMoveTimer->stop();
                delete this;
            }
        }
        else{
            setPos(pos().x()-10,pos().y());
            firedistance+=10;
            if(firedistance>=300)
            {
                //emit FireEnd();
                FireMoveTimer->stop();
                delete this;
            }
        }

    });
    FireMoveTimer->start(100);
}

QRectF fire::boundingRect()const
{
    return QRectF(pos().x(),pos().y(),obWidth,obHeight);
}
void fire::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    switch (type) {
    case 1:
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Fire1);
        if(!collidingItems().isEmpty())
                {
                    for(int i = 0; i < collidingItems().length(); i++)
                    {
                        if(collidingItems().at(i)->data(1).toInt()==1)
                        {
                            if(collidingItems().at(i)->data(1).toInt()==7)
                            {

                                //碰到怪物
                                emit FireEnd();
                                delete this;
                            }
                        }
                    }
                }
        break;
    case 2:
        painter->drawPixmap(pos().x(),pos().y(),obWidth,obHeight,Fire2);
        if(!collidingItems().isEmpty())
                {
                    for(int i = 0; i < collidingItems().length(); i++)
                    {
                        if(collidingItems().at(i)->data(1).toInt()==1)
                        {
                            if(collidingItems().at(i)->data(1).toInt()==7)
                            {

                                //碰到怪物
                                emit FireEnd();
                                delete this;
                            }
                        }
                    }
                }
        break;
    default:
        break;
    }
}

void fire::setType(int num)
{
    type=num;
}
void fire::setWidthHeight(int w, int h)
{
    obWidth=w;
    obHeight=h;
}
