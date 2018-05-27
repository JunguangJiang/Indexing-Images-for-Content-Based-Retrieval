#include "imagedatabase.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
ImageDatabase::ImageDatabase(){

}

bool ImageDatabase::init(QString databaseFile)
{
    QFile file(databaseFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "图片数据库载入文件"<<databaseFile<<"打开失败!";
        return false;
    }

    QTextStream in(&file);
    double a_min[Dimension],a_max[Dimension];
    int a_dataId=0;
    in.readLine(); in.readLine();//舍弃前两行
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(' ');
        assert(list.size() == Dimension+1);
        for(int i=0; i<Dimension; i++){
            a_min[i] = a_max[i] =  list[i].toDouble();
        }
        m_imageLabel.push_back(list[Dimension]);
        m_rtree.Insert(a_min, a_max, a_dataId++);//所有图片从0开始顺序编号
    }
    file.close();
    return true;
}

bool m_resultCallBack(int id, void* queryResult){
    //qDebug() << "Hit data " << id;
    ((QVector<int>*)queryResult)->push_back(id);
    return true;//返回所有满足条件的结果
}

QVector<int> ImageDatabase::rangeQuery(double a_min[], double a_max[]){//范围查询
    int visistedNodesNumber=0;
    return rangeQuery(a_min, a_max, visistedNodesNumber);
}

QVector<int> ImageDatabase::rangeQuery(double a_min[], double a_max[], int& visitedNodesNumber){//范围查询
    m_queryResult.clear();
    m_rtree.Search(a_min, a_max, &m_resultCallBack, (void*)&m_queryResult, visitedNodesNumber);
    //qDebug() << "总共访问了"<<visitedNodesNumber<<"个结点";
    return m_queryResult;
}

QVector<int> ImageDatabase::exactQuery(double a_point[]){
    return rangeQuery(a_point, a_point);
}

QVector<int> ImageDatabase::knnQuery(double p[], int k){
    int visitedNodesNumber=0;
    m_queryResult.clear();
    m_rtree.Search_KNN(p, k, &m_resultCallBack, (void*)&m_queryResult, visitedNodesNumber);
    //qDebug() << "总共访问了"<<visitedNodesNumber<<"个结点";
    return m_queryResult;
}

double ImageDatabase::knnAccuracy(double p[], int k, QString label){
    knnQuery(p, k);
    int correctTimes=0;
    foreach (int id, m_queryResult) {
        if(getLabel(id) == label){
            correctTimes++;
        }
    }
    return double(correctTimes)/double(k);
}

double distance(double p1[], double p2[]){
    return RTree_::distance(p1,p2);
}//两个点之间的距离
