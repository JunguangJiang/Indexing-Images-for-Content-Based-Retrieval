#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include <QString>
#include <QVector>
#include "RTree.h"
#include "parameter.h"
class ImageDatabase//图片数据库类
{
public:
    ImageDatabase();//构建一个维度为dimension的图片数据库
    bool init(QString databaseFile);//根据databaseFile中的内容进行数据库的初始化
    void rangeQueryFromFile(QString queryFile,QString resultFile);//从queryFile中读取查询，将结果写到resultFile中
    QVector<int> rangeQuery(double a_min[], double a_max[]);//范围查询
    QVector<int> exactQuery(double a_point[]);//精确查询
    QVector<int> knnQuery(double p[], int k);//k最近邻查询，返回距离p最近的k个点
private:
    RTree_ m_rtree;
    QVector<int> m_queryResult;//存储查询结果
};

bool readNthFeature(int n, double feature[], QString databaseFile);//读入第n行的特征向量feature（用于调试）
bool readNthImageName(int n, QString& imageName, QString imageNameFile);//读入第n行的图片名
bool readIdByName(int& id, QString imageName, QString imageNameFile);//根据图片名得到ID
double distance(double p1[], double p2[]);

#endif // IMAGEDATABASE_H
