#ifndef PARAMETER_H
#define PARAMETER_H
#include <QString>

//Windows下的相对路径
#define ImageDatabaseFile "data/color_feature.txt"
#define ImageQuery "data/color_feature.query"

//（Mac下的相对路径比较奇葩，就直接用绝对路径替代了）
//#define ImageDatabaseFile "/Users/jiangjunguang/Files/Learning/ADS/Project1/Indexing-Images-for-Content-Based-Retrieval/data/color_feature.txt"
//#define ImageQuery "/Users/jiangjunguang/Files/Learning/ADS/Project1/Indexing-Images-for-Content-Based-Retrieval/data/color_feature.query"

#define Dimension 9
#define RTree_ RTree<int, double, Dimension, double, 16, 8>//R树的非模板类，维度为9，每个结点中最多有16个子结点，最少8个子节点

#endif // PARAMETER_H
