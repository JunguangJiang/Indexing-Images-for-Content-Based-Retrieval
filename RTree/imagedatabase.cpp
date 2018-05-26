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
    while(!in.atEnd()){
        QString line = in.readLine();
        if(line.length()>0 && line[0] == 'r'){
            QStringList list = line.split(' ');
            assert(list.size() == Dimension+1);
            for(int i=0; i<Dimension; i++){
                a_min[i] = a_max[i] =  list[i+1].toDouble();
                //qDebug() << a_min[i];
            }
            m_rtree.Insert(a_min, a_max, a_dataId++);//所有图片从0开始顺序编号
        }
    }
    return true;
}

bool m_resultCallBack(int id, void* queryResult){
    //qDebug() << "Hit data " << id;
    ((QVector<int>*)queryResult)->push_back(id);
    return true;//返回所有满足条件的结果
}

QVector<int> ImageDatabase::rangeQuery(double a_min[], double a_max[]){//范围查询
    int found_count=0;
    int visitedNodesNumber=0;
    m_queryResult.clear();
    m_rtree.Search(a_min, a_max, &m_resultCallBack, (void*)&m_queryResult, visitedNodesNumber);
    qDebug() << "总共访问了"<<visitedNodesNumber<<"个结点";
    return m_queryResult;
}

QVector<int> ImageDatabase::exactQuery(double a_point[]){
    return rangeQuery(a_point, a_point);
}

QVector<int> ImageDatabase::knnQuery(double p[], int k){
    int visitedNodesNumber=0;
    m_queryResult.clear();
    m_rtree.Search_KNN(p, k, &m_resultCallBack, (void*)&m_queryResult, visitedNodesNumber);
    qDebug() << "总共访问了"<<visitedNodesNumber<<"个结点";
    return m_queryResult;
}

bool readNthFeature(int n, double feature[], QString databaseFile){
    QFile file(databaseFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "图片数据库载入文件"<<databaseFile<<"打开失败!";
        return false;
    }

    QTextStream in(&file);
    QString line;
    while(!in.atEnd() && n>=0){
        line = in.readLine();
        if(line.length()>0 && line[0] == 'r'){
            n--;
        }
    }
    if(n==-1){
        QStringList list = line.split(' ');
        assert(list.size() == Dimension+1);
        for(int i=0; i<Dimension; i++){
            feature[i] = list[i+1].toDouble();
        }
        return true;
    }else{
        qDebug() << databaseFile<<"中不存在第"<<n<<"行特征向量";
        return false;
    }
}

bool readNthImageName(int n, QString& imageName, QString imageNameFile){
    QFile file(imageNameFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "图片数据库载入文件"<<imageNameFile<<"打开失败!";
        return false;
    }

    QTextStream in(&file);
    QString line;
    while(!in.atEnd() && n>=0){
        line = in.readLine();
        if(line.length()>0){
            n--;
        }
    }
    if(n==-1){
        imageName = line;
        return true;
    }else{
        qDebug() << imageNameFile<<"中不存在第"<<n<<"个图片";
        return false;
    }
}

bool readIdByName(int& id, QString imageName, QString imageNameFile){
    QFile file(imageNameFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "图片数据库载入文件"<<imageNameFile<<"打开失败!";
        return false;
    }

    QTextStream in(&file);
    QString line;
    id = 0;
    while(!in.atEnd())
    {
        line = in.readLine();
        if(line.length()!=imageName)
        {
            id++;
        }
        else
        {
            return true;
        }
    }
    qDebug() << imageNameFile<<"中不存在名为"<<imageName<<"的图片";
    return false;
}

double distance(double p1[], double p2[]){//欧式距离的平方
    double ret=0;
    for(int i=0; i<Dimension; i++){
        ret+=(p1[i]-p2[i])*(p1[i]-p2[i]);
    }
    return ret;
}
