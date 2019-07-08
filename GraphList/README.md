# GraphList
这个文件是对图的一些基本操作，能完成对图的BFS、DFS、多源最短路、生成最小生成树（分别使用Kruskal和Prim）。

## GraphList.cpp
主程序，图的存储结构使用的是邻接表。

## test.txt
保存图的基本信息：
第1行：m n表示图中有m个点，n条边
第2 - n+1行：f t v表示编号f和t的点之间有边相连 ，且权重为v