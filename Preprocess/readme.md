# 数据的预处理
## python版本
- 在python3.6.3中运行正常。

## selectfeature.py
- 功能:将colorfeature.txt中提取若干维特征到另外一个文件
- 使用：python selectfeature.py -i data/feature.txt -o data/文件名 -c 0,1,2
（将提取第0、1、2维的向量）。详细功能参见python selectfeature.py -h。
- 注意：生成的文件中第1行为图片总数，第2行为处理后的特征数。

## selectline.py
- 功能:将输入文件提取若干行到另外一个文件
- 使用：详细功能参见python selectline.py -h。
- 注意：生成的文件中第1行为图片总数，第2行为处理后的特征数。
- 注意：为了能够处理imagelist.txt，对imagelist.txt进行了修改，请使用更新后的data/imagelist.txt。

## preprocess.py
- 功能：集成上述命令行，用于实验1中数据的快速生成。
- 注意：sh文件只能运行在unix或者类unix环境中，其他系统可以参照其中的代码实现类似功能。