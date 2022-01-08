#pragma once
#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;
class Arc{
public:
    int vex1=0, vex2=0,cost=0;//����ͷ�Ľڵ㼰�ߵ�Ȩ��ֵ������������Ҫ�ķ���
    Arc() {};//���캯��
    ~Arc() {};//��������
    void Input(int, int, int);//�������ز����ĺ���
    void SwapArc(Arc&);//���������ߣ���������ʹ��
};
class Graph {
public:
    int vexNum, arcNum;//������������ߵ�����
    int* vexs;//��ͨ����
    class Arc* arcs;//����
    int* minCSTree;//��С���������飬�����鱣����С·���ıߵ����
    Graph(int m = 0, int n = 0);//���캯��
    ~Graph();//��������
    void Input_one(int, int, int, int);//�������
    void Input_one_random(int);//�������һ��
    void InFile(int, int&, int&, int&);//��ȡ�ļ�
    void OutFile(int);//����ļ�
    void Kruskal();//��С�������㷨
    int RepetExam(int, int, int);//����˹�����ʱ�Ƿ����ظ�����
    int Find_MFset(int);//�������Ĳ���
    int Merge_MFset(int, int);//�������ĺϲ�
    bool Validate(class Arc);//�жϱ��Ƿ���ͬһ����
    void HeapAdjust(int, int);//�ѵ���
    void HeapInit();//�ѳ�ʼ��
    void HeapSort(int);//������
};
int CountLines();//�����ı�������
void point(int n, int& a, int& b);//���ӳ��
