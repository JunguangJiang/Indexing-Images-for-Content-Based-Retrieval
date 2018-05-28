## 各个文件的功能说明
- data  存储所有的数据，如果程序运行时打不开文件，可以考虑移动这个文件夹的位置
- parameter.h 定义了文件路径、R树的参数等。在修改文件路径、或者R树参数时，只需要修改这个文件
- imagedatabase.h 图片数据库，在做图形界面时需要调用其中init和knnSearch。在imagedatabasetest.cpp的knnQueryTest中提供了一个使用样例。
- RTree.h R树的底层实现，做图形界面时可以无视这个文件。

