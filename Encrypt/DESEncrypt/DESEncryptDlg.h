
// DESEncryptDlg.h : ͷ�ļ�
//
#include "yxyDES2.h"
#pragma once


// CDESEncryptDlg �Ի���
class CDESEncryptDlg : public CDialogEx
{
// ����
public:
	CDESEncryptDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DESENCRYPT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
