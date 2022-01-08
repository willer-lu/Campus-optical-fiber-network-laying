#include "pch.h"
#include "graph.h"
#include<stdlib.h>
using namespace std;
void Arc::Input(int VEX1, int VEX2, int COST) {//将传进来的参数赋值给类中的相应变量
    vex1 = VEX1;
    vex2 = VEX2;
    cost = COST;
}
void Arc::SwapArc(class Arc&arc) {//交换两条边，对应堆排序中的交换，类似复制构造函数
    int tempArc,tempCost;//辅助变量实现交换
    tempArc = vex1;
    vex1 = arc.vex1;
    arc.vex1 = tempArc;
    tempArc = vex2;
    vex2 = arc.vex2;
    arc.vex2 = tempArc;
    tempCost = cost;
    cost = arc.cost;
    arc.cost = tempCost;
}
int Graph::Find_MFset(int i) {//并集树的查找 对于第一次查找的顶点返回其序号 否则返回对应的连通分量
    int j,t=0;
    for (j = i; vexs[j] > 0; j = vexs[j]);
    return j;
}
int  Graph::Merge_MFset(int i, int j) {//并集树的合并 以连通分量较小的为基准
    if (vexs[i] > vexs[j]) {
        vexs[j] += vexs[i];
        vexs[i] = j;
    }
    else {
        vexs[i] += vexs[j];
        vexs[j] = i;
    }
    return  true;
}
bool Graph::Validate(class Arc arc) {//若边的两个顶点在同一集合返回false否则返回true
    if (Find_MFset(arc.vex1) == Find_MFset(arc.vex2))return false;
    return true;
}
void Graph::HeapAdjust(int s, int m) {//堆调整
    class Arc rc = arcs[s]; // 暂存 R[s] 
    for (int j = s * 2; j <= m; j = j * 2) {//比较节点和它的两个孩子节点选出三者最小
        if (j<m && arcs[j].cost>arcs[j + 1].cost)j++;//左右子树根之间进行比较，令j返回关键字较小位置
        if (!(rc.cost > arcs[j].cost))break;//作根与子树根之间的比较，<=说明找到rc的插入位置
        arcs[s] = arcs[j];
        s = j;// 否则记录上移，尚需继续往下调整
    }
    arcs[s] = rc;// 将调整前的堆顶记录插入到 s 位置
}
void Graph::HeapInit() {//堆的初始化（小顶堆）
    for (int i = arcNum / 2; i > 0; i--)HeapAdjust(i, arcNum);
}
void Graph::HeapSort(int i) {//堆排序
    arcs[1].SwapArc(arcs[i]);//将第一条边和第i条边进行交换，即得到最小的边
    if (i != 1)HeapAdjust(1, i - 1);//交换完成后对剩下的进行堆调整
}
Graph::Graph(int nVexNum, int nArcNum) {
    vexNum = nVexNum;//顶点数目
    arcNum = nArcNum;//边的数目
    vexs = new  int[vexNum + 1];
    arcs = new class Arc[arcNum + 1];//开辟地址空间
    minCSTree = new int[vexNum];//新建最小生成树数组
    minCSTree[0] = 0;//初始化
    for (int i = 1; i < vexNum + 1; i++)vexs[i] = -1;//将所有的分量均置为-1
}
Graph::~Graph() {//释放空间
    delete[]vexs;
    delete[]arcs;
    delete[]minCSTree;
}
void Graph::Input_one(int i, int pos1, int pos2, int co) {//读入一个数据
    arcs[i].Input(pos1, pos2, co);
}
void Graph::Input_one_random(int num) {//随机输入一个数据
    int j, k,cost, n = 0;//j、k即顶点位置，cost表示权值为随机数
   srand((int)time(NULL));
    for (j = 1; j < num; j++) {
        for (k = j + 1; k <= num; k++) {
            n++;
            cost = 1 + rand() % 10;//随机输入一个权值
            arcs[n].Input(j, k, cost);//将数据读入到数组中

        }

    }
}
void Graph::Kruskal() {//Kruskal算法
    int arc = arcNum;//边的数量，从全部边开始
    int pathway = 1;//最小生成树数组元素的序号
    HeapInit();//堆初始化
    while (pathway <= vexNum - 1 && arc > 0) {
        HeapSort(arc);//堆排序
        if (Validate(arcs[arc])) {//如果新增加的边两顶点不在同一集合即不构成回路
            Merge_MFset(Find_MFset(arcs[arc].vex1), Find_MFset(arcs[arc].vex2));//将这两个顶点合并
            minCSTree[pathway] = arc;//将该边的序号添加到最小生成树数组中
            pathway++;
            minCSTree[0]++;//该空间存储最小生成树长度信息
        }
        arc--;//在剩下的边中找权值最小的边
    }
}
void Graph::OutFile(int n) {//生成文件
    int i;
    ofstream fout;//输出流
    fout.open("Results.txt");
    fout << "最小花费方案如下" << endl << "位置1    位置2    距离" << endl;
    for (i = 1; i < n; i++) {//将最小生成树的结果输出到文本文件
        fout << arcs[minCSTree[i]].vex1 << "       ";
        fout << arcs[minCSTree[i]].vex2 << "         ";
        fout << arcs[minCSTree[i]].cost << endl;
    }
    fout.close();//关闭文件
}
int CountLines() {
    ifstream ReadFile;//读取文件
    int n = 0;//记录行数
    char line[512];//足够大的空间
    ReadFile.open("Datas.txt", ios::in);//表示以只读方式读取文件
    if (ReadFile.fail())return 0;//文件打开失败
    else {
        while (!ReadFile.eof()) {
            ReadFile.getline(line, 512, '\n');//以换行符结束
            n++;
        }
        return n;
    }
}
void Graph::InFile(int i, int& pos1, int& pos2, int& cost) {
    int j;
    ifstream fin;//输入流
    fin.open("Datas.txt", ios::in);//文件中每行数据分别为两顶点位置和之间的权重
    for (j = 0; j < i; j++) {
        fin >> pos1 >> pos2 >> cost;
    }
    fin.close();//关闭文件
}
int Graph::RepetExam(int n, int pos1, int pos2) {//检验是否存在与之前输出数据重复
    int i;
    for (i = 1; i <= n; i++) {//逐个检查
        if ((arcs[i].vex1 == pos1 && arcs[i].vex2 == pos2) || (arcs[i].vex1 == pos2 && arcs[i].vex2 == pos1)) {
            return true;
        }
    }return false;
}
void point(int n, int& a, int& b) {//创造点的映射 有助于画图，相当于给定点的坐标
    switch (n) {
    case 1:a = 300; b = 100; break;
    case 2:a = 300; b = 50; break;
    case 3:a = 350; b = 100; break;
    case 4:a = 350; b = 150; break;
    case 5:a = 400; b = 50; break;
    case 6:a = 200; b = 71; break;
    case 7:a = 250; b = 66; break;
    case 8:a = 250; b = 166; break;
    case 9:a = 120; b = 80; break;
    default:break;
    }

}