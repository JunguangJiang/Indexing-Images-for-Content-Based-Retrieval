#include "mainwindow.h"
#include <QApplication>
#include "imagedatabase.h"
#include "parameter.h"
int main(int argc, char *argv[])
{
    ImageDatabase m_database;
    m_database.init(ImageDatabaseFile);
    double a_min[9]={3096, 1755, 5025, 2387, 1110, 2148, 2511, 1428, 2303};
    m_database.exactQuery(a_min);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
