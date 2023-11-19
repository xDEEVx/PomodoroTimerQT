#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.setStyleSheet( " background-color: #303030; " );
    mainWindow.show();
    return app.exec();
}
