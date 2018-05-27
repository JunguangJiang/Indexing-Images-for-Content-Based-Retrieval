#include "mainwindow.h"
#include <QApplication>
#include "performancetest.h"
int main(int argc, char *argv[])
{
//    RTreeDiskAccessTest();
//    RTreeSplitNodesCountTest();
//    RTreeDistanceTypeTest(1);
//    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
