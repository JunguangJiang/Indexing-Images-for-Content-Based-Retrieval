#include "mainwindow.h"
#include <QApplication>
//#include "imagedatabasetest.h"
int main(int argc, char *argv[])
{
    //ImageDatabaseTest test;
    //test.knnQueryTest();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
