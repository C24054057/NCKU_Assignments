#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QApplication *main;
};

#endif // MAINWINDOW_H
