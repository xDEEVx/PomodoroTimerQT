#include "mainwindow.h"
#include <QFont>
#include <QPalette>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("~ pomodoro ~");
    setFixedSize(250, 200);

    titleLabel = new QLabel("POMODORO", this);
    titleLabel->setGeometry(0, 20, 250, 50);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("SF Pro Black", 30));
    titleLabel->setStyleSheet( " color: #ffffff; " );

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 95, 230, 30);
    progressBar->setStyleSheet( "color: #ffffff; selection-color: #000000; gridline-color: #303030; background-color: #303030; selection-background-color: #ffffff;" );
    progressBar->setFont(QFont("SF Pro Black", 12));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));


    startButton = new QPushButton("START", this);
    startButton->setGeometry(10, 130, 100, 30);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startPomodoro()));
    startButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    startButton->setFont(QFont("SF Pro Black", 12));

    stopButton = new QPushButton("STOP", this);
    stopButton->setGeometry(140, 130, 100, 30);
    connect(stopButton, SIGNAL(clicked()), timer, SLOT(stop()));
    stopButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    stopButton->setFont(QFont("SF Pro Black", 12));

    changeButton = new QPushButton("CHANGE", this);
    changeButton->setGeometry(10, 165, 230, 30);
    connect(changeButton, SIGNAL(clicked()), this, SLOT(change()));
    changeButton->setStyleSheet( " background-color: #444444; color: #ffffff; border-width: 2px; border-radius: 10px; border-style: solid; border-color: #444444; alternate-background-color: #303030;" );
    changeButton->setFont(QFont("SF Pro Black", 12));

    timeLeft = 25 * 60;
    isPomodoro = true;
    isBreak = false;
}

MainWindow::~MainWindow()
{
}

void MainWindow::startPomodoro()
{
    isBreak = false;
    timeLeft = 25 * 60;
    progressBar->setRange(0, timeLeft);
    progressBar->setValue(timeLeft);
    titleLabel->setText("POMODORO");
    titleLabel->setStyleSheet( " color: #ff3438; " );
    progressBar->setStyleSheet( "color: #ff3438; selection-color: #000000; gridline-color: #303030; background-color: #303030; selection-background-color: #ff3438;" );
    startButton->setText("RESTART");
    timer->start(1000);
}

void MainWindow::startBreak()
{
    isBreak = true;
    timeLeft = 5 * 60;
    progressBar->setRange(0, timeLeft);
    progressBar->setValue(timeLeft);
    titleLabel->setText("BREAK");
    titleLabel->setStyleSheet( " color: #5fe053; " );
    progressBar->setStyleSheet( "color: #5fe053; selection-color: #000000; gridline-color: #303030; background-color: #303030; selection-background-color: #5fe053;" );
    setWindowTitle("~ break ~");
    timer->start(1000);
} 

void MainWindow::updateTimer()
{
    if (timeLeft > 0) {
        timeLeft--;
        progressBar->setValue(timeLeft);

        int minutes = timeLeft / 60;
        int seconds = timeLeft % 60;

        QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        titleLabel->setText(timeString);
        titleLabel->setFont(QFont("SF Pro Black", 50));
    } else {
        timer->stop();
        if (isPomodoro) {
            isPomodoro = false;
            startBreak();
        } else {
            isPomodoro = true;
            titleLabel->setText("POMODORO");
            titleLabel->setFont(QFont("SF Pro Black", 30));
        }
    }
}

void MainWindow::stop()
{
    titleLabel->setText("POMODORO");
    setWindowTitle("pomodoro");
    timeLeft=0;
    progressBar->setValue(0);
    isPomodoro = false;
    isBreak = false;
}

void MainWindow::change()
{
    if(isBreak) {
        startPomodoro();
    }
    else {
        startBreak();
    }
}
