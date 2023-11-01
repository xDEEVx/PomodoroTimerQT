#include "mainwindow.h"
#include <QFont>
#include <QPalette>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("~ pomodoro ~");
    setFixedSize(250, 120);

    titleLabel = new QLabel("POMODORO", this);
    titleLabel->setGeometry(0, 0, 250, 50);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("SF Pro Display Black", 30));
    titleLabel->setStyleSheet( " color: #ffffff; " );

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 50, 230, 25);
    progressBar->setStyleSheet( "color: #ffffff; selection-color: #000000; gridline-color: #393939; background-color: #393939; selection-background-color: #ffffff;" );

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    startButton = new QPushButton("START", this);
    startButton->setGeometry(10, 80, 100, 30);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startPomodoro()));
    startButton->setStyleSheet( " background-color: #393939; color: #ffffff; border-color: #393939; alternate-background-color: #393939;" );

    stopButton = new QPushButton("STOP", this);
    stopButton->setGeometry(140, 80, 100, 30);
    connect(stopButton, SIGNAL(clicked()), timer, SLOT(stop()));
    stopButton->setStyleSheet( " background-color: #393939; color: #ffffff; border-color: #393939; alternate-background-color: #393939;" );

    timeLeft = 25 * 60;
    isPomodoro = true;
}

MainWindow::~MainWindow()
{
}

void MainWindow::startPomodoro()
{
    timeLeft = 25 * 60;
    progressBar->setRange(0, timeLeft);
    progressBar->setValue(timeLeft);
    titleLabel->setText("POMODORO");
    titleLabel->setStyleSheet( " color: #ff3438; " );
    startButton->setText("RESTART");
    timer->start(1000);
}

void MainWindow::startBreak()
{
    timeLeft = 5 * 60;
    progressBar->setRange(0, timeLeft);
    progressBar->setValue(timeLeft);
    titleLabel->setText("BREAK");
    titleLabel->setStyleSheet( " color: #5fe053; " );
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
    } else {
        timer->stop();
        if (isPomodoro) {
            isPomodoro = false;
            startBreak();
        } else {
            isPomodoro = true;
            titleLabel->setText("POMODORO");
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
}
