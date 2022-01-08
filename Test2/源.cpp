#include "pch.h"
#include "graph.h"
#include<stdlib.h>
using namespace std;
void Arc::Input(int VEX1, int VEX2, int COST) {//���������Ĳ�����ֵ�����е���Ӧ����
    vex1 = VEX1;
    vex2 = VEX2;
    cost = COST;
}
void Arc::SwapArc(class Arc&arc) {//���������ߣ���Ӧ�������еĽ��������Ƹ��ƹ��캯��
    int tempArc,tempCost;//��������ʵ�ֽ���
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
int Graph::Find_MFset(int i) {//�������Ĳ��� ���ڵ�һ�β��ҵĶ��㷵������� ���򷵻ض�Ӧ����ͨ����
    int j,t=0;
    for (j = i; vexs[j] > 0; j = vexs[j]);
    return j;
}
int  Graph::Merge_MFset(int i, int j) {//�������ĺϲ� ����ͨ������С��Ϊ��׼
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
bool Graph::Validate(class Arc arc) {//���ߵ�����������ͬһ���Ϸ���false���򷵻�true
    if (Find_MFset(arc.vex1) == Find_MFset(arc.vex2))return false;
    return true;
}
void Graph::HeapAdjust(int s, int m) {//�ѵ���
    class Arc rc = arcs[s]; // �ݴ� R[s] 
    for (int j = s * 2; j <= m; j = j * 2) {//�ȽϽڵ�������������ӽڵ�ѡ��������С
        if (j<m && arcs[j].cost>arcs[j + 1].cost)j++;//����������֮����бȽϣ���j���عؼ��ֽ�Сλ��
        if (!(rc.cost > arcs[j].cost))break;//������������֮��ıȽϣ�<=˵���ҵ�rc�Ĳ���λ��
        arcs[s] = arcs[j];
        s = j;// �����¼���ƣ�����������µ���
    }
    arcs[s] = rc;// ������ǰ�ĶѶ���¼���뵽 s λ��
}
void Graph::HeapInit() {//�ѵĳ�ʼ����С���ѣ�
    for (int i = arcNum / 2; i > 0; i--)HeapAdjust(i, arcNum);
}
void Graph::HeapSort(int i) {//������
    arcs[1].SwapArc(arcs[i]);//����һ���ߺ͵�i���߽��н��������õ���С�ı�
    if (i != 1)HeapAdjust(1, i - 1);//������ɺ��ʣ�µĽ��жѵ���
}
Graph::Graph(int nVexNum, int nArcNum) {
    vexNum = nVexNum;//������Ŀ
    arcNum = nArcNum;//�ߵ���Ŀ
    vexs = new  int[vexNum + 1];
    arcs = new class Arc[arcNum + 1];//���ٵ�ַ�ռ�
    minCSTree = new int[vexNum];//�½���С����������
    minCSTree[0] = 0;//��ʼ��
    for (int i = 1; i < vexNum + 1; i++)vexs[i] = -1;//�����еķ�������Ϊ-1
}
Graph::~Graph() {//�ͷſռ�
    delete[]vexs;
    delete[]arcs;
    delete[]minCSTree;
}
void Graph::Input_one(int i, int pos1, int pos2, int co) {//����һ������
    arcs[i].Input(pos1, pos2, co);
}
void Graph::Input_one_random(int num) {//�������һ������
    int j, k,cost, n = 0;//j��k������λ�ã�cost��ʾȨֵΪ�����
   srand((int)time(NULL));
    for (j = 1; j < num; j++) {
        for (k = j + 1; k <= num; k++) {
            n++;
            cost = 1 + rand() % 10;//�������һ��Ȩֵ
            arcs[n].Input(j, k, cost);//�����ݶ��뵽������

        }

    }
}
void Graph::Kruskal() {//Kruskal�㷨
    int arc = arcNum;//�ߵ���������ȫ���߿�ʼ
    int pathway = 1;//��С����������Ԫ�ص����
    HeapInit();//�ѳ�ʼ��
    while (pathway <= vexNum - 1 && arc > 0) {
        HeapSort(arc);//������
        if (Validate(arcs[arc])) {//��������ӵı������㲻��ͬһ���ϼ������ɻ�·
            Merge_MFset(Find_MFset(arcs[arc].vex1), Find_MFset(arcs[arc].vex2));//������������ϲ�
            minCSTree[pathway] = arc;//���ñߵ������ӵ���С������������
            pathway++;
            minCSTree[0]++;//�ÿռ�洢��С������������Ϣ
        }
        arc--;//��ʣ�µı�����Ȩֵ��С�ı�
    }
}
void Graph::OutFile(int n) {//�����ļ�
    int i;
    ofstream fout;//�����
    fout.open("Results.txt");
    fout << "��С���ѷ�������" << endl << "λ��1    λ��2    ����" << endl;
    for (i = 1; i < n; i++) {//����С�������Ľ��������ı��ļ�
        fout << arcs[minCSTree[i]].vex1 << "       ";
        fout << arcs[minCSTree[i]].vex2 << "         ";
        fout << arcs[minCSTree[i]].cost << endl;
    }
    fout.close();//�ر��ļ�
}
int CountLines() {
    ifstream ReadFile;//��ȡ�ļ�
    int n = 0;//��¼����
    char line[512];//�㹻��Ŀռ�
    ReadFile.open("Datas.txt", ios::in);//��ʾ��ֻ����ʽ��ȡ�ļ�
    if (ReadFile.fail())return 0;//�ļ���ʧ��
    else {
        while (!ReadFile.eof()) {
            ReadFile.getline(line, 512, '\n');//�Ի��з�����
            n++;
        }
        return n;
    }
}
void Graph::InFile(int i, int& pos1, int& pos2, int& cost) {
    int j;
    ifstream fin;//������
    fin.open("Datas.txt", ios::in);//�ļ���ÿ�����ݷֱ�Ϊ������λ�ú�֮���Ȩ��
    for (j = 0; j < i; j++) {
        fin >> pos1 >> pos2 >> cost;
    }
    fin.close();//�ر��ļ�
}
int Graph::RepetExam(int n, int pos1, int pos2) {//�����Ƿ������֮ǰ��������ظ�
    int i;
    for (i = 1; i <= n; i++) {//������
        if ((arcs[i].vex1 == pos1 && arcs[i].vex2 == pos2) || (arcs[i].vex1 == pos2 && arcs[i].vex2 == pos1)) {
            return true;
        }
    }return false;
}
void point(int n, int& a, int& b) {//������ӳ�� �����ڻ�ͼ���൱�ڸ����������
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