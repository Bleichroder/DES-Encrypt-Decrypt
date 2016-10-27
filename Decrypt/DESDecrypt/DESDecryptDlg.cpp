
// DESDecryptDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DESDecrypt.h"
#include "DESDecryptDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDESDecryptDlg 对话框



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


// CDESDecryptDlg 消息处理程序

BOOL CDESDecryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowText(_T("时间授权Demo"));
	key = _T("maxwall");
	CRegKey cKey;
	if (cKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\DESEncrypt\\EncryptedCode")) == ERROR_SUCCESS)		//判断注册表中有没有激活码项，如果有则进行比对
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
		if (lastY < st.wYear)							//当前日期和截止日期比对
			MessageBox(_T("激活码过期"), _T("注意"));
		else if (lastY > st.wYear)
		{
			//MessageBox(_T("登陆成功"), _T("提示"));
		}
		else if (lastY == st.wYear)
		{
			if (lastM < st.wMonth)
				MessageBox(_T("激活码过期"), _T("注意"));
			else if (lastM > st.wMonth)
			{
				//MessageBox(_T("登陆成功"), _T("提示"));
			}
			else if (lastM == st.wMonth)
			{
				if (lastD < st.wDay)
					MessageBox(_T("激活码过期"), _T("注意"));
				else if (lastD >= st.wDay + 5)
				{
					//MessageBox(_T("登陆成功"), _T("提示"));
				}
				else
				{
					CString a;
					int b = lastD - st.wDay;
					a.Format(_T("%d"), b);
					MessageBox(a + _T("天剩余"), _T("注意"));
				}
			}
		}

		CString lastuser = code.Right(code.GetLength() - nPos - 1);
		SetDlgItemText(IDC_STATIC_user, _T("授权给") + lastuser);
		SetDlgItemText(IDC_STATIC_time, code.Left(nPos));
	}
	else
	{
		SetDlgItemText(IDC_STATIC_user, _T("未授权"));
		SetDlgItemText(IDC_STATIC_time, _T(""));
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDESDecryptDlg::OnPaint()
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
HCURSOR CDESDecryptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDESDecryptDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	// TODO: 在此添加控件通知处理程序代码
	CString nowcode;
	DWORD dwcount = 1024;
	GetDlgItemText(IDC_EDIT1, nowcode);
	if (nowcode == _T(""))
	{
		MessageBox(_T("输入不得为空"), _T("注意"));
		return;
	}
	CRegKey cKey;
	if (cKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\DESEncrypt\\EncryptedCode")) == ERROR_SUCCESS)		//判断注册表中有没有激活码项，如果有则进行比对
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
			MessageBox(_T("激活码错误"), _T("错误"));
			cKey.Close();
			return;
		}
		/*int nowres = _ttoi(regnowcode.Left(rPos));
		rPos = regcode.Find(_T("-"));
		int orires = _ttoi(regcode.Left(rPos));*/

		//if (nowres == orires)								//不重置
		//{
		/*Pos = regcode.Find(_T("-"));			//解析源激活码中的时间和用户
		if (Pos == -1)
		{
			MessageBox(_T("激活码错误"), _T("错误"));
			cKey.Close();
			return;
		}*/

		nPos = regcode.ReverseFind(_T('-'));
		CString lastuser = regcode.Right(regcode.GetLength() - nPos - 1);

		nPos = regnowcode.ReverseFind(_T('-'));
		CString curruser = regnowcode.Right(regnowcode.GetLength() - nPos - 1);

		if (lastuser != curruser)						//用户名不正确
		{
			MessageBox(_T("用户名错误，更新失败"), _T("错误"));
		}
		else
		{
			cKey.SetStringValue(_T("EnCd"), nowcode);
			MessageBox(_T("更新激活码成功"), _T("提示"));
			SetDlgItemText(IDC_STATIC_time, regnowcode.Left(nPos));
		}
		//}
		//else if (nowres == orires + 8)						//重置激活码
		//{
		//}
	}
	else
	{																								//注册表中没有激活码项，新建项并保存激活码
		cKey.Create(HKEY_CURRENT_USER, _T("Software\\DESEncrypt\\EncryptedCode"));
		if (cKey.Open(HKEY_CURRENT_USER, _T("Software\\DESEncrypt\\EncryptedCode")) == ERROR_SUCCESS)
		{
			cKey.SetStringValue(_T("EnCd"), nowcode);
			MessageBox(_T("初始化激活码成功"), _T("提示"));
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
		if (lastY < st.wYear)							//当前日期和截止日期比对
			MessageBox(_T("激活码过期"), _T("注意"));
		else if (lastY > st.wYear)
		{
			if (lastY == st.wYear + 1 && lastM == 1 && st.wMonth == 12)
			{
				if (lastD + 31 - st.wDay < 5)
				{
					CString a;
					int b = lastD + 31 - st.wDay;
					a.Format(_T("%d"), b);
					MessageBox(a + _T("天剩余"), _T("注意"));
				}
			}
			//MessageBox(_T("登陆成功"), _T("提示"));
		}
		else if (lastY == st.wYear)
		{
			if (lastM < st.wMonth)
				MessageBox(_T("激活码过期"), _T("注意"));
			else if (lastM > st.wMonth)
			{
				if (lastM == st.wMonth + 1 && lastD + 30 - st.wDay < 5)
				{
					MessageBox(_T("即将到期"), _T("注意"));
				}
				//MessageBox(_T("登陆成功"), _T("提示"));
			}
			else if (lastM == st.wMonth)
			{
				if (lastD < st.wDay)
					MessageBox(_T("激活码过期"), _T("注意"));
				else if (lastD >= st.wDay + 5)
				{
					//MessageBox(_T("登陆成功"), _T("提示"));
				}
				else
				{
					CString a;
					int b = lastD - st.wDay;
					a.Format(_T("%d"), b);
					MessageBox(a + _T("天剩余"), _T("注意"));
				}
			}
		}

		CString lastuser = nowcode.Right(nowcode.GetLength() - nPos - 1);
		SetDlgItemText(IDC_STATIC_user, _T("授权给") + lastuser);
		SetDlgItemText(IDC_STATIC_time, nowcode.Left(nPos));
	}
	cKey.Close();
}
