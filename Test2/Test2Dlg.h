#include <string>
#include <afx.h>
#include <iostream>
#include<afxtempl.h>
using namespace std;
// Test2Dlg.h: 头文件
//

#pragma once


// CTest2Dlg 对话框
class CTest2Dlg : public CDialogEx
{
// 构造
public:
	CTest2Dlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST2_DIALOG };
#endif
	int pos1=1, pos2=2,n=0; //顶点的位置及个数
	int cost=0;//权值
	CString str;//字符串变量
	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	
	afx_msg void OnAbout();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFilein();//当点击文件输入时
	afx_msg void OnBnClickedButtonRandomin();//当点击随机输入时
	afx_msg void OnBnClickedButtonTypein();//当点击人工输入时
	afx_msg void OnBnClickedButtonConfirmnum();//当点击确定时
	afx_msg void OnBnClickedButtonInpos();//当点击记入时
	afx_msg void OnBnClickedButtonCalculate();//当点击计算最小消耗方案时
	afx_msg void OnBnClickedButtonClear();//当点击清空时
	afx_msg void OnBnClickedButtonMemoryinfile();//当点击生成文件时
	CEdit EDIT1;//文本编辑框的变量 用于读取数据时使用
	CEdit EDIT2;
	CEdit EDIT3;
	CEdit EDIT4;
};
