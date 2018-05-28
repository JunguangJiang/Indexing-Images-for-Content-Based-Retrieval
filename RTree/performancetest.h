#ifndef PERFORMANCETEST_H
#define PERFORMANCETEST_H

void RTreeDiskAccessTest();//R树进行范围查询时的磁盘访问性能

void RTreeSplitNodesCountTest();//R数进行插入时的结点分裂次数性能测试

void RTreeDistanceTypeTest(int k=10);//R树选择不同的距离函数的性能测试

void FeatureDistractMethodTest(int k=10);//特征提取方法测试

#endif // PERFORMANCETEST_H
