#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include <QString>
#include <QSet>
#include "RTree.h"
#include "parameter.h"
class ImageDatabase//图片数据库类
{
public:
    ImageDatabase();//构建一个维度为dimension的图片数据库
    void init(QString databaseFile);//根据databaseFile中的内容进行数据库的初始化
    void rangeQueryFromFile(QString queryFile,QString resultFile);//从queryFile中读取查询，将结果写到resultFile中
    QSet<int> rangeQuery(double a_min[], double a_max[]);//范围查询
    QSet<int> exactQuery(double a_point[]);//精确查询
    QSet<int> knnQuery(double p[], int k);//k最近邻查询，返回距离p最近的k个点
private:
    RTree_ m_rtree;
    QSet<int> m_queryResult;//存储查询结果
};

#endif // IMAGEDATABASE_H
