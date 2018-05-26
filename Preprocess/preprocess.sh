prefix="data/" 
suffix=".txt"
input="color_feature"
input_image="imagelist"
# 首先从原有的特征向量中提取出部分向量
python selectfeature.py -i ${prefix}${input}${suffix} -o ${prefix}4${suffix} -c 0,1,2,3 #提取前4个特征
python selectfeature.py -i ${prefix}${input}${suffix} -o ${prefix}8${suffix} -c 0,1,2,3,4,5,6,7 #提取前8个特征

# 然后从中取出特定行
for lines in {1000,2000,3000,4000,5000}
do
    for features in {4,8}
    do
        python selectlines.py -i ${prefix}${features}${suffix} -o ${prefix}${features}_${lines}${suffix} -m ${lines} # 从特征向量文件中取lines行
    done
    python selectlines.py -i ${prefix}${input_image}${suffix} -o ${prefix}image_${lines}${suffix} -m ${lines} # 从图片名文件中取对应的lines行
done
