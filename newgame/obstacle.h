#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QGraphicsitem>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
class obstacle : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    obstacle(QObject *parent = 0,int moneytype=0);
    int type;//地0，砖块1，金币2，
    int obPosX;
    int obPosY;
    int obWidth;
    int obHeight;
    int showflag;
    int situation;
    int firetype;
    QPixmap Ground=QPixmap(":/obstacle/obstacle/ground.png");
    QPixmap Brick=QPixmap(":/obstacle/obstacle/brick.png");
    QPixmap Money;
    QPixmap Coin=QPixmap(":/obstacle/obstacle/money.png");
    QPixmap WinFlag=QPixmap(":/obstacle/obstacle/win.png");
    QPixmap Mushroom1=QPixmap(":/obstacle/obstacle/mushroom1.png");
    QPixmap Mushroom2=QPixmap(":/obstacle/obstacle/mushroom2.png");
    QPixmap Situation_Stand=QPixmap(":/mario/mario/stand.png");
    QPixmap Situation_Fly=QPixmap(":/mario/mario/fly.png");
    QPixmap Situation_Slide=QPixmap(":/mario/mario/quick.png");
    QPixmap Fire_Source1=QPixmap(":/fire/fire/fire.png");
    QPixmap Fire_Source2=QPixmap(":/fire/fire/bigfire.png");







    QRectF boundingRect() const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    void setType(int num);
    void setWidthHeight(int w,int h);
    void setShowFlag(int num);
    void setSituation(int situation_mario);
    void situation_delete();
    int getHeight();
    int getY();

signals:
    void GetCoin();
    void GetMushroom2();
    void GetMushroom1();
    void GetBrick();
    void GetFireSource();

public slots:
};

#endif // OBSTACLE_H
