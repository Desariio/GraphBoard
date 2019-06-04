#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "cells.h"
#include "board.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QThread>
#include <QTime>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

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
   // void connectionSocket();
    void autoSolve();
    void nextStep();
    void previousStep();
    void checkSolved();
    //void action();

    void socketReady();
    void socketDisconnected();
    void on_btnConnection_clicked();

private:
    Ui::MainWindow *ui;
    Board board;
    Board boardSolved;
    std::vector<Board> listOfBoard;

    QTcpSocket *socket;
    QByteArray data;

    QJsonDocument doc;
    QJsonParseError docError;

    void delay(int ms);
    void setBtnEnable(bool isEnable);
};

#endif // MAINWINDOW_H
