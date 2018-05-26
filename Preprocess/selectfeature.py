# -*- coding: utf-8 -*-
# 对图片的向量数据中挑选出部分特征向量
def select_feature(input, output, convert):
    output_file = open(file=output, mode='w')
    output_file.truncate()  # 首先清空输出文件的内容

    lines_number = 0 # 行数

    with open(file=input, mode='r') as input_file:
        for eachline in input_file:
            if eachline[0] == 'r':
                lines_number += 1

    features_number = len(convert)  # 特征数目
    output_file.write(str(lines_number)+'\n'+str(features_number)+'\n') #第一行记录总行数和每一行的特征数

    with open(file=input, mode='r') as input_file:
        for eachline in input_file:
            if eachline[0] == 'r':
                list = eachline.strip('rect ').strip('\n').split(' ')
                newlist = []
                for i in convert:
                    newlist.append(list[i])
                output_file.write(' '.join(newlist))
                output_file.write('\n')

    output_file.close()


def usage():
    print("从图片的向量数据中提取部分特征")
    print("-i filename 指定输入文件名为filename")
    print("-o filename 指定输出文件名为filename")
    print("-c 0,2,4,7 保留原向量中第0、2、4、7维的数据")
    print("-h 查看提示")

import getopt
import sys

if __name__ == '__main__':
    input = "color_feature.txt"
    output = "selected_feature.txt"
    convert = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    try:
        opts, args = getopt.getopt(sys.argv[1:], "i:o:c:h", ["input=", "output=", "convert=", "help"])
    except getopt.GetoptError as err:
        print(err)
        usage()
        sys.exit(2)
    for o,a in opts:
        if o in ("-i", "--input"):
            input = a
        elif o in ("-o", "--output"):
            output = a
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-c", "--convert"):
            convert = a.strip(',').split(',')
            convert = [int(x) for x in convert]
    select_feature(input=input, output=output, convert=convert)