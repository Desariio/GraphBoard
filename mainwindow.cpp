#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
int CPT = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setBtnEnable(false);
    ui->gridBoard->setSpacing(1);

    connect(ui->openFile, SIGNAL(triggered(bool)), this, SLOT(initBoardButton()));
    connect(ui->btnSolve, SIGNAL(clicked(bool)),this, SLOT(autoSolve()));
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(nextStep()));
    connect(ui->btnPrevious, SIGNAL(clicked(bool)), this, SLOT(previousStep()));
    connect(ui->btnCheckBoard, SIGNAL(clicked(bool)), this, SLOT(checkSolved()));

    connect(ui->actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBoardButton()
{
    setBtnEnable(true);

    QSize btnSize = QSize(40, 40);

    QString stringFile = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Documents/OCQT/ (*.txt)"));
    std::string file = stringFile.toStdString();
    const char* f = file.c_str();
    this->board = Board(f);

    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            QLineEdit *btn = new QLineEdit;
            btn->setValidator(new QIntValidator(1, 9, this));
            btn->setAlignment(Qt::AlignCenter);
            btn->setStyleSheet("background-color:white; color:black");
            if(this->board.getCells(i, j).getNumber() != 0){
                btn->setText(QString::number(this->board.getCells(i, j).getNumber()));
                btn->setFixedSize(btnSize);
                btn->setEnabled(false);
                ui->gridBoard->addWidget(btn, i, j);
            }else{
                btn->setText("");
                btn->setFixedSize(btnSize);
                ui->gridBoard->addWidget(btn, i, j);
            }
        }
    }
    this->listOfBoard.push_back(this->board);
    ++CPT;
}

void MainWindow::autoSolve()
{
    setBtnEnable(false);
    int steps = 0;
    Board tmp;
   // QThread *th = new QThread;
    //th->start();
    do
    {
        std::cout << this->board << '\n' << std::endl;
        tmp = this->board;
        this->board.step();
        if(tmp != this->board){
            for(int i = 0; i < 9; ++i){
                for(int j = 0; j < 9; ++j){
                     QWidget *w = ui->gridBoard->itemAtPosition(i, j)->widget();
                     QLineEdit *btn = qobject_cast<QLineEdit*>(w);
                    if(tmp.getCells(i, j).getNumber() != this->board.getCells(i, j).getNumber()){
                        btn->setText(QString::number(this->board.getCells(i, j).getNumber()));
                        btn->setStyleSheet("background-color:white; color:red");
                        ui->gridBoard->addWidget(btn, i, j);
                        //th->wait(1);
                        delay(1000);
                        btn->setStyleSheet("color:black");
                        this->listOfBoard.push_back(this->board);
                        ++CPT;
                        break;
                    }
                }
            }
        }
        ++steps;
    }while(this->board != tmp);

    if(this->board.isSolved())
        QMessageBox::information(this, "Solved", QString("Board is solved in %1 steps!").arg(steps));
    else
        QMessageBox::information(this, "Cannot be Solved","This board cannot be solved");
    //th->quit();
    setBtnEnable(true);
}

void MainWindow::nextStep()
{
    Board tmp = this->board;
    this->board.step();
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            QWidget *w = ui->gridBoard->itemAtPosition(i, j)->widget();
            QLineEdit *btn = qobject_cast<QLineEdit*>(w);
            if(tmp.getCells(i, j).getNumber() != this->board.getCells(i, j).getNumber()){
                btn->setText(QString::number(this->board.getCells(i, j).getNumber()));
                btn->setStyleSheet("background-color:white; color:red");
                ui->gridBoard->addWidget(btn, i, j);
                this->listOfBoard.push_back(this->board);
                ++CPT;
                //th->wait(1);
                //delay(1000);
                //btn->setStyleSheet("background-color:gray; color:black");
                break;
            }

        }
    }
    if(this->listOfBoard.size() > 1)
        ui->btnPrevious->setEnabled(true);
}

void MainWindow::previousStep()
{
    bool remove = false;
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            QWidget *w = ui->gridBoard->itemAtPosition(i, j)->widget();
            QLineEdit *btn = qobject_cast<QLineEdit*>(w);
            if(CPT > 2){
                auto tmp = this->listOfBoard[CPT-2];

                if(tmp.getCells(i, j).getNumber() !=
                        this->board.getCells(i,j).getNumber()){
                    std::cout << "CPT :" << CPT << std::endl;
                    btn->setText("");
                    ui->gridBoard->addWidget(btn, i, j);
                    this->listOfBoard.pop_back();
                    this->board = tmp;
                    --CPT;
                    remove =true;
                    break;
                }
            }else{
                auto tmp = this->listOfBoard[0];

                if(tmp.getCells(i, j).getNumber() !=
                        this->board.getCells(i,j).getNumber()){
                    std::cout << "CPT :" << CPT << std::endl;
                    btn->setText("");
                    ui->gridBoard->addWidget(btn, i, j);
                    this->listOfBoard.pop_back();

                    this->board = tmp;
                    --CPT;
                    remove =true;
                    break;
                }
            }
            if(remove) break;
        }
    }
    if(this->listOfBoard.size() < 2)
        ui->btnPrevious->setEnabled(false);
}

void MainWindow::checkSolved()
{  
    bool check = false;
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            QWidget *w = ui->gridBoard->itemAtPosition(i, j)->widget();
            QLineEdit *btn = qobject_cast<QLineEdit*>(w);
            if(this->board.getCells(i, j).getNumber() == 0){
                this->board.setCells(i, j, btn->text().toInt());
            }
        }
    }
    if(this->board.isSolved())
        QMessageBox::information(this, "Solved", QString("Congratulations ! \nYou solved this board !"));
    else
        QMessageBox::information(this, "Unsolved", QString("You failed !"));

    setBtnEnable(false);
}

void MainWindow::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::setBtnEnable(bool isEnable)
{
    ui->btnPrevious->setEnabled(isEnable);
    ui->btnNext->setEnabled(isEnable);
    ui->btnSolve->setEnabled(isEnable);
    ui->btnCheckBoard->setEnabled(isEnable);
}

