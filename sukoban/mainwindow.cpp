#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secwindow.h"
#include "thirdwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*開啟 Level 1的視窗*/
void MainWindow::on_pushButton_clicked()
{
    secwindow secwindow;
    secwindow.setModal(true);
    secwindow.exec();
}

/*開啟 Level 2的視窗*/
void MainWindow::on_pushButton_2_clicked()
{
    thirdwindow thirdwindow;
    thirdwindow.setModal(true);
    thirdwindow.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    main->quit();
}
