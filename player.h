#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <QWidget>
#include <QDate>

class Player{

public:
    Player();
    Player(QString name, int score, QDate date, QTime time, bool autoSolve, int steps);

    //getters
    QString getName(){return this->name;}
    int getScore(){return this->score;}
    QDate getDate(){return this->date;}
    QTime getTime(){return this->time;}
    bool getAutoSolve(){return this->autoSolve;}
    int getSteps(){return this->steps;}

    //setters
    void setName(QString name);
    void setScore(int score);
    void setDate(QDate date);
    void setTime(QTime time);
    void setAutoSolve(bool autoSolve);
    void setSteps(int steps);

private:
    QString name;
    int score;
    QDate date;
    QTime time;
    bool autoSolve;
    int steps;
};

#endif // PLAYER_H
