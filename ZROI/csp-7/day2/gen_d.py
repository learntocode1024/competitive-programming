#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

_n = ati([0, 7, 50, 1E5, 1E6]) # ati函数将数组中的每一个元素转换为整形，方便您可以使用1E4一类的数来表示数据大小
_m = ati([0, 11, 100, 1E6, 1E6]) 

# 这是一个图论题的数据生成器，该题目在洛谷的题号为P1339
for i in range(4, 5): # 即在[1, 4)范围内循环，也就是从1到3
    test_data = IO(file_prefix="subgraph", data_id=i) # 生成 heat[1|2|3].in/out 三组测试数据

    n = _n[i] # 点数
    m = _m[i] # 边数
    test_data.input_writeln(n, m) # 写入到输入文件里，自动以空格分割并换行
    test_data.input_writeln("1 1 2")
    graph = Graph.UDAG(n, m) # 生成一个n点，m边的随机图，边权限制为5
    test_data.input_writeln(graph.to_str(output=Edge.unweighted_edge)) # 自动写入到输入文件里，默认以一行一组u v w的形式输出
