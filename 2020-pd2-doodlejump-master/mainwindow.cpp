#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*標題(Doodle Jump)*/
    title = new QLabel(this);
    title->setText("Doodle Jump");
    title->setGeometry(50,50,300,100);
    ftitle.setPixelSize(50);
    title->setFont(ftitle);

    /*分數(Score)*/
    score = new QLabel(this);
    score->setText("Score：");
    score->setGeometry(100,200,100,50);
    fscore.setPixelSize(30);
    score->setFont(fscore);
    number = new QLabel(this);
    number->setNum(0);
    number->setGeometry(230,200,100,50);
    fnumber.setPixelSize(30);
    number->setFont(fnumber);

    /*開始按鈕*/
    startButton = new QPushButton(this);
    startButton->setText("start");
    startButton->setGeometry(150,300,100,50);
    fstart.setPixelSize(30);
    startButton->setFont(fstart);
    connect(startButton,SIGNAL(clicked()),this,SLOT(start_doodle_game()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



int MainWindow::start_doodle_game(){
    doodlegame a;
    a.setModal(true);
    a.exec();

    title->setText("GAME OVER");
    number->setNum(a.count);
    return 0;
}



