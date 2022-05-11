#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsitem>
#include <QPixmap>
#include <QTimer>

class monster : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit monster(QObject *parent = nullptr);
    int type;
    int moPosX;
    int moPosY;
    int moWidth;
    int moHeight;
    QPixmap monster_fly=QPixmap(":/monster/monster/monster1.png");
    QPixmap monster_ground=QPixmap(":/monster/monster/monster2.png");
    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    void setType(int num);
    void setWidthHeight(int w,int h);
    void setShowFlag(int num);
    QTimer*HurtTimer=new QTimer;
    int work=1;



signals:
    void GetMonster_Fly();
    void GetMonster_Ground();
public slots:

};

#endif // MONSTER_H
