#ifndef SECWINDOW_H
#define SECWINDOW_H
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
class secwindow;
}

class secwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secwindow(QWidget *parent = nullptr);
    ~secwindow();
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
    Ui::secwindow *ui;
    QLabel *character, *wall[22], *ground[17], *crate[5], *endpoint[5];
    int x_pos, y_pos, crate_pos[5][2], endpoint_pos[5][2];
    QApplication *a;
    int count=0;  //紀錄步數
    int best=0;
    QString bestScore;
};

#endif // SECWINDOW_H
