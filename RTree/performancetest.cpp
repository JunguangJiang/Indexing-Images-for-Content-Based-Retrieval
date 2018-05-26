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

void RTreeDistanceTypeTest(){
    ImageDatabase m_database;
    if(!m_database.init(ImageDatabaseFile))return;//初始化数据库
    double p[8]={1553, 4367, 6897, 2239, 3278, 2712, 3094, 3553};
    qDebug() << "KNN查询准确度为" << m_database.knnAccuracy(p,10,"n03877845");
}
