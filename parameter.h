﻿#ifndef PARAMETER_H
#define PARAMETER_H
#include <QString>

const int Dimension = 77;//维度
const int LineNumber = 5613;//插入数据的个数

//实验内容4.1
const int DiskAccessQueryNumber = 5000;//磁盘访问查询个数
const int MaxNodeNumber = 16;
const int MinNodeNumber = 8;


#define RTree_ RTree<int, double, Dimension, double, MaxNodeNumber, MinNodeNumber, DistanceType>//R树的非模板类，每个结点中最多有16个子结点，最少8个子节点,采用L2距离

//实验内容4.3
const int DistanceTypeTestQueryNumber = 5000;//不同距离函数性能测试时的查询个数
const int DistanceType = 2;
//DistanceType=1时，采用L1距离；
//DistanceType=2时，采用L2距离；
//DistanceType=3时，采用L∞；
//DistanceType=4时，采用余弦相似度

//Windows下的相对路径
const QString suffix = "data/merge/";
const QString ImageDatabaseFile = (suffix+QString::number(Dimension)+"_"+QString::number(LineNumber)+".txt");//特征向量文件
//const QString ImageList = "data/image_"+QString::number(LineNumber)+".txt";//载入图片名文件
const QString ImageList = "data/imagelist.txt";//载入图片名文件

const QString DiskAccessQueryFile = suffix+"range_query_"+QString::number(Dimension)+"_"+QString::number(DiskAccessQueryNumber)+".txt";//实验内容1中进行范围查询的查询输入文件
const QString DiskAccessResultFile = "result/range_result.txt";//实验内容1中范围查询的结果文件

const QString SplitNodesCountFile = "result/split_nodes_count_result.txt";//实验4.1中结点分裂次数影响因素的结果文件

const QString DistanceTypeTestQueryFile = suffix+"query_"+QString::number(Dimension)+"_"+QString::number(DistanceTypeTestQueryNumber)+".txt";//实验内容4.3中knn查询输入文件
//const QString DistanceTypeTestImageList = "data/image_"+QString::number(DistanceTypeTestQueryNumber)+".txt";//实验内容4.3中knn查询输入对应的图片名文件
const QString DistanceTypeResultFile = "result/distance_type_result.txt";//实验内容4.3结果文件
const QString ExtractHist = "histExtraction.py";
const QString ExtractResult = "histfeature.txt";

#endif // PARAMETER_H
