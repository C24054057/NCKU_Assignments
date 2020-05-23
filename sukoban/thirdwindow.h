#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H
#include <QDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QApplication>
#include <QString>
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QWidget>

namespace Ui {
class thirdwindow;
}

class thirdwindow : public QDialog
{
    Q_OBJECT

public:
    explicit thirdwindow(QWidget *parent = nullptr);
    ~thirdwindow();
    void keyPressEvent(QKeyEvent *e);

public slots:
    void turnRight();
    void turnLeft();
    void turnUp();
    void turnDown();
    void restart();
signals:
    void turnRight_signal();
    void turnLeft_signal();
    void turnUp_signal();
    void turnDown_signal();
    void restart_signal();

private:
    Ui::thirdwindow *ui;
    QLabel *character, *wall[26], *ground[5][5], *crate[5], *endpoint[5];
    int x_pos, y_pos, crate_pos[5][2], endpoint_pos[5][2];
    QApplication *b;
    int count=0;  //紀錄步數
    int best=0;
    QString bestScore;
};

#endif // THIRDWINDOW_H
