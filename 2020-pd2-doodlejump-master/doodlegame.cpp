#include "doodlegame.h"
#include "ui_doodlegame.h"
#include <windows.h>
#include <QDebug>

doodlegame::doodlegame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doodlegame),
    scene(new QGraphicsScene(0, 0, 0, 0)),
    tjump(new QTimer),
    tbullet(new QTimer),
    thorizontal(new QTimer),
    tjumpFast(new QTimer),
    tgameover(new QTimer)
{
    ui->setupUi(this);

    /*初始化*/
    srand(time(0));
    timer = 5;
    dt = 1;
    count = 0;
    viewTop=hscene-500;         //視窗上方邊界初始位置
    scene->setSceneRect(0, viewTop, wview, hview);
    ui->graphicsView->setScene(scene);
    which_prop2 = 0;

    /*放置平台(綠色)*/
    for(int i=0; i<nplatform1; i++){
        platform1[i] = new QGraphicsPixmapItem(QPixmap(":/res/platform.png").scaled(platformSizex,platformSizey));
        plat1[i].x = rand() % wplatform;
        plat1[i].y = rand() % hplatform1;
        scene->addItem(platform1[i]);
        platform1[i]->setPos(plat1[i].x, plat1[i].y);
    }

    /*放置平台(藍色)*/
    for(int i=0; i<nplatform2; i++){
        platform2[i] = new QGraphicsPixmapItem(QPixmap(":/res/platform2.png").scaled(platformSizex,platformSizey));
        plat2[i].x = rand() % wplatform;
        plat2[i].y = rand() % hplatform2;
        scene->addItem(platform2[i]);
        platform2[i]->setPos(plat2[i].x, plat2[i].y);
    }
    connect(thorizontal,SIGNAL(timeout()),this,SLOT(horizintal_move()));
    thorizontal->start(10);

    /*放置道具1(黃色板子)*/
    for(int i=0; i<nprop1; i++){
        p1[i].setPixmap((QPixmap(":/res/prop1.png")).scaled(prop1Sizex,prop1Sizey));
        p1[i].x = -50;
        p1[i].y = hprop1/nprop1*(i+1);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(&p1[i]));
        p1[i].setPos(p1[i].x,p1[i].y);
    }

    /*放置道具2(彈簧)*/
    for(int i=0; i<nprop2; i++){
        p2[i].setPixmap((QPixmap(":/res/prop2.png")).scaled(prop2Sizex,prop2Sizey));
        p2[i].x = rand() % wprop2;
        p2[i].y = rand() % hprop2;
        scene->addItem(static_cast<QGraphicsPixmapItem*>(&p2[i]));
        p2[i].setPos(p2[i].x,p2[i].y);
    }
    connect(tjumpFast, SIGNAL(timeout()), this, SLOT(jump_fast()));
    tjumpFast->start(3);


    /*設置怪物*/
    for(int i=0; i<nmonster; i++){
        monster[i] = new QGraphicsPixmapItem(QPixmap(":/res/monster.png").scaled(monsterSizex,monsterSizey));
        m[i].x = rand() % wmonster;
        m[i].y = rand() % hmonster;
        scene->addItem(monster[i]);
        monster[i]->setPos(m[i].x,m[i].y);
    }

    /*設置黑洞*/
    for(int i=0; i<nblackHole; i++){
        blackHole[i] = new QGraphicsPixmapItem(QPixmap(":/res/blackhole.png").scaled(blackHoleSizex,blackHoleSizey));
        which_prop2 = rand() % nprop2;
        b[i].x = p2[which_prop2].x;
        m[i].y = p2[which_prop2].y - 250;
        scene->addItem(blackHole[i]);
        blackHole[i]->setPos(b[i].x,b[i].y);
    }

    /*設置人物*/
    d = new doodler;
    d->setPixmap(QPixmap(":/res/doodler.png").scaled(doodlerSizex,doodlerSizey));
    d->setPos(150,hscene-50);
    connect(this, SIGNAL(turnRight_signal()), d, SLOT(turn_right()));
    connect(this, SIGNAL(turnLeft_signal()), d, SLOT(turn_left()));
    connect(tjump, SIGNAL(timeout()), this, SLOT(jump()));
    tjump->start(10);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(d));


    /*設記分板(左上角)*/
    scoreLabel = new QLabel(this);
    scoreLabel->setText("Best Score：");
    scoreLabel->setGeometry(0,0,100,50);
    fscoreLabel.setPixelSize(20);
    scoreLabel->setFont(fscoreLabel);
    scoreNumber = new QLabel(this);
    scoreNumber->setNum(count);
    scoreNumber->setGeometry(110,0,100,50);
    fscoreNumber.setPixelSize(20);
    scoreNumber->setFont(fscoreNumber);

    /*放暫停鍵(右上角)*/
    pause = new QPushButton(this);
    pause->setText("Pause");
    pause->setGeometry(350,0,100,40);
    fpause.setPixelSize(20);
    pause->setFont(fpause);
    connect(pause, SIGNAL(clicked()),this,SLOT(click_to_pause()));
    pauseORresume = 1;

    connect(tgameover, SIGNAL(timeout()),this,SLOT(game_over()));
    tgameover->start(1);


}

doodlegame::~doodlegame()
{
    delete ui;
}


void doodlegame::jump(){
    int top = 45;         //上方折返點
    int posy = d->y();
    int x = d->x();
    int y = d->y();

    if(dt>0 and timer==top) //要往下折返
    {
        dt=-1;
        timer=0;
        y += vmove;
    }
    else if(dt>0)          //繼續往上
    {
        if(y < viewTop+200)   //調整畫面(保持doodler在視野內)
        {
            count = hscene-viewTop+300;           //加分
            scoreNumber->setNum(count);
            viewTop -=5;
            scene->setSceneRect(0, viewTop, wview, hview);
            ui->graphicsView->setScene(scene);
        }

        timer++;
        y -= vmove;
    }
    else                             //繼續往下
    {
        y += vmove;

        for(int i=0; i<nplatform1; i++){
            //準備踏到第i個綠色板子
            if(posy+doodlerSizey<=plat1[i].y and
               y+doodlerSizey>=plat1[i].y and
               ((x<=plat1[i].x and x+doodlerSizex>=plat1[i].x) or
                (x<=plat1[i].x+platformSizex and x+doodlerSizex>=plat1[i].x+platformSizex) or
                (x>=plat1[i].x and x+doodlerSizex<=plat1[i].x+platformSizex)))
            {
                y = plat1[i].y - doodlerSizey;  //調整踏到的位置
                dt = 1;
                break;
            }
            else if(i<nplatform2 and         //藍色板子比綠色板子少，所以要判斷
                   posy+doodlerSizey<=plat2[i].y and           //看有沒有踏到第i個藍色板子
                   y+doodlerSizey>=plat2[i].y and
                   ((x<=plat2[i].x and x+doodlerSizex>=plat2[i].x) or
                    (x<=plat2[i].x+platformSizex and x+doodlerSizex>=plat2[i].x+platformSizex) or
                    (x>=plat2[i].x and x+doodlerSizex<=plat2[i].x+platformSizex)))
            {
                y = plat2[i].y - doodlerSizey;  //調整踏到的位置
                dt = 1;
                break;
            }
            else if(i<nprop1 and             //黃色道具比綠色板子少，所以要判斷
                    posy+doodlerSizey<=p1[i].y and           //看有沒有踏到第i個黃色道具
                    y+doodlerSizey>=p1[i].y and
                    x>=p1[i].x and x+doodlerSizex<=p1[i].x+prop1Sizex)
            {
                y = p1[i].y - doodlerSizey;
                dt = 1;
                break;
            }
        }//for
    }//else
    d->setPos(x,y);
}


/*platform2的水平來回移動*/
void doodlegame::horizintal_move(){
    for(int i=0; i<nplatform2; i++)
    {
        if(i<nplatform2/2){          //都往左走，超過邊界再做調整
            if(plat2[i].x+platformSizex<=0) plat2[i].x = wview - platformSizex;
            else plat2[i].x -= 1;
        }
        else{                        //都往右走，超過邊界再做調整
            if(plat2[i].x>=wview) plat2[i].x = 0;
            else plat2[i].x += 1;
        }
        platform2[i]->setPos(plat2[i].x, plat2[i].y);
    }
}

/*道具2(彈簧)*/
//效果：直接瞬移到畫面最上方，但不會因為doodler超過畫面一半而加分
void doodlegame::jump_fast(){
    int x = d->x();
    int y = d->y();
    for(int i=0; i<nprop2; i++){
        if(y+doodlerSizey<=p2[i].y and
           y+vmove+doodlerSizey>=p2[i].y and
           ((x<=p2[i].x and x+doodlerSizex>=p2[i].x) or
            (x<=p2[i].x+prop2Sizex and x+doodlerSizex>=p2[i].x+prop2Sizex) or
            (x>=p2[i].x and x+doodlerSizex<=p2[i].x+prop2Sizex)))
        {
            y = viewTop;
            d->setPos(x, y);
        }
    }
}

/*GAME OVER*/
void doodlegame::game_over(){
    if(d->y()+doodlerSizey/2>viewTop+500)        //跑到螢幕下方外，出局
    {
        closeEvent(game);
    }

    for(int i=0; i<nmonster; i++)                    //撞到怪物，出局
    {
        if( ((d->x()<=m[i].x and d->x()+doodlerSizex>=m[i].x) or
             (d->x()>=m[i].x and d->x()+doodlerSizex<=m[i].x+monsterSizex) or
             (d->x()<=m[i].x+monsterSizex and d->x()+doodlerSizex>=m[i].x+monsterSizex)) and
            (d->y()<=m[i].y+monsterSizey and d->y()+doodlerSizey>=m[i].y+monsterSizey) )
            closeEvent(game);
    }
    for(int i=0; i<nblackHole; i++)                    //撞到怪物，出局
    {
        if( ((d->x()<=b[i].x and d->x()+doodlerSizex>=b[i].x) or
             (d->x()>=b[i].x and d->x()+doodlerSizex<=b[i].x+monsterSizex) or
             (d->x()<=b[i].x+blackHoleSizex and d->x()+doodlerSizex>=b[i].x+blackHoleSizex)) and
            (d->y()<=b[i].y+blackHoleSizey and d->y()+doodlerSizey>=b[i].y+blackHoleSizey) )
            closeEvent(game);
    }


}

/*PAUSE*/
void doodlegame::click_to_pause(){
    if(pauseORresume == 1){
        pauseORresume = 0;
        disconnect(thorizontal,SIGNAL(timeout()),this,SLOT(horizintal_move()));
        disconnect(tjumpFast, SIGNAL(timeout()), this, SLOT(jump_fast()));
        disconnect(this, SIGNAL(turnRight_signal()), d, SLOT(turn_right()));
        disconnect(this, SIGNAL(turnLeft_signal()), d, SLOT(turn_left()));
        disconnect(tjump, SIGNAL(timeout()), this, SLOT(jump()));
        disconnect(tgameover, SIGNAL(timeout()),this,SLOT(game_over()));
    }
    else{
        pauseORresume = 1;
        connect(thorizontal,SIGNAL(timeout()),this,SLOT(horizintal_move()));
        connect(tjumpFast, SIGNAL(timeout()), this, SLOT(jump_fast()));
        connect(this, SIGNAL(turnRight_signal()), d, SLOT(turn_right()));
        connect(this, SIGNAL(turnLeft_signal()), d, SLOT(turn_left()));
        connect(tjump, SIGNAL(timeout()), this, SLOT(jump()));
        connect(tgameover, SIGNAL(timeout()),this,SLOT(game_over()));
    }
}

/*連接鍵盤左右和左右函式*/
void doodlegame::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_D) emit turnRight_signal();
    if(e->key() == Qt::Key_A)  emit turnLeft_signal();
}

/*連接滑鼠與fly函式*/
void doodlegame::mousePressEvent(QMouseEvent *event){
    bullet *b = new bullet;
    b->setPixmap(QPixmap(":/res/bullet.jpg").scaled(bulletSizex, bulletSizey));
    b->setPos(d->x()+doodlerSizex/2-bulletSizex/2,d->y()-bulletSizey);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    connect(tbullet, SIGNAL(timeout()), b, SLOT(fly()));
    tbullet->start(2);
    //射殺monster
    for(int i=0; i<nmonster; i++){
        if( ((b->x()>=m[i].x and b->x()<=m[i].x+monsterSizex) or
            (b->x()+bulletSizex>=m[i].x and b->x()+bulletSizex<=m[i].x+monsterSizex)) and
             viewTop <= m[i].y   )
        {
            scene->removeItem(monster[i]);
            m[i].x = 50000;           //調整monster.x的位置，doodler才不會撞到
            m[i].y = 50000;           //調整monster.y的位置
        }
    }
}

\



