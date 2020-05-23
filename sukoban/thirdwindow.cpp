#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "mainwindow.h"
#define wall_left_boundary 40
#define wall_right_boundary 160
#define wall_up_boundary 40
#define wall_down_boundary 160

thirdwindow::thirdwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thirdwindow)
{
    ui->setupUi(this);

    int i,j;

    /*打開file拿最大的分數(也就是最低破關的步數)*/
    QFile file("C://2020-pd2-sokoban-master//BestScore_level2.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream in(&file);
    bestScore = in.readLine();
    best = bestScore.toInt();
    ui->label_3->setNum(best);
    file.close();


    /* 設圍牆 7*7 */
    QPixmap wall_picture(":/res/WallRound_Brown.png");
    for(i=0; i<26; i++){
        wall[i] = new QLabel(this);
        wall[i] ->setPixmap(wall_picture);
        if(i<=6) wall[i] ->setGeometry(wall_left_boundary+20*i,wall_up_boundary,20,20);
        else if(i<=13) wall[i] ->setGeometry(wall_left_boundary+20*(i-7),wall_down_boundary,20,20);
        else if(i<=18) wall[i] ->setGeometry(wall_left_boundary,wall_up_boundary+20*(i-13),20,20);
        else if(i<=23) wall[i] ->setGeometry(wall_right_boundary,wall_up_boundary+20*(i-18),20,20);
        else if(i==24) wall[i] ->setGeometry(80,120,20,20);
        else wall[i] ->setGeometry(120,120,20,20);
        wall[i] ->setScaledContents(true);
    }

    /* 設草地地面 5*5 */
    QPixmap ground_picture(":/res/Ground_Grass.png");
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(i==1 && j==3) continue;
            else if(i==3 && j==3) continue;
            ground[i][j] = new QLabel(this);
            ground[i][j] ->setPixmap(ground_picture);
            ground[i][j] ->setGeometry(wall_left_boundary+20*(i+1),wall_up_boundary+20*(j+1),20,20);
            ground[i][j] ->setScaledContents(true);
        }
    }


    /* 設箱子(有四塊) */
    crate_pos[1][0] = 80; crate_pos[1][1] = 100;
    crate_pos[2][0] = 100; crate_pos[2][1] = 80;
    crate_pos[3][0] = 100; crate_pos[3][1] = 120;
    crate_pos[4][0] = 120; crate_pos[4][1] = 100;
    QPixmap crate_picture(":/res/Crate_Brown.png");
    for(i=1; i<=4; i++){
        crate[i] = new QLabel(this);
        crate[i]->setPixmap(crate_picture);
        crate[i]->setGeometry(crate_pos[i][0],crate_pos[i][1],20,20);
        crate[i]->setScaledContents(true);
    }

    /*設結束的點(有四個)*/
    endpoint_pos[1][0] = 80; endpoint_pos[1][1] = 80;
    endpoint_pos[2][0] = 60; endpoint_pos[2][1] = 140;
    endpoint_pos[3][0] = 140; endpoint_pos[3][1] = 80;
    endpoint_pos[4][0] = 140; endpoint_pos[4][1] = 140;
    QPixmap endpoint_picture(":/res/EndPoint_Brown.png");
    for(i=1; i<=4; i++){
        endpoint[i] = new QLabel(this);
        endpoint[i]->setPixmap(endpoint_picture);
        endpoint[i]->setGeometry(endpoint_pos[i][0],endpoint_pos[i][1],20,20);
        endpoint[i]->setScaledContents(true);
    }

    /* 設人物的初始位置 */
    x_pos = wall_left_boundary+20;
    y_pos = wall_up_boundary+20;

    /* 設人物 和 連接上下左右鍵與畫面*/
    connect(this, SIGNAL(turnRight_signal()), this, SLOT(turnRight()));
    connect(this, SIGNAL(turnLeft_signal()), this, SLOT(turnLeft()));
    connect(this, SIGNAL(turnUp_signal()), this, SLOT(turnUp()));
    connect(this, SIGNAL(turnDown_signal()), this, SLOT(turnDown()));
    QPixmap character_picture(":/res/Character4.png");
    character = new QLabel(this);
    character->setPixmap(character_picture);
    character->setGeometry(x_pos,y_pos,20,20);
    character->setScaledContents(true);


    /*用鍵盤R 重新開啟視窗*/
    connect(this, SIGNAL(restart_signal()), this, SLOT(restart()));

}

thirdwindow::~thirdwindow()
{
    delete ui;
}

/*設定讓角色上下左右的函式*/
void thirdwindow::turnRight(){
    int dis;
    int c = 0, c2=0;
    int i;
    int end = 0;


    //確認人物與牆壁的距離
    dis = wall_right_boundary - x_pos;

    //確認有無箱子在人物右邊(一號箱子在右邊為1，二號為2，三號為3，四號為4，都沒有為0)
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos+20) && (crate_pos[i][1] == y_pos) ){
            c = i;
            break;
        }
    }

    //確認有無箱子在人物右邊的右邊
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos+40) && (crate_pos[i][1] == y_pos) ){
            c2 = i;
            break;
        }
    }

    if( (c != 0) && ( (dis == 40) || (c2 != 0) ) );
    else if(c != 0){
        crate_pos[c][0] += 20;
        x_pos += 20;
        crate[c]->setGeometry(crate_pos[c][0],y_pos,20,20);
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }
    else if(dis == 20);
    else if(x_pos==60 && y_pos==120);
    else if(x_pos==100 && y_pos==120);
    else{
        x_pos += 20;
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }

    for(i=1; i<=4; i++){
        if(crate_pos[i][0] == 80 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 60 && crate_pos[i][1] == 140) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 140) end++;
    }
    if(end == 4){
        //代表箱子全部到達endpoint，進入下一關
        QFile file("C://2020-pd2-sokoban-master//BestScore_level2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream in(&file);
        if(best==0 && count>0){
            file.resize(0);
            in << count;
        }
        else if(count <= best){
            file.resize(0);
            in << count;
        }
        b->quit();
    }

}
void thirdwindow::turnLeft(){
    int dis;
    int c = 0, c2 = 0;
    int i;
    int end = 0;


    //確認人物與牆壁的距離
    dis = x_pos - wall_left_boundary;

    //確認有無箱子在人物左邊(一號箱子在右邊為1，二號為2，三號為3，四號為4，都沒有為0)
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos-20) && (crate_pos[i][1] == y_pos) ){
            c = i;
            break;
        }
    }

    //確認有無箱子在人物左邊的左邊
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos-40) && (crate_pos[i][1] == y_pos) ){
            c2 = i;
            break;
        }
    }

    if( (c != 0) && ( (dis == 40) || (c2 != 0) ) );
    else if(c != 0){
        crate_pos[c][0] -= 20;
        x_pos -= 20;
        crate[c]->setGeometry(crate_pos[c][0],y_pos,20,20);
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }
    else if(dis == 20);
    else if(x_pos==100 && y_pos==120);
    else if(x_pos==140 && y_pos==120);
    else{
        x_pos -= 20;
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }

    for(i=1; i<=4; i++){
        if(crate_pos[i][0] == 80 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 60 && crate_pos[i][1] == 140) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 140) end++;
    }
    if(end == 4){
        //代表箱子全部到達endpoint，進入下一關
        QFile file("C://2020-pd2-sokoban-master//BestScore_level2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream in(&file);
        if(best==0 && count>0){
            file.resize(0);
            in << count;
        }
        else if(count <= best){
            file.resize(0);
            in << count;
        }
        b->quit();
    }


}
void thirdwindow::turnUp(){
    int dis;
    int c = 0, c2 = 0;
    int i;
    int end = 0;


    //確認人物與牆壁的距離
    dis = y_pos - wall_up_boundary;

    //確認有無箱子在人物上方(一號箱子在右邊為1，二號為2，三號為3，四號為4，都沒有為0)
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos) && (crate_pos[i][1] == y_pos-20) ){
            c = i;
            break;
        }
    }
    //確認有無箱子在人物上方的上方
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos) && (crate_pos[i][1] == y_pos-40) ){
            c2 = i;
            break;
        }
    }

    if( (c != 0) && ( (dis == 40) || (c2 != 0) ) );
    else if(c != 0){
        crate_pos[c][1] -= 20;
        y_pos -= 20;
        crate[c]->setGeometry(x_pos,crate_pos[c][1],20,20);
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }
    else if(dis == 20);
    else if(x_pos==80 && y_pos==140);
    else if(x_pos==120 && y_pos==140);
    else{
        y_pos -= 20;
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }

    for(i=1; i<=4; i++){
        if(crate_pos[i][0] == 80 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 60 && crate_pos[i][1] == 140) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 140) end++;
    }
    if(end == 4){
        //代表箱子全部到達endpoint，進入下一關
        QFile file("C://2020-pd2-sokoban-master//BestScore_level2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream in(&file);
        if(best==0 && count>0){
            file.resize(0);
            in << count;
        }
        else if(count <= best){
            file.resize(0);
            in << count;
        }
        b->quit();
    }


}
void thirdwindow::turnDown(){
    int dis;
    int c = 0, c2 = 0;
    int i;
    int end = 0;


    //確認人物與牆壁的距離
    dis = wall_down_boundary - y_pos;

    //確認有無箱子在人物下方(一號箱子在右邊為1，二號為2，三號為3，四號為4，都沒有為0)
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos) && (crate_pos[i][1] == y_pos+20) ){
            c = i;
            break;
        }
    }
    //確認有無箱子在人物下方的下方
    for(i=1; i<=4; i++){
        if( (crate_pos[i][0] == x_pos) && (crate_pos[i][1] == y_pos+40) ){
            c2 = i;
            break;
        }
    }

    if( (c != 0) && ( (dis == 40) || (c2 != 0) ) );
    else if( c!=0 && (x_pos==80 && y_pos==80) );
    else if( c!=0 && (x_pos==120 && y_pos==80) );
    else if(c != 0){
        crate_pos[c][1] += 20;
        y_pos += 20;
        crate[c]->setGeometry(x_pos,crate_pos[c][1],20,20);
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }
    else if(dis == 20);
    else if(x_pos==80 && y_pos==100);
    else if(x_pos==120 && y_pos==80);
    else{
        y_pos += 20;
        character->setGeometry(x_pos,y_pos,20,20);
        count++;
        ui->label->setNum(count);
    }


    for(i=1; i<=4; i++){
        if(crate_pos[i][0] == 80 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 60 && crate_pos[i][1] == 140) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 80) end++;
        else if(crate_pos[i][0] == 140 && crate_pos[i][1] == 140) end++;
    }
    if(end == 4){
        //代表箱子全部到達endpoint，進入下一關
        QFile file("C://2020-pd2-sokoban-master//BestScore_level2.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream in(&file);
        if(best==0 && count>0){
            file.resize(0);
            in << count;
        }
        else if(count <= best){
            file.resize(0);
            in << count;
        }
        b->quit();
    }




}

/*重新開始*/
void thirdwindow::restart(){
    MainWindow restart;
    restart.on_pushButton_2_clicked();
    b->quit();
}


/*連接鍵盤上下左右和上下左右函式*/
void thirdwindow::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Right) emit turnRight_signal();
    if(e->key() == Qt::Key_Left)  emit turnLeft_signal();
    if(e->key() == Qt::Key_Up)    emit turnUp_signal();
    if(e->key() == Qt::Key_Down)  emit turnDown_signal();
    if(e->key() == Qt::Key_R) emit restart_signal();
}
