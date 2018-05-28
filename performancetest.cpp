#include "performancetest.h"
#include "parameter.h"
#include "imagedatabase.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

void RTreeDiskAccessTest(){
    ImageDatabase m_database;
    if(!m_database.init(ImageDatabaseFile))return;//初始化数据库
    QFile file(DiskAccessQueryFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "实验内容1：范围查询文件"<<DiskAccessQueryFile<<"打开失败!";
        return;
    }
    QTextStream in(&file);
    in.readLine(); in.readLine();//舍弃前两行
    double a_min[Dimension],a_max[Dimension];
    int totalDiskAccess=0;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(' ');
        assert(list.size() == Dimension);
        for(int i=0; i<Dimension; i++){
            a_min[i] = list[i].toDouble();
        }
        line = in.readLine();
        list = line.split(' ');
        assert(list.size() == Dimension);
        for(int i=0; i<Dimension; i++){
            a_max[i] = list[i].toDouble();
        }
        int visitedNodesNumber = 0;
        QVector<int> queryResult = m_database.rangeQuery(a_min, a_max, visitedNodesNumber);
        totalDiskAccess += visitedNodesNumber;
    }

    double averageDiskAccessNumber = double(totalDiskAccess)/(double)(DiskAccessQueryNumber);
    qDebug() << "磁盘平均读写次数为" << averageDiskAccessNumber;
    file.close();
    QFile resultFile(DiskAccessResultFile);
    if(!resultFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug() << "实验内容1：范围查询的结果文件" << DiskAccessResultFile << "打开失败!";
        return;
    }
    QTextStream out(&resultFile);
    out << Dimension << "," << LineNumber << "," << averageDiskAccessNumber << endl;
    resultFile.close();
}

void RTreeSplitNodesCountTest(){
    ImageDatabase m_database;
    if(!m_database.init(ImageDatabaseFile))return;//初始化数据库
    QFile resultFile(SplitNodesCountFile);
    if(!resultFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug() << "实验内容4.1：结点分裂次数影响因素的结果文件" << SplitNodesCountFile<<"打开失败!";
        return;
    }
    QTextStream out(&resultFile);
    out << MaxNodeNumber << "," << LineNumber << "," << m_database.getSplitNodesCount() << endl;
    resultFile.close();
}

void RTreeDistanceTypeTest(int k){
    ImageDatabase m_database;
    if(!m_database.init(ImageDatabaseFile))return;//初始化数据库
    double averageScore = 0.0;

    double p[Dimension];
    QFile file(DistanceTypeTestQueryFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "实验内容4.3：knn查询文件"<<DistanceTypeTestQueryFile<<"打开失败!";
        return;
    }
    QTextStream in(&file);
    in.readLine(); in.readLine();//舍弃前两行
    int n=0;
    qDebug() << "loading";
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(' ');
        assert(list.size() == Dimension+1);
        for(int i=0; i<Dimension; i++){
            p[i] = list[i].toDouble();
        }
        averageScore += m_database.knnAccuracy(p, k, list[Dimension]);
        n++;
        if((n%100)==0)
            qDebug() << n << endl;
    }
    file.close();
    averageScore /= double(n);

    QFile resultFile(DistanceTypeResultFile);
    if(!resultFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug() << "实验内容4.3：不同相似度函数对查询准确度影响的结果文件" << DistanceTypeResultFile<<"打开失败!";
        return;
    }
    QTextStream out(&resultFile);
    out << Dimension << "," << LineNumber << "," << averageScore << endl;
    resultFile.close();
}
