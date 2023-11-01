#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startPomodoro();
    void updateTimer();
    void startBreak();
    void stop();

private:
    QLabel *titleLabel;
    QProgressBar *progressBar;
    QTimer *timer;
    QMessageBox *notificationwork;
    QMessageBox *notificationpause;
    int timeLeft;
    bool isPomodoro;
    QPushButton *startButton;
    QPushButton *stopButton;
};

#endif // MAINWINDOW_H
