#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include <QString>
#include <QProcess>
#include <QVector>
#include "RTree.h"
#include "parameter.h"
class ImageDatabase//图片数据库类
{
public:
    ImageDatabase();
    bool init(QString databaseFile);//根据databaseFile中的内容进行数据库的初始化
    QVector<int> rangeQuery(double a_min[], double a_max[], int& visitedNodesNumber);//范围查询
    QVector<int> rangeQuery(double a_min[], double a_max[]);//范围查询
    QVector<int> exactQuery(double a_point[]);//精确查询
    QVector<int> knnQuery(double p[], int k);//k最近邻查询，返回距离p最近的k个点
    double knnAccuracy(double p[], int k, QString label);//knn查询的准确度计算，label是对应的标签
    int getSplitNodesCount()const{return m_rtree.m_splitNodesCount;}//返回结点分裂总次数
    double distance(double p1[], double p2[]){return m_rtree.distance(p1,p2);}
    QString getLabel(int id){return m_imageLabel[id];}//返回id对应的图片名
    void getFeature(int id, double* p);
private:
    RTree_ m_rtree;
    QVector<int> m_queryResult;//存储查询结果
    QVector<QString> m_imageLabel;//存储标签
};

double distance(double p1[], double p2[]);//两个点之间的距离
#endif // IMAGEDATABASE_H
