#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>
#include<QDir>
#include<QListWidget>
#include"imagedatabase.h"
#include<QFileDialog>

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
    void selectImg(QListWidgetItem*);
    void selectLocal(QString);
    void on_Search_clicked();

    void on_pushButton_clicked();

    void on_selectLocal_clicked();

private:
    Ui::MainWindow *ui;
    QString selected;
    QFileDialog *fileDialog;
    int selectedID;
    void getAllImg();
    ImageDatabase m_database;
    bool inDatabase;//所需查询的图片是否在数据库中，默认为否。
};

#endif // MAINWINDOW_H
