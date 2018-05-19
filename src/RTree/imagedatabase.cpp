#include "imagedatabase.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
ImageDatabase::ImageDatabase(){

}

void ImageDatabase::init(QString databaseFile){
    QFile file(databaseFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "图片数据库载入文件"<<databaseFile<<"打开失败!";
        return;
    }

    QTextStream in(&file);
    double a_min[dimension],a_max[dimension];
    int a_dataId=0;
    while(!in.atEnd()){
        QString line = in.readLine();
        if(line.length()>0 && line[0] == 'r'){
            QStringList list = line.split(' ');
            assert(list.size() == dimension+1);
            for(int i=0; i<dimension; i++){
                a_min[i] = a_max[i] =  list[i+1].toDouble();
                qDebug() << a_min[i];
            }
            m_rtree.Insert(a_min, a_max, a_dataId++);//所有图片从0开始顺序编号
        }
    }
}

bool m_resultCallBack(int id, void* queryResult){
    qDebug() << "Hit data " << id;
    ((QSet<int>*)queryResult)->insert(id);
    return true;//返回所有满足条件的结果
}

QSet<int> ImageDatabase::rangeQuery(double a_min[], double a_max[]){//范围查询
    int found_count=0;
    int visitedNodesNumber=0;
    m_queryResult.clear();
    m_rtree.Search(a_min, a_max, &m_resultCallBack, (void*)&m_queryResult, visitedNodesNumber);
    qDebug() << "总共访问了"<<visitedNodesNumber<<"个结点";
    return m_queryResult;
}

QSet<int> ImageDatabase::exactQuery(double a_point[]){
    return rangeQuery(a_point, a_point);
}


