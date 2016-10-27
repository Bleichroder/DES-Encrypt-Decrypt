
// DESDecryptDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DESDecrypt.h"
#include "DESDecryptDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDESDecryptDlg �Ի���



CDESDecryptDlg::CDESDecryptDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DESDECRYPT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESDecryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDESDecryptDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDESDecryptDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDESDecryptDlg ��Ϣ�������

BOOL CDESDecryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(_T("ʱ����ȨDemo"));
	key = _T("maxwall");
	CRegKey cKey;
	if (cKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\DESEncrypt\\EncryptedCode")) == ERROR_SUCCESS)		//�ж�ע�������û�м���������������бȶ�
	{
		TCHAR TMP[1024];
		DWORD dwcount = 1024;
		cKey.QueryStringValue(_T("EnCd"), TMP, &dwcount);
		int Pos, nPos;
		code = TMP;
		code = des.DESw(code, key);
		Pos = code.Find(_T("-"));
		int lastY = _ttoi(code.Left(Pos));
		nPos = code.Find(_T('-'), Pos + 1);
		int lastM = _ttoi(code.Mid(Pos + 1, nPos - 1));
		Pos = code.Find(_T("-"), nPos + 1);
		int lastD = _ttoi(code.Mid(nPos + 1, Pos - 1));
		nPos = code.ReverseFind(_T('-'));

		SYSTEMTIME st;
		GetLocalTime(&st);
		if (lastY < st.wYear)							//��ǰ���ںͽ�ֹ���ڱȶ�
			MessageBox(_T("���������"), _T("ע��"));
		else if (lastY > st.wYear)
		{
			//MessageBox(_T("��½�ɹ�"), _T("��ʾ"));
		}
		else if (lastY == st.wYear)
		{
			if (lastM < st.wMonth)
				MessageBox(_T("���������"), _T("ע��"));
			else if (lastM > st.wMonth)
			{
				//MessageBox(_T("��½�ɹ�"), _T("��ʾ"));
			}
			else if (lastM == st.wMonth)
			{
				if (lastD < st.wDay)
					MessageBox(_T("���������"), _T("ע��"));
				else if (lastD >= st.wDay + 5)
				{
					//MessageBox(_T("��½�ɹ�"), _T("��ʾ"));
				}
				else
				{
					CString a;
					int b = lastD - st.wDay;
					a.Format(_T("%d"), b);
					MessageBox(a + _T("��ʣ��"), _T("ע��"));
				}
			}
		}

		CString lastuser = code.Right(code.GetLength() - nPos - 1);
		SetDlgItemText(IDC_STATIC_user, _T("��Ȩ��") + lastuser);
		SetDlgItemText(IDC_STATIC_time, code.Left(nPos));
	}
	else
	{
		SetDlgItemText(IDC_STATIC_user, _T("δ��Ȩ"));
		SetDlgItemText(IDC_STATIC_time, _T(""));
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDESDecryptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDESDecryptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDESDecryptDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString nowcode;
	DWORD dwcount = 1024;
	GetDlgItemText(IDC_EDIT1, nowcode);
	if (nowcode == _T(""))
	{
		MessageBox(_T("���벻��Ϊ��"), _T("ע��"));
		return;
	}
	CRegKey cKey;
	if (cKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\DESEncrypt\\EncryptedCode")) == ERROR_SUCCESS)		//�ж�ע�������û�м���������������бȶ�
	{
		int nPos;
		TCHAR TMP[1024];
		cKey.QueryStringValue( _T("EnCd"), TMP, &dwcount);
		//int b = GetLastError();
		code = TMP;
		CString regcode = des.DESw(code, key);
		CString regnowcode = des.DESw(nowcode, key);

		int rPos = regnowcode.Find(_T("-"));
		if (rPos == -1)
		{
			MessageBox(_T("���������"), _T("����"));
			cKey.Close();
			return;
		}
		/*int nowres = _ttoi(regnowcode.Left(rPos));
		rPos = regcode.Find(_T("-"));
		int orires = _ttoi(regcode.Left(rPos));*/

		//if (nowres == orires)								//������
		//{
		/*Pos = regcode.Find(_T("-"));			//����Դ�������е�ʱ����û�
		if (Pos == -1)
		{
			MessageBox(_T("���������"), _T("����"));
			cKey.Close();
			return;
		}*/

		nPos = regcode.ReverseFind(_T('-'));
		CString lastuser = regcode.Right(regcode.GetLength() - nPos - 1);

		nPos = regnowcode.ReverseFind(_T('-'));
		CString curruser = regnowcode.Right(regnowcode.GetLength() - nPos - 1);

		if (lastuser != curruser)						//�û�������ȷ
		{
			MessageBox(_T("�û������󣬸���ʧ��"), _T("����"));
		}
		else
		{
			cKey.SetStringValue(_T("EnCd"), nowcode);
			MessageBox(_T("���¼�����ɹ�"), _T("��ʾ"));
			SetDlgItemText(IDC_STATIC_time, regnowcode.Left(nPos));
		}
		//}
		//else if (nowres == orires + 8)						//���ü�����
		//{
		//}
	}
	else
	{																								//ע�����û�м�������½�����漤����
		cKey.Create(HKEY_CURRENT_USER, _T("Software\\DESEncrypt\\EncryptedCode"));
		if (cKey.Open(HKEY_CURRENT_USER, _T("Software\\DESEncrypt\\EncryptedCode")) == ERROR_SUCCESS)
		{
			cKey.SetStringValue(_T("EnCd"), nowcode);
			MessageBox(_T("��ʼ��������ɹ�"), _T("��ʾ"));
		}
		
		int Pos, nPos;
		nowcode = des.DESw(nowcode, key);
		Pos = nowcode.Find(_T("-"));
		int lastY = _ttoi(nowcode.Left(Pos));
		nPos = nowcode.Find(_T('-'), Pos + 1);
		int lastM = _ttoi(nowcode.Mid(Pos + 1, nPos - 1));
		Pos = nowcode.Find(_T("-"), nPos + 1);
		int lastD = _ttoi(nowcode.Mid(nPos + 1, Pos - 1));
		nPos = nowcode.ReverseFind(_T('-'));

		SYSTEMTIME st;
		GetLocalTime(&st);
		if (lastY < st.wYear)							//��ǰ���ںͽ�ֹ���ڱȶ�
			MessageBox(_T("���������"), _T("ע��"));
		else if (lastY > st.wYear)
		{
			if (lastY == st.wYear + 1 && lastM == 1 && st.wMonth == 12)
			{
				if (lastD + 31 - st.wDay < 5)
				{
					CString a;
					int b = lastD + 31 - st.wDay;
					a.Format(_T("%d"), b);
					MessageBox(a + _T("��ʣ��"), _T("ע��"));
				}
			}
			//MessageBox(_T("��½�ɹ�"), _T("��ʾ"));
		}
		else if (lastY == st.wYear)
		{
			if (lastM < st.wMonth)
				MessageBox(_T("���������"), _T("ע��"));
			else if (lastM > st.wMonth)
			{
				if (lastM == st.wMonth + 1 && lastD + 30 - st.wDay < 5)
				{
					MessageBox(_T("��������"), _T("ע��"));
				}
				//MessageBox(_T("��½�ɹ�"), _T("��ʾ"));
			}
			else if (lastM == st.wMonth)
			{
				if (lastD < st.wDay)
					MessageBox(_T("���������"), _T("ע��"));
				else if (lastD >= st.wDay + 5)
				{
					//MessageBox(_T("��½�ɹ�"), _T("��ʾ"));
				}
				else
				{
					CString a;
					int b = lastD - st.wDay;
					a.Format(_T("%d"), b);
					MessageBox(a + _T("��ʣ��"), _T("ע��"));
				}
			}
		}

		CString lastuser = nowcode.Right(nowcode.GetLength() - nPos - 1);
		SetDlgItemText(IDC_STATIC_user, _T("��Ȩ��") + lastuser);
		SetDlgItemText(IDC_STATIC_time, nowcode.Left(nPos));
	}
	cKey.Close();
}
