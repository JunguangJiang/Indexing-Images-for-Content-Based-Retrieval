#include "imagedatabasetest.h"
#include "imagedatabase.h"
#include "parameter.h"
#include <QString>
#include <vector>
ImageDatabaseTest::ImageDatabaseTest()
{

}

void ImageDatabaseTest::knnQueryTest(){
    ImageDatabase m_database;
    m_database.init(ImageDatabaseFile);//初始化数据库
    double p[9]={3096, 1755, 5025, 2387, 1110, 2148, 2511, 1428, 2303};//查询图片的特征向量
    QVector<int> queryResult = m_database.knnQuery(p, 10);//返回knn查询结果，按照相关性从大到小排序，queryResult中的每个元素对应一个整数编号id
    double feature[Dimension];
    foreach (int id, queryResult) {
        readNthFeature(id, feature, ImageDatabaseFile);//从文件中读出id所对应的特征向量
        qDebug()<<"Hit:编号="<<id<<"特征向量="<<std::vector<double>(feature, feature+Dimension) << "与查询点的距离平方为："<<distance(p, feature);
    }
}
