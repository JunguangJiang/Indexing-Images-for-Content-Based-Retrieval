#ifndef PARAMETER_H
#define PARAMETER_H
#include <QString>

#define Dimension 8//维度
#define LineNumber 1000//插入数据的个数

#define MaxNodeNumber 16
#define MinNodeNumber 8
#define RTree_ RTree<int, double, Dimension, double, MaxNodeNumber, MinNodeNumber>//R树的非模板类，维度为9，每个结点中最多有16个子结点，最少8个子节点

//Windows下的相对路径
const QString ImageDatabaseFile = ("data/"+QString::number(Dimension)+"_"+QString::number(LineNumber)+".txt");//特征向量文件
const QString ImageList = "data/image_"+QString::number(LineNumber)+".txt";//载入图片名文件

#endif // PARAMETER_H
