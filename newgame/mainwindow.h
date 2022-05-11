#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define SCREENWIDTH 1220
#define SCREENHEIGHT 800
#define GROUNDNUM 16
#define GROUNDW 100
#define GROUNDH 100
#define BRICKNUM 20
#define BRICKW 100
#define BRICKH 100
#define COINNUM 6
#define COINW 50
#define COINH 50
#define Situation_Num 20
#define FIRENUM 5
#define FIRESOURCENUM 30
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTime>
#include <obstacle.h>
#include <player.h>
#include <monster.h>
#include <fire.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void firstLevelIni();
    void newOb(obstacle *one,int type,int x,int y,int w,int h,int data);
    void nGround(int begin,int end,int x,int y);
    void nBrick(int begin, int end, int x, int y);

    QGraphicsScene *pScene=new QGraphicsScene();
    QGraphicsView *pView=new QGraphicsView();
    //QPixmap background=QPixmap(":/background/background/background.jpg");

    obstacle *ground[GROUNDNUM];
    obstacle *brick[BRICKNUM];
    obstacle *coin[COINNUM];
//    obstacle *coin0;
//    obstacle *coin1;


    obstacle *winflag;
    obstacle *mushroom2;
    obstacle *mushroom1;
    player *item;
    monster *monster_fly;
    monster *monster_ground;


    int mushroom1_num=1;
    int mushroom2_num=1;
    int coin_num[COINNUM]={1};


    QGraphicsTextItem *text=new QGraphicsTextItem;

    int win=0;

    //栈
    int stack_situation[Situation_Num]={0};
    void IniStack();
    void Push(int situation);
    int Pop();
    int cursor=0;
    int cursorx=50;
    obstacle *stack_graph[Situation_Num];

    //队列
    //fire资源
    obstacle *fire_source[FIRENUM];
    int fire_type[FIRENUM];
    int fire_num[FIRENUM];
    obstacle *list_graph[FIRENUM];
    int cursorx_list_start;
    //碰到fire
    fire *list_fire[FIRENUM];
    int list_firetype[FIRENUM];//0没有，1普通，2特殊
    int cursor_fire_start=0;
    int cursor_fire_end=0;

    int curnum_fire=0;
    int tolnum_fire=3;
    void IniList();
    void Push_List(int firetype);
    void Pop_List();
    void nFire(int begin, int end, int x, int y,int firetype);

    int cur_firetype;





private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
