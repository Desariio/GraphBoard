#include "player.h"

Player::Player()
{
    this->name = "";
    this->score = 0;
    //this->date = "";
    //this->time = "";
    this->autoSolve = false;
    this->steps = 0;
}

Player::Player(QString name, int score, QDate date, QTime time, bool autoSolve, int steps)
    :name(name), score(score), date(date), time(time), autoSolve(autoSolve), steps(steps)
{

}


// SETTERS
void Player::setName(QString name)
{
    this->name = name;
}
void Player::setScore(int score)
{
    this->score = score;
}
void Player::setDate(QDate date)
{
    this->date = date;
}
void Player::setTime(QTime time)
{
    this->time = time;
}
void Player::setAutoSolve(bool autoSolve)
{
    this->autoSolve = autoSolve;
}
void Player::setSteps(int steps)
{
    this->steps = steps;
}

