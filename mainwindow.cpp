//   Copyright 2019 | Vladimir Simonyan | simonyan.vlad@gmail.com   // 



#include <QtGui>
#include <QWidget>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const int N = 21, M = 14;
int sblocks[N][M];
int block_type, block_rot, block_i, block_j, block_col;
int next_block_type, next_block_rot, next_block_col;
int score, gop;
bool pause;

int blocks[7][4][4][4] = {
    {
        {{0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}},

        {{0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}}
    },

    {
        {{0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}},

        {{1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

        {{0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    },

    {
        {{0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

        {{0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

        {{0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    },

    {
        {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}}
    },

    {
        {{0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},

        {{0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    },

    {
        {{0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}},

        {{1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},

        {{0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}}
    },

    {
        {{0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

        {{0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}},

        {{0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}}
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bg[0] = new QWidget(this);
    bg[0]->setGeometry(0,0,311,620);
    bg[0]->setStyleSheet("background-color:black;");

    for (int i = 0; i < N-1; i++){
        for (int j = 2; j < M-2; j++){
            int ii = i, jj = j-2;
            elem[ii][jj] = new QWidget(this);
            elem[ii][jj]->setGeometry(1+jj*31,ii*31,30,30);
            elem[ii][jj]->setStyleSheet("background-color:lightgray;");
        }
    }

    bg[1] = new QWidget(this);
    bg[1]->setGeometry(311,0,120,620);
    bg[1]->setStyleSheet("background-color:lightgray;");

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ekox[i][j] = new QWidget(this);
            ekox[i][j]->setGeometry(311+20+j*20,150+i*20,19,19);
            ekox[i][j]->setStyleSheet("background-color:gray;");
        }
    }

    tmr = new QTimer;
    connect(tmr, SIGNAL(timeout()), this, SLOT(Step()));
    tmr->start();
    MainWindow::NewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::NewGame() {
    score = 0;
    pause = false;
    next_block_type = rand() % 7;
    next_block_rot = rand() % 4;
    next_block_col = next_block_type + 1;
    MainWindow::TimeSet();
    MainWindow::CreateBlock();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(j == 0 || j == 1 || j == M-2 || j == M-1) sblocks[i][j] = 1;
            else if(i == N-1) sblocks[i][j] = 1;
            else sblocks[i][j] = 0;
        }
    }
}

void MainWindow::CreateBlock() {
    block_type = next_block_type;
    block_rot = next_block_rot;
    block_col = next_block_col;
    if ((blocks[block_type][block_rot][0][0] + blocks[block_type][block_rot][0][1] + blocks[block_type][block_rot][0][2] + blocks[block_type][block_rot][0][3]) > 0)
        gop = block_i = 1;
    else gop = block_i = 0;
    block_j = 4;
    next_block_type = rand() % 7;
    next_block_rot = rand() % 4;
    next_block_col = next_block_type + 1;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (blocks[next_block_type][next_block_rot][i][j]) {
                if (next_block_col == 1 || next_block_col == 7) ekox[i][j]->setStyleSheet("background-color:#fff3b200;");
                else if (next_block_col == 2 || next_block_col == 6) ekox[i][j]->setStyleSheet("background-color:#ff77b900;");
                else if (next_block_col == 3) ekox[i][j]->setStyleSheet("background-color:#ff2572eb;");
                else if (next_block_col == 4) ekox[i][j]->setStyleSheet("background-color:#ffc1004f;");
                else if (next_block_col == 5) ekox[i][j]->setStyleSheet("background-color:#ffff1d77;");
            }
            else ekox[i][j]->setStyleSheet("background-color:gray;");
        }
    }
}

void MainWindow::Step() {
    if(!pause) {
        bool flg = true;
        for (int i = -1; i < 3; i++) {
            for (int j = -1; j < 3; j++) {
                if ((sblocks[block_i + 1 + i][block_j + j + 2] * blocks[block_type][block_rot][i + 1][j + 1]) != 0) {
                    flg = false;
                    break;
                }
            }
            if(!flg) break;
        }

        if (flg) block_i++;
        else MainWindow::FixBlock();
        MainWindow::Update();
    }
}

void MainWindow::FixBlock() {
    for (int i = -1; i < 3; i++)
        for (int j = -1; j < 3; j++)
            if(blocks[block_type][block_rot][i + 1][j + 1]) sblocks[block_i + i][block_j + j + 2] = block_col;
    if (block_i == gop) {     // Game Over
        MainWindow::GameOver();
    }
    else {
        MainWindow::CreateBlock();
        MainWindow::Test();
    }
}

void MainWindow::Update() {
    for (int i = 0; i < N-1; i++){
        for (int j = 2; j < M-2; j++){
            int ii = i, jj = j-2;
            elem[ii][jj]->setStyleSheet("background-color:lightgray;");
            if (sblocks[i][j] == 1 || sblocks[i][j] == 7) elem[ii][jj]->setStyleSheet("background-color:#fff3b200;");
            else if (sblocks[i][j] == 2 || sblocks[i][j] == 6) elem[ii][jj]->setStyleSheet("background-color:#ff77b900;");
            else if (sblocks[i][j] == 3) elem[ii][jj]->setStyleSheet("background-color:#ff2572eb;");
            else if (sblocks[i][j] == 4) elem[ii][jj]->setStyleSheet("background-color:#ffc1004f;");
            else if (sblocks[i][j] == 5) elem[ii][jj]->setStyleSheet("background-color:#ffff1d77;");
        }
    }
    for (int i = -1; i < 3; i++){
        for (int j = -1; j < 3; j++){
            if(blocks[block_type][block_rot][i+1][j+1]) {
                if (block_col == 1 || block_col == 7) elem[block_i+i][block_j+j]->setStyleSheet("background-color:#fff3b200;");
                else if (block_col == 2 || block_col == 6) elem[block_i+i][block_j+j]->setStyleSheet("background-color:#ff77b900;");
                else if (block_col == 3) elem[block_i+i][block_j+j]->setStyleSheet("background-color:#ff2572eb;");
                else if (block_col == 4) elem[block_i+i][block_j+j]->setStyleSheet("background-color:#ffc1004f;");
                else if (block_col == 5) elem[block_i+i][block_j+j]->setStyleSheet("background-color:#ffff1d77;");
            }
        }
    }
    MainWindow::TimeSet();
}

void MainWindow::Test() {
    for (int i = N-2; i >= 0; i--){
        bool flag = true;
        for (int j = 2; j < M-2; j++){
            if (sblocks[i][j] == 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
           for (int k = i; k > 0; k--){
               for (int j = 2; j < M-2; j++){
                   sblocks[k][j] = sblocks[k-1][j];
               }
           }
           score += 100;
           MainWindow::Update();
           MainWindow::Test();
        }
    }
}

void MainWindow::TimeSet() {
    if (score < 500) tmr->setInterval(300);
    else if (score >= 500 && score < 1000) tmr->setInterval(250);
    else if (score >= 1000) tmr->setInterval(200);
}

void MainWindow::GameOver() {
    tmr->setInterval(500);
    for (int i = 0; i < N-1; i++) {
        for (int j = 2; j < M-3; j++) {
            sblocks[i][j] = 3;
        }
    }
    MainWindow::Update();
    MainWindow::NewGame();
}

void MainWindow::Pause() {
    pause = !pause;
}

void MainWindow::Left() {
    if(!pause) {
        bool flg = true;
        for (int i = -1; i < 3; i++) {
            for (int j = -1; j < 3; j++) {
                if ((sblocks[block_i + i][block_j - 1 + j + 2] * blocks[block_type][block_rot][i + 1][j + 1]) != 0) {
                    flg = false;
                    break;
                }
            }
            if(!flg) break;
        }

        if (flg) {
            block_j--;
            MainWindow::Update();
        }
    }
    else MainWindow::Pause();
}

void MainWindow::Right() {
    if(!pause) {
        bool flg = true;
        for (int i = -1; i < 3; i++) {
            for (int j = -1; j < 3; j++) {
                if ((sblocks[block_i + i][block_j + 1 + j + 2] * blocks[block_type][block_rot][i + 1][j + 1]) != 0) {
                    flg = false;
                    break;
                }
            }
            if(!flg) break;
        }

        if (flg) {
            block_j++;
            MainWindow::Update();
        }
    }
    else MainWindow::Pause();
}

void MainWindow::Rotate() {
    if (!pause) {
        if(block_i != 0) {
            bool flg = true;
            for (int i = -1; i < 3; i++) {
                for (int j = -1; j < 3; j++) {
                    if ((sblocks[block_i + i][block_j + j + 2] * blocks[block_type][(block_rot + 1) % 4][i + 1][j + 1]) != 0) {
                        flg = false;
                        break;
                    }
                }
                if(!flg) break;
            }
            if(flg) block_rot = (block_rot + 1) % 4;
        }
    }
    else MainWindow::Pause();
    MainWindow::Update();
}

void MainWindow::Drop() {
    tmr->setInterval(0);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_8 || event->key() == Qt::Key_W) {MainWindow::Rotate();}
    else if(event->key() == Qt::Key_2 || event->key() == Qt::Key_S) {MainWindow::Drop();}
    else if(event->key() == Qt::Key_6 || event->key() == Qt::Key_D) {MainWindow::Right();}
    else if(event->key() == Qt::Key_4 || event->key() == Qt::Key_A) {MainWindow::Left();}
    else if(event->key() == Qt::Key_P) {MainWindow::Pause();}
    QMainWindow::keyPressEvent(event);
}
