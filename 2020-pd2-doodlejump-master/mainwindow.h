#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QCloseEvent>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "doodlegame.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    int start_doodle_game();

signals:
    void update_best_score_signal(int&);


private:
    Ui::MainWindow *ui;
    QLabel *title, *score, *number;
    QPushButton *startButton;
    QFont ftitle, fscore ,fnumber ,fstart;
    QString s;
    int finalScore;
};

#endif // MAINWINDOW_H
