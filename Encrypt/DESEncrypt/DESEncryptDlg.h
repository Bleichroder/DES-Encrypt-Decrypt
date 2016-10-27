
// DESEncryptDlg.h : 头文件
//
#include "yxyDES2.h"
#pragma once


// CDESEncryptDlg 对话框
class CDESEncryptDlg : public CDialogEx
{
// 构造
public:
	CDESEncryptDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DESENCRYPT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	yxyDES2 des;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString key;
	CString nowcode;
	CString code;
//	CString res;
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnBnClickedCheckreset();
//	afx_msg void OnEnChangeEdit3();
};
