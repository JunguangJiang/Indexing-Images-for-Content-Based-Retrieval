# -*- coding: utf-8 -*-
# 对图片的向量数据中挑选出部分行
def select_line(input, output, m):
    output_file = open(file=output, mode='w')
    output_file.truncate()  # 首先清空输出文件的内容

    with open(file=input, mode='r') as input_file:
        n = int(input_file.readline()) # 读入原先的行数
        if m == 0:
            m = n
        output_file.write(str(m)+'\n')
        output_file.write(input_file.readline())
        if m >= n: # 直接复制所有内容
            for eachline in input_file:
                output_file.write(eachline)
        else:
            k = int(n/m)
            id = 0
            for eachline in input_file:
                if id % k == 0 and id < k*m:
                    output_file.write(eachline)
                id += 1

    output_file.close()


def usage():
    print("从图片的向量数据中提取部分行")
    print("-i filename 指定输入文件名为filename")
    print("-o filename 指定输出文件名为filename")
    print("-m 保留m行")
    print("-h 查看提示")

import getopt
import sys

if __name__ == '__main__':
    input = "selected_feature.txt"
    output = "selected_line.txt"
    m = 0 # 保留m行
    try:
        opts, args = getopt.getopt(sys.argv[1:], "i:o:m:h", ["input=", "output=", "help"])
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
        elif o in ("-m"):
           m = int(a)

    select_line(input=input, output=output, m=m)