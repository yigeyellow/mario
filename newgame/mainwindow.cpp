#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstLevelIni();
    this->hide();
    pView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

////初始化--------------------------------------------------
void MainWindow::firstLevelIni(){

    IniStack();
    IniList();

    //初始化地面
    for(int i=0;i<GROUNDNUM;i++)
    {
        ground[i]=new obstacle;
    }
    nGround(GROUNDNUM-1,GROUNDNUM,0,0);
    nGround(0,GROUNDNUM-1,0,350);//begin,end,x,y

    //初始化砖块
    for(int i=0;i<BRICKNUM;i++)
    {
        brick[i] = new obstacle;
        connect(brick[i],&obstacle::GetBrick,[=](){
            qDebug()<<"111";
            if(item->getY()>=brick[i]->getY())
            {
                item->moveBy(0,5);
                item->setVelocity(-10);
            }

        });
    }
    nBrick(0,BRICKNUM,100,200);


    //初始化胜利旗帜
    winflag=new obstacle;
    newOb(winflag,3,1000,0,200,600,4);


    //初始化快速蘑菇2
    mushroom2=new obstacle;
    newOb(mushroom2,4,300,300,70,70,5);
    //变快蘑菇2
    connect(mushroom2,&obstacle::GetMushroom2,[=](){
        item->setSituation(player::slide);
        mushroom2_num=0;
        Push(2);
    });


    //初始化飞行蘑菇1
    mushroom1=new obstacle;
    newOb(mushroom1,5,200,50,70,70,0);
    //飞行蘑菇1
    connect(mushroom1,&obstacle::GetMushroom1,[=](){
        item->setSituation(player::fly);
        mushroom1_num=0;
        Push(1);
    });




    //初始化角色
    item=new player;
    item->setPos(150,300);
    item->setData(1,1);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsFocusable);
    pScene->addItem(item);
    pScene->setFocusItem(item);


    //初始化金币
    for(int i=0;i<COINNUM;i++)
    {
        coin[i] = new obstacle;
        coin_num[i]=1;
    }
    newOb(coin[0],2,250,100,70,70,3);
    newOb(coin[1],2,170,100,70,70,3);


    //初始化飞行怪物
    monster_fly=new monster;
    monster_fly->setPos(800,150);
    monster_fly->setWidthHeight(70,70);
    monster_fly->setType(1);
    monster_fly->setData(1,7);
    pScene->addItem(monster_fly);



    //血量
    QFont font;
    font.setKerning(true);
    font.setBold(true);
    text->setPlainText("血量:"+QString::number(item->heroBlood));
    text->setPos(100,0);
    text->setFont(font);
    pScene->addItem(text);
    //血量++
    for(int i=0;i<COINNUM;i++)
    {
        connect(coin[i],&obstacle::GetCoin,[=](){
           coin_num[i]=0;
           item->heroBlood+=1;
           text->setPlainText("血量:"+QString::number(item->heroBlood));
           text->update();
        });
    }
    //血量--
    connect(monster_fly,&monster::GetMonster_Fly,[=](){
        item->heroBlood-=1;
        text->setPlainText("血量:"+QString::number(item->heroBlood));
        text->update();
        monster_fly->work=0;

        switch (Pop()) {
        case 0:
            item->setSituation(player::stand);
            break;
        case 1://飞
            item->setSituation(player::fly);
            break;
        case 2://slide
            item->setSituation(player::slide);
            break;
        default:
            break;
        }
    });






    //fire资源
    for(int i=0;i<FIRENUM;i++)
    {
        fire_source[i]=new obstacle;
        connect(fire_source[i],&obstacle::GetFireSource,[=](){
                Push_List(fire_type[i]);
                fire_num[i]=0;
        });
    }
    //nFire(0,1,300,100,1);

    newOb(fire_source[0],7,200,100,70,70,9);
    fire_type[0]=2;
    fire_source[0]->firetype=2;
    fire_num[0]=1;
    newOb(fire_source[1],7,250,100,70,70,9);
    fire_type[1]=1;
    fire_source[1]->firetype=1;
    fire_num[1]=1;
    newOb(fire_source[2],7,300,100,70,70,9);
    fire_type[2]=1;
    fire_source[2]->firetype=1;
    fire_num[2]=1;
    newOb(fire_source[3],7,350,100,70,70,9);
    fire_type[3]=1;
    fire_source[3]->firetype=1;
    fire_num[3]=1;



    connect(item,&player::Fire,[=](){
        qDebug()<<"mario执行了fire";
        Pop_List();
    });








    //pView->drawBackground(background,QRect(0,0,SCREENWIDTH,SCREENHEIGHT));

    //pView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    pView->resize(SCREENWIDTH,SCREENHEIGHT);
    pView->setScene(pScene);
    pView->setStyleSheet("border:none; background:pink;");//背景色
    pView->centerOn(500,0);

    //背景移动（随人物）
    connect(item,&player::BackGroundMove_Left,[=](){
        for(int i=0;i<GROUNDNUM;i++)
        {
            ground[i]->moveBy(item->getHorizontalSpeed(),0);
        }
        for(int i=0;i<BRICKNUM;i++)
        {
            brick[i]->moveBy(item->getHorizontalSpeed(),0);
        }
        for(int i=0;i<COINNUM;i++)
        {
            if(coin_num[i]==1)
            {
                coin[i]->moveBy(item->getHorizontalSpeed(),0);
            }
        }
        winflag->moveBy(item->getHorizontalSpeed(),0);
        if(mushroom1_num==1)
        {
            mushroom1->moveBy(item->getHorizontalSpeed(),0);
        }
        if(mushroom2_num==1)
        {
            mushroom2->moveBy(item->getHorizontalSpeed(),0);
        }
        monster_fly->moveBy(item->getHorizontalSpeed(),0);
        for(int i=0;i<FIRENUM;i++)
        {
            if(fire_num[i]==1){
                fire_source[i]->moveBy(item->getHorizontalSpeed(),0);
            }
        }
    });
    connect(item,&player::BackGroundMove_Right,[=](){
        for(int i=0;i<GROUNDNUM;i++)
        {
            ground[i]->moveBy(-item->getHorizontalSpeed(),0);
        }
        for(int i=0;i<BRICKNUM;i++)
        {
            brick[i]->moveBy(-item->getHorizontalSpeed(),0);
        }
        for(int i=0;i<COINNUM;i++)
        {
            if(coin_num[i])
            {
                coin[i]->moveBy(-item->getHorizontalSpeed(),0);
            }
        }
        winflag->moveBy(-item->getHorizontalSpeed(),0);
        if(mushroom1_num==1)
        {
            mushroom1->moveBy(-item->getHorizontalSpeed(),0);
        }
        if(mushroom2_num==1)
        {
            mushroom2->moveBy(-item->getHorizontalSpeed(),0);
        }
        monster_fly->moveBy(-item->getHorizontalSpeed(),0);
        for(int i=0;i<FIRENUM;i++)
        {
            if(fire_num[i]==1){
                fire_source[i]->moveBy(-item->getHorizontalSpeed(),0);
            }
        }
    });

    //胜利
    connect(item,&player::succeed,[=](){
        if(win==0){
            pView->close();
            QMessageBox::about(this,"Victory","你赢了!");
            win++;
            this->close();
        }

    });

    //失败
    connect(item,&player::failed,[=](){
        if(win==0){
            pView->close();
            QMessageBox::about(this,"Victory","你输了!");
            win++;
            this->close();
        }
    });
}


void MainWindow::newOb(obstacle *one, int type, int x, int y, int w, int h, int data)
{
    one->setType(type);//地0，砖头1，金币2,胜利旗帜3
    one->setWidthHeight(w,h);
    one->setPos(x,y);
    if(type==6)
    {
        one->setSituation(data);
//    }else if(type==8){
//        one->firetype=data;
    }else{
        one->setData(1,data);//人1,地2，砖头2，金币3,胜利旗帜4,变快蘑菇5,飞行蘑菇6，飞行怪物7
    }
    pScene->addItem(one);
}
void MainWindow::nGround(int begin, int end, int x, int y)
{
    for(int i=begin;i<end;i++)
    {
        newOb(ground[i],0,x+0.4*GROUNDW*(i-begin),y,GROUNDW,GROUNDH,2);
    }
}
void MainWindow::nBrick(int begin, int end, int x, int y)
{
    for(int i=begin;i<end;i++)
    {
        newOb(brick[i],1,x+0.4*BRICKW*(i-begin),y,BRICKW,BRICKH,2);
    }
}



void MainWindow::paintEvent(QPaintEvent *event)
{

}




//栈
void MainWindow::IniStack()
{
    //头节点为10,用于判断是否到头
    cursor=0;
    stack_situation[cursor]=10;
    //栈第1个元素
    cursor++;
    stack_situation[cursor]=0;
    //左上角栈的显示
    stack_graph[cursor]=new obstacle;
    cursorx=100;
    newOb(stack_graph[cursor],6,cursorx,0,30,30,0);//最后一位不是data,是situation

}

void MainWindow::Push(int situation)
{
    //situation:::::::stand:0  fly:1  slide:2
    cursor++;
    stack_situation[cursor]=situation;
    //栈的显示
    stack_graph[cursor]=new obstacle;
    cursorx+=14;
    newOb(stack_graph[cursor],6,cursorx,0,30,30,situation);
}

int MainWindow::Pop()
{
    //判断是否还有situation，并删除栈的显示
    if(stack_situation[cursor-1]!=10)
    {
        stack_graph[cursor]->situation_delete();
        cursor--;
        cursorx-=14;
    }
    //返回上一个（或这一个）situation
    return stack_situation[cursor];
}



//队列listfire
void MainWindow::IniList()
{
    //firetype::::::::没有0，普通1，高级2
    for(int i=0;i<FIRENUM;i++)
    {
        list_firetype[i]=1;
    }
    //初始化各种游标和数量
    cursor_fire_start=0;
    cursor_fire_end=0;
    curnum_fire=3;
    tolnum_fire=3;
    //在左上角的队列显示
    cursorx_list_start=100;
    for(int i=0;i<curnum_fire;i++)
    {
        list_graph[i]=new obstacle;
        newOb(list_graph[i],8,cursorx_list_start+14*i,14,27,27,8);
        list_graph[i]->firetype=1;
    }
}

void MainWindow::Push_List(int firetype)
{
    //判断，只有弹槽没满时，才可以加入新的fire
    if(curnum_fire!=tolnum_fire)
    {
        //在end处，fire加入队列
        list_firetype[cursor_fire_end]=firetype;
        //链表的显示
        list_graph[cursor_fire_end]=new obstacle;
        newOb(list_graph[cursor_fire_end],8,cursorx_list_start+14*cursor_fire_end,14,27,27,9);
        list_graph[cursor_fire_end]->firetype=list_firetype[cursor_fire_end];
        //游标走向下一个
        if(cursor_fire_end==tolnum_fire-1)
        {
            cursor_fire_end=0;
        }else {
           cursor_fire_end++;
        }

        //当前fire数++
        curnum_fire++;
    }

}
void MainWindow::Pop_List()
{
    if(curnum_fire>0)
    {
        //在start处，初始化队列fire实体
        list_fire[cursor_fire_start]=new fire;
        //获取fire的data
        int data;
        if(list_firetype[cursor_fire_start]==1) {data=8;}
        else {data=10;}
        //获取方向
        if(item->inthorizontaldir==0){list_fire[cursor_fire_start]->fireDir=0;}
        else{list_fire[cursor_fire_start]->fireDir=1;}
        //其他
        list_fire[cursor_fire_start]->setPos(item->pos().x(),item->pos().y());
        list_fire[cursor_fire_start]->setWidthHeight(30,30);
        list_fire[cursor_fire_start]->setType(list_firetype[cursor_fire_start]);
        list_fire[cursor_fire_start]->setData(1,data);
        pScene->addItem(list_fire[cursor_fire_start]);


        //减去左上角图标
        delete list_graph[cursor_fire_start];
        //从队列中减去fire
        if(cursor_fire_start==tolnum_fire-1)
        {
            cursor_fire_start=0;
        }else {
           cursor_fire_start++;
        }
        //当前fire数--
        curnum_fire--;
    }

}

void MainWindow::nFire(int begin, int end, int x, int y, int firetype)
{
    for(int i=begin;i<end;i++)
    {
        newOb(fire_source[i],7,x+(i-begin)*60,y,60,60,9);
        fire_type[i]=firetype;
    }
}

