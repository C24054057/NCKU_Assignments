#ifndef DOODLEGAME_H
#define DOODLEGAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>

#include <ctime>
#include "mainwindow.h"
#include "bullet.h"
#include "prop.h"
#include "doodler.h"

#define nplatform1 1000
#define nplatform2 150
#define platformSizex 50
#define platformSizey 15
#define wplatform 450            //板子水平可以生成的範圍
#define hplatform1 30000          //板子(綠色)垂直可以生成的範圍
#define hplatform2 27000          //板子(藍色)垂直可以生成的範圍

#define nmonster 0
#define monsterSizex 50
#define monsterSizey 30
#define wmonster 450             //怪物水平可以生成的範圍
#define hmonster 30000          //怪物垂直可以生成的範圍

#define nblackHole 100
#define blackHoleSizex 30
#define blackHoleSizey 30
#define wblackHole 450           //黑洞水平可以生成的範圍
#define hblackHole 30000        //黑洞垂直可以生成的範圍

#define hscene 30000
#define wview 400
#define hview 500

#define hmove 25                     //左右移動的距離
#define vmove 5                    //上下移動的距離

struct point{
  int x, y;
};


namespace Ui {
class doodlegame;
}

class doodlegame : public QDialog
{
    Q_OBJECT

public:
    explicit doodlegame(QWidget *parent = nullptr);
    ~doodlegame();
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *event);

    int count;                                   //計算現在的成績


public slots:
    void jump();
    void horizintal_move();
    void jump_fast();
    void click_to_pause();
    void game_over();




signals:
    void turnRight_signal();
    void turnLeft_signal();





private:
    Ui::doodlegame *ui;
    QGraphicsScene *scene;
    QGraphicsView view;
    QGraphicsPixmapItem *platform1[nplatform1], *platform2[nplatform2], *monster[nmonster], *blackHole[nblackHole];
    point plat1[nplatform1], plat2[nplatform2], m[nmonster], b[nblackHole];
    //決定doodler現在要往上還是往下跳
    //dt>0, 則往上跳。 dt<0, 則往下跳。 遇到timer==10 or timer==-10要折返
    int timer, dt;
    prop p1[nprop1];  //道具1(黃色長板子)
    prop p2[nprop2];  //道具2(彈簧)
    doodler *d;
    QTimer *tjump, *tbullet, *thorizontal, *tjumpFast, *tgameover;
    int viewTop;
    QLabel *scoreLabel, *scoreNumber;
    QFont fscoreLabel, fscoreNumber, fpause;
    QPushButton *pause;
    int pauseORresume;   //1代表遊戲進行中，0代表遊戲暫停
    QCloseEvent *game;
    QLabel *gameover;
    int which_prop2;
};

#endif // DOODLEGAME_H
