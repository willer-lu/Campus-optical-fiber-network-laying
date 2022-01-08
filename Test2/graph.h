#pragma once
#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;
class Arc{
public:
    int vex1=0, vex2=0,cost=0;//边两头的节点及边的权重值，即铺设所需要的费用
    Arc() {};//构造函数
    ~Arc() {};//析构函数
    void Input(int, int, int);//输入边相关参数的函数
    void SwapArc(Arc&);//交换两条边，堆排序中使用
};
class Graph {
public:
    int vexNum, arcNum;//顶点的数量，边的数量
    int* vexs;//连通分量
    class Arc* arcs;//边类
    int* minCSTree;//最小生成树数组，该数组保存最小路径的边的序号
    Graph(int m = 0, int n = 0);//构造函数
    ~Graph();//析构函数
    void Input_one(int, int, int, int);//逐个输入
    void Input_one_random(int);//随机输入一个
    void InFile(int, int&, int&, int&);//读取文件
    void OutFile(int);//输出文件
    void Kruskal();//最小生成树算法
    int RepetExam(int, int, int);//检查人工输入时是否有重复数据
    int Find_MFset(int);//并集树的查找
    int Merge_MFset(int, int);//并集树的合并
    bool Validate(class Arc);//判断边是否在同一集合
    void HeapAdjust(int, int);//堆调整
    void HeapInit();//堆初始化
    void HeapSort(int);//堆排序
};
int CountLines();//计算文本的行数
void point(int n, int& a, int& b);//点的映射
