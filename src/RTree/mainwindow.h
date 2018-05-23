#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>
#include<QDir>
#include<QListWidget>
#include"imagedatabase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadImg_clicked();
    void selectImg(QListWidgetItem*);
    void on_Search_clicked();

private:
    Ui::MainWindow *ui;
    QString selected;
    int selectedID;
    void getAllImg();
    ImageDatabase m_database;
};

#endif // MAINWINDOW_H
