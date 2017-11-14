#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/icons/Images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    for(long index = 0;index < 1000000000;index++);

    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
