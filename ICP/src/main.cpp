/**
  * Main
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
/*
*/
