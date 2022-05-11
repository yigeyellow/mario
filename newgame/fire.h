#ifndef FIRE_H
#define FIRE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>


class fire:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    fire(QObject *parent = 0);
    int type;//没有0，普通攻击1，高级攻击2
    int obPosX;
    int obPosY;
    int obWidth;
    int obHeight;
    int fireDir=1;//左0，右1
    int firedistance;
    QPixmap Fire1=QPixmap(":/fire/fire/fire.png");
    QPixmap Fire2=QPixmap(":/fire/fire/bigfire.png");
    QTimer *FireMoveTimer=new QTimer;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    void setType(int num);
    void setWidthHeight(int w,int h);

signals:
    void GetFire();
    void FireEnd();
};

#endif // FIRE_H
