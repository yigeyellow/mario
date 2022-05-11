#include "player.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>


player::player(QObject *parent) : QObject(parent)
{
    connect(JumpTimer,&QTimer::timeout,[=](){
        if(Situation==stand||Situation==slide)
        {
            FreeFalling();//自由落体
        }

        //失败判定
        if(pos().y()>500||heroBlood<=0)
        {
            emit failed();
        }
        //判定碰撞
        if(!collidingItems().isEmpty())
        {
            for(int i = 0;i < collidingItems().length(); i++)
            {
                switch (collidingItems().at(i)->data(1).toInt())
                {
                case 4://胜利旗帜
                    emit succeed();
                    break;
                default:
                    break;
                }
            }
        }
    });

    //按键
    connect(KeyTimer,&QTimer::timeout,[=](){
        if(KeyPressed(Key_W))
        {
            if(Situation==stand||Situation==slide)
            {
                setVelocity(4);
            }
            else if(Situation==fly)
            {
                moveBy(0,-2);
            }

        }
        else if(KeyPressed(Key_A))
        {
            HorizontalDir=left;
            inthorizontaldir=0;
            if(pos().x()>100)
            {
                moveBy(-HorizontalSpeed,0);
            }
            else
            {
                emit BackGroundMove_Left();
            }
        }
        else if(KeyPressed(Key_D))
        {
            HorizontalDir=right;
            inthorizontaldir=1;
            if(pos().x()<400)
            {
                moveBy(HorizontalSpeed,0);
            }
            else
            {
                emit BackGroundMove_Right();
            }
        }
        else if(KeyPressed(Key_S))
        {
            moveBy(0,2);
        }
        else if(KeyPressed(Key_J))
        {
            //如果达到时间间隔
            if(firetime)
            {
                emit Fire();
                firetime=false;
            }
        }

    });

    //fire时间间隔
    connect(FireTimer,&QTimer::timeout,[=](){
        firetime=true;
    });

    FireTimer->start(1000);
    JumpTimer->start(40);
    KeyTimer->start(10);
}
void player::FreeFalling()
{

    if(velocity<=0)
    {
        VerticalDir=down;
    }
    else if(velocity>0)
    {
        VerticalDir=up;
        moveBy(0,-velocity);
    }

    //如果没有碰到东西
    if(collidingItems().isEmpty())
    {
        moveBy(0,-velocity);
        velocity=0.5*velocity-gravity;
    }
}

void player::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        SaveKeyPressed(Key_W);
    }
    else if(event->key()==Qt::Key_A)
    {
        SaveKeyPressed(Key_A);
    }
    else if(event->key()==Qt::Key_D)
    {
        SaveKeyPressed(Key_D);
    }
    else if(event->key()==Qt::Key_S)
    {
        SaveKeyPressed(Key_S);
    }
    else if(event->key()==Qt::Key_J)
    {
        SaveKeyPressed(Key_J);
    }
}
void player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        SaveKeyReleased(Key_W);
    }
    else if(event->key()==Qt::Key_A)
    {
        SaveKeyReleased(Key_A);
    }
    else if(event->key()==Qt::Key_D)
    {
        SaveKeyReleased(Key_D);
    }
    else if(event->key()==Qt::Key_S)
    {
        SaveKeyReleased(Key_S);
    }
    else if(event->key()==Qt::Key_J)
    {
        SaveKeyReleased(Key_J);
    }
}




void player::setVelocity(int v)
{
    velocity=v;
}
float player::getVelocity()
{
    return velocity;
}

QRectF player::boundingRect()const
{
    return QRectF(pos().x(),pos().y(),PicWidth,PicHeight);
}
void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(Situation==slide)
    {
        setHorizontalSpeed(5);
    }else{
        setHorizontalSpeed(2);
    }
    if(HorizontalDir==right)
    {
        if(Situation==stand)
        {
            painter->drawPixmap(pos().x(),pos().y(),PicWidth,PicHeight,HeroStand);
        }
        else if(Situation==slide)
        {
            painter->drawPixmap(pos().x(),pos().y(),PicWidth,PicHeight,HeroSlide);
        }
        else if(Situation==fly)
        {
            painter->drawPixmap(pos().x(),pos().y(),PicWidth,PicHeight,HeroFly);
        }

    }else{
        if(Situation==stand)
        {
            painter->drawPixmap(pos().x(),pos().y(),PicWidth,PicHeight,HeroStand_Left);
        }
        else if(Situation==slide)
        {
            painter->drawPixmap(pos().x(),pos().y(),PicWidth,PicHeight,HeroSlide_Left);
        }
        else if(Situation==fly)
        {
            painter->drawPixmap(pos().x(),pos().y(),PicWidth,PicHeight,HeroFly_Left);
        }
    }

}
void player::setWidthHeight(int w, int h)
{
    PicWidth=w;
    PicHeight=h;
}
//自加

int player::getHorizontalSpeed()
{
    return HorizontalSpeed;
}
void player::setHorizontalSpeed(int horizontalspeed)
{
    HorizontalSpeed=horizontalspeed;
}
void player::setHorizontalDirection(Dir horizontaldir)
{
    HorizontalDir=horizontaldir;
}
void player::setSituation(Situ situation)
{
    Situation=situation;
}
int player::getY()
{
    return pos().y();
}
