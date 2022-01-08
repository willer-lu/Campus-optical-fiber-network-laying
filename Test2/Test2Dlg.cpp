#include <string>
#include <afx.h>
#include <iostream>
#include<afxtempl.h>
// Test2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Test2.h"
#include "Test2Dlg.h"
#include "afxdialogex.h"
#include "graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
// CTest2Dlg 对话框
CTest2Dlg::CTest2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CTest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, EDIT1);
	DDX_Control(pDX, IDC_EDIT2, EDIT2);
	DDX_Control(pDX, IDC_EDIT3, EDIT3);
	DDX_Control(pDX, IDC_EDIT4, EDIT4);
}
BEGIN_MESSAGE_MAP(CTest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FileIn, &CTest2Dlg::OnBnClickedButtonFilein)
	ON_BN_CLICKED(IDC_BUTTON_RandomIn, &CTest2Dlg::OnBnClickedButtonRandomin)
	ON_BN_CLICKED(IDC_BUTTON_TypeIn, &CTest2Dlg::OnBnClickedButtonTypein)
	ON_BN_CLICKED(IDC_BUTTON_ConfirmNum, &CTest2Dlg::OnBnClickedButtonConfirmnum)
	ON_BN_CLICKED(IDC_BUTTON_InPos, &CTest2Dlg::OnBnClickedButtonInpos)
	ON_BN_CLICKED(IDC_BUTTON_Calculate, &CTest2Dlg::OnBnClickedButtonCalculate)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CTest2Dlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_MemoryInFile, &CTest2Dlg::OnBnClickedButtonMemoryinfile)
	
END_MESSAGE_MAP()
// CTest2Dlg 消息处理程序
BOOL CTest2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CTest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTest2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CTest2Dlg::OnAbout() {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
//以上均为MFC自动生成的代码
Graph* g;//图类对象
int i = 0;//辅助变量
int num = 0;//图中的结点个数
void CTest2Dlg::OnBnClickedButtonFilein()//当点击文件输入按钮时
	{
		int a1, a2, b1, b2,n;
		GetDlgItem(IDC_BUTTON_Calculate)->EnableWindow(true); //GetDlgItem表示返回一个指向指定控件或子窗口的指针
		GetDlgItem(IDC_BUTTON_TypeIn)->EnableWindow(false);//EnableWindow表示允许/禁止指定的窗口或控件接受鼠标和键盘的输入
		GetDlgItem(IDC_BUTTON_RandomIn)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_FileIn)->EnableWindow(false);//将其他按钮设为可操作及不可操作
		n = CountLines();//计算文本文件中共有多少行记录（每行记录保存一对结点之间的信息）
		for (num = 0; num * (num - 1) / 2 != n && num < 30; num++);//计算对应多少个结点，num即结点个数
		g = new Graph(num, n);//创建一个图，n即为有多少条边
		for (i = 1; i <= n; i++) {//逐行读取文件的内容
			g->InFile(i, pos1, pos2, cost);
			g->Input_one(i, pos1, pos2, cost);
		}
			CString st = "", str = "", s;//str用来储存需要输出的位置信息，s储存图中顶点的序号，st辅助读取
			str.Format("文件读取了%d个位置,它们之间的距离信息如下: \r\n\r\n 位置1     位置2     距离\r\n\r\n", num);
			//Format表示通过格式操作使任意类型的数据转换成一个字符串
			int j;
			for (j = 1; j <= num * (num - 1) / 2; j++) {//循环终止条件即为所有边画出
				CClientDC dc(this);//MFC自带的绘图工具
				point(g->arcs[j].vex1, a1, b1);//对于已知的顶点找到对应的映射关系
				point(g->arcs[j].vex2, a2, b2);
				dc.MoveTo(a1, b1);//确定点的位置
				dc.LineTo(a2, b2);//绘制线段，从当前顶点到指定点
				s.Format("%d", g->arcs[j].vex1);
				dc.TextOut(a1, b1, s);//将顶点序号显示出来
				s.Format("%d", g->arcs[j].vex2);
				dc.TextOut(a2, b2, s);
				st.Format(" %d	 ", g->arcs[j].vex1);
				str += st;
				st.Format("%d	 ", g->arcs[j].vex2);
				str += st;
				st.Format("%d   \r\n", g->arcs[j].cost);
				str += st;
			}
			GetDlgItem(IDC_EDIT6)->SetWindowText(str);
		}
void CTest2Dlg::OnBnClickedButtonRandomin()//当点击随机输入按钮时
	{
		int a1, b1, a2, b2;
		srand((int)time(NULL));//随机输入函数
		num = 2 + (int)rand() % 8;//随即生成2~9个顶点 
		g = new Graph(num, num * (num - 1) / 2);//随机生成一个含num个位置的图，2<n<10
		g->Input_one_random(num);//随机输入一个数
		GetDlgItem(IDC_BUTTON_Calculate)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_RandomIn)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_TypeIn)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_FileIn)->EnableWindow(false);
		CString st = "", str = "", s;
		str.Format("随机生成了%d个位置,它们之间的距离信息如下: \r\n\r\n位置1    位置2    距离\r\n\r\n", num);
		int j;
		for (j = 1; j <= num * (num - 1) / 2; j++) {
			CClientDC dc(this);
			point(g->arcs[j].vex1, a1, b1);
			point(g->arcs[j].vex2, a2, b2);
			dc.MoveTo(a1, b1);
			dc.LineTo(a2, b2);
			s.Format("%d", g->arcs[j].vex1);
			dc.TextOut(a1, b1, s);
			dc.LineTo(a2, b2);
			s.Format("%d", g->arcs[j].vex2);
			dc.TextOut(a2, b2, s);
			st.Format(" %d	 ", g->arcs[j].vex1);
			str += st;
			st.Format("%d	 ", g->arcs[j].vex2);
			str += st;
			st.Format("%d    \r\n", g->arcs[j].cost);
			str += st;
		}
		GetDlgItem(IDC_EDIT6)->SetWindowText(str);
	}
void CTest2Dlg::OnBnClickedButtonTypein()//当点击人工输入时
	{
		UpdateData(true);//刷新数据
		GetDlgItem(IDC_BUTTON_ConfirmNum)->EnableWindow(true);
		GetDlgItem(IDC_EDIT1)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_FileIn)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_RandomIn)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_TypeIn)->EnableWindow(false);	
}
void CTest2Dlg::OnBnClickedButtonConfirmnum()//当点击确定按钮时
	{
		UpdateData(true);
		CString num1;
		GetDlgItemText(IDC_EDIT1, num1);//获取顶点个数文本框的内容
		n = atoi(num1);//将字符串转化为整型数据
		num = n;
		g = new Graph(num, num * (num - 1) / 2);
		if (num > 1 && num <= 9) {//支持输入2~9个顶点
			CString str = "您输入的信息如下: \r\n\r\n位置1    位置2    距离\r\n\r\n";
			GetDlgItem(IDC_EDIT6)->SetWindowText(str);
			GetDlgItem(IDC_BUTTON_InPos)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_ConfirmNum)->EnableWindow(false);
			GetDlgItem(IDC_EDIT2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT4)->EnableWindow(true);
		}
		
}
	void CTest2Dlg::OnBnClickedButtonInpos()//当点击记入按钮时
	{
		int a1, a2, b1, b2;
		CString s,num2,num3,num4;
		CClientDC dc(this);
		UpdateData(true);
		CString st = "", str = "";
		GetDlgItemText(IDC_EDIT2, num2);
		GetDlgItemText(IDC_EDIT3, num3);
		GetDlgItemText(IDC_EDIT4, num4);
		pos1= atoi(num2);
		pos2 = atoi(num3);
		cost = atoi(num4);//获取位置1 位置2 距离三个输入框的内容并转化为整型数据
		GetDlgItem(IDC_EDIT6)->GetWindowText(str);
		if ((i <= num * (num - 1) / 2) && (pos1 <= num && pos1 > 0) && (pos2 <= num && pos2 > 0) && (pos1 != pos2) && !(g->RepetExam(num, pos1, pos2)))
		{//分别判定输入个数、输入顶点序号是否在范围内、两顶点序号是否相同以及与之前输入的顶点是否重复
			++i;		 
			g->Input_one(i, pos1, pos2, cost);//逐个输入
			st.Format("  %d         ", pos1);
			str += st;
			st.Format("%d	", pos2);
			str += st;
			st.Format("%d		\r\n", cost);
			str += st;
			GetDlgItem(IDC_EDIT6)->SetWindowText(str);
			point(pos1, a1, b1);
			dc.MoveTo(a1, b1);
			s.Format("%d", pos1);
			dc.TextOut(a1, b1, s);
			point(pos2, a2, b2);
			dc.LineTo(a2, b2);
			s.Format("%d", pos2);
			dc.TextOut(a2, b2, s);
			s.Format("%d", cost);
			
		}
		else MessageBox("非法数据，请重新输入！");
		if (i == num * (num - 1) / 2) {//当输入完毕时即可计算
			GetDlgItem(IDC_BUTTON_Calculate)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_InPos)->EnableWindow(false);
		}
		SetDlgItemText(IDC_EDIT2, "");//把编辑栏变空
		SetDlgItemText(IDC_EDIT3, "");
		SetDlgItemText(IDC_EDIT4, "");
	}
	void CTest2Dlg::OnBnClickedButtonCalculate()//当点击计算最小消耗方案按钮时
	{
		int j;
		g->Kruskal();//利用克鲁斯卡尔算法计算得到最小生成树数组
		CString st = "", str = "最小花费方案如下: \r\n\r\n位置1     位置2		距离\r\n\r\n";
		for (j = 1; j <= num - 1; j++) {//num个顶点只需要num-1条路径
			int a1, b1, a2, b2, k;
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, RGB(255, 0, 0));//画笔的线型、颜色
			CPen* pOldPen = dc.SelectObject(&pen);//调用画笔工具
			k = g->minCSTree[j];//将最小生成树对应的边一一绘制及输出
			point(g->arcs[k].vex1, a1, b1);
			point(g->arcs[k].vex2, a2, b2);
			dc.MoveTo(a1, b1);
			dc.LineTo(a2, b2);
			dc.SelectObject(pOldPen);
			st.Format(" %d	", g->arcs[k].vex1);
			str += st;
			st.Format("%d		", g->arcs[k].vex2);
			str += st;
			st.Format("%d			\r\n", g->arcs[k].cost);
			str += st;
		}
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);
		GetDlgItem(IDC_BUTTON_Calculate)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_MemoryInFile)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_Clear)->EnableWindow(true);
		UpdateData(false);
	}
	void CTest2Dlg::OnBnClickedButtonClear()//当点击清空按钮时
	{
		SetDlgItemText(IDC_EDIT1, "O");
		SetDlgItemText(IDC_EDIT2, "O"); 
		SetDlgItemText(IDC_EDIT3, "O");
		SetDlgItemText(IDC_EDIT4, "O");
		SetDlgItemText(IDC_EDIT5, "");
		SetDlgItemText(IDC_EDIT6, "");
		SetDlgItemText(IDC_EDIT8, "");//把编辑栏变空
		GetDlgItem(IDC_BUTTON_RandomIn)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_TypeIn)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_FileIn)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_ConfirmNum)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_Calculate)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_InPos)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_MemoryInFile)->EnableWindow(false);
		GetDlgItem(IDC_EDIT1)->EnableWindow(false);
		GetDlgItem(IDC_EDIT2)->EnableWindow(false);
		GetDlgItem(IDC_EDIT3)->EnableWindow(false);
		GetDlgItem(IDC_EDIT4)->EnableWindow(false);
		i = 0;
		num = 0;//将所有按钮和全局变量初始化
	}
	void CTest2Dlg::OnBnClickedButtonMemoryinfile()//当点击生成文件按钮时
	{
		g->OutFile(num);//生成结果文件
		MessageBox("已成功生成txt文件!");
	}
	
	
