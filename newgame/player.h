#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include<QGraphicsItem>
#include <QTimer>
#include <QKeyEvent>

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include<QKeyEvent>
#include <QString>
#include <QList>
#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include<QCursor>
#include<QGraphicsSceneMouseEvent>
#include<QDrag>
#include<QWidget>
#include<QMimeData>
#include<QApplication>
#include<QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QTimer>
#include <QPixmap>
#include <QObject>
#include <QDebug>
#include<QKeyEvent>
#include<QList>
#include<QPainter>

class player : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);
    //基本
    int heroPosX;
    int heroPosY;
    QPixmap HeroStand=QPixmap(":/mario/mario/stand.png");
    QPixmap HeroStand_Left=QPixmap(":/mario/mario/stand_left.png");
    QPixmap HeroSlide=QPixmap(":/mario/mario/quick.png");
    QPixmap HeroSlide_Left=QPixmap(":/mario/mario/quick_left.png");
    QPixmap HeroFly=QPixmap(":/mario/mario/fly.png");
    QPixmap HeroFly_Left=QPixmap(":/mario/mario/fly_left.png");

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    //加运动
    QTimer *KeyTimer=new QTimer;
    QTimer *JumpTimer=new QTimer;

    enum Dir{up,down,left,right};
    enum Situ{stand,slide,fly};
    Situ Situation=stand;
    Dir VerticalDir;
    Dir HorizontalDir=right;
    int inthorizontaldir=1;
    int HorizontalSpeed=2;
    //加血量
    int heroBlood=10;

    //自加
    void setHorizontalSpeed(int horizontalspeed);
    int getHorizontalSpeed(void);
    void setHorizontalDirection(Dir horizontaldir);
    void setSituation(Situ situation);




//private:
    //基本
    int PicWidth=50;
    int PicHeight=60;
    void setWidthHeight(int w,int h);
    //运动
    float velocity=5;
    void setVelocity(int v);
    float getVelocity();
    float gravity=4;
    bool JumpOrnot;
    bool UnderBrick;
    int getY();
    //fire
    bool firetime=false;
    QTimer *FireTimer=new QTimer;



    //加按钮(看不懂)
    void keyPressEvent(QKeyEvent *event)override;
    void keyReleaseEvent(QKeyEvent *event)override;
    inline void SaveKeyPressed( int key )
    {
        m_PressedKeys |= ( 1 << key );
    }
    inline void SaveKeyReleased( int key )
    {
        m_PressedKeys &= ~( 1 << key );
    }
    inline bool KeyPressed( int key )
    {
        return m_PressedKeys & ( 1 << key );
    }
    enum Interested_Keys
    {
        Key_A = 1,
        Key_W,
        Key_D,
        Key_K,
        Key_J,
        Key_L,
        Key_S
    };
        quint32  m_PressedKeys=0;

private:
signals:
   void succeed();
   void failed();
   void GetMushroom2();
   void BackGroundMove_Left();
   void BackGroundMove_Right();
   void Fire();



public slots:
        void FreeFalling(void);
};

#endif // PLAYER_H
