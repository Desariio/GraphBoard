#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "cells.h"
#include "board.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QThread>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void initBoardButton();
    void autoSolve();
    void nextStep();
    void previousStep();
    void checkSolved();
    //void action();

private:
    Ui::MainWindow *ui;
    Board board;
    Board boardSolved;
    std::vector<Board> listOfBoard;


    void delay(int ms);
    void setBtnEnable(bool isEnable);
};

#endif // MAINWINDOW_H
