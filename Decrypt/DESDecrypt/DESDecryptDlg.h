
// DESDecryptDlg.h : ͷ�ļ�
//
#include "yxyDES2.h"
#pragma once


// CDESDecryptDlg �Ի���
class CDESDecryptDlg : public CDialogEx
{
// ����
public:
	CDESDecryptDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DESDECRYPT_DIALOG };
#endif

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
	CString code, key;
	afx_msg void OnBnClickedOk();
};
