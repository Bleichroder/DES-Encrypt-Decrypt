
// DESEncryptDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DESEncrypt.h"
#include "DESEncryptDlg.h"
#include "afxdialogex.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDESEncryptDlg 对话框




CDESEncryptDlg::CDESEncryptDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDESEncryptDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESEncryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDESEncryptDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDESEncryptDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDESEncryptDlg::OnBnClickedCancel)
//	ON_BN_CLICKED(IDC_CHECKRESET, &CDESEncryptDlg::OnBnClickedCheckreset)
//ON_EN_CHANGE(IDC_EDIT3, &CDESEncryptDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CDESEncryptDlg 消息处理程序

BOOL CDESEncryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	SetWindowText(_T("授权总管"));
/*	if (IsDlgButtonChecked(IDC_CHECKRESET))
	{
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	}*/
	key = _T("maxwall");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDESEncryptDlg::OnPaint()
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
HCURSOR CDESEncryptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDESEncryptDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString user;
	CString year,month,day;
	CString sourcecode;
	GetDlgItemText(IDC_EDIT1,user);
	GetDlgItemText(IDC_EDITY,year);
	GetDlgItemText(IDC_EDITM,month);
	GetDlgItemText(IDC_EDITD,day);
	int y = _ttoi(year);
	int m = _ttoi(month);
	int d = _ttoi(day);
	if (user == _T(""))									//输入不可以为空
	{
		MessageBox(_T("用户名不得为空"), _T("注意"));
		return;
	}
	if(year==_T("")||month==_T("")||day==_T("")||y>2050||y<2010||m<1||m>12)			//判断日期的格式
	{
		if (y % 4 == 0)
		{
			switch (m)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (d < 1 || d > 31)
				{
					MessageBox(_T("时间格式不正确"), _T("注意"));
					return;
				}
			case 4:
			case 6:
			case 9:
			case 11:
				if (d < 1 || d > 30)
				{
					MessageBox(_T("时间格式不正确"), _T("注意"));
					return;
				}
			case 2:
				if (d < 1 || d > 29)
				{
					MessageBox(_T("时间格式不正确"), _T("注意"));
					return;
				}
			default:
				break;
			}
		}
		else
		{
			switch (m)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (d < 1 || d > 31)
				{
					MessageBox(_T("时间格式不正确"), _T("注意"));
					return;
				}
			case 4:
			case 6:
			case 9:
			case 11:
				if (d < 1 || d > 30)
				{
					MessageBox(_T("时间格式不正确"), _T("注意"));
					return;
				}
			case 2:
				if (d < 1 || d > 28)
				{
					MessageBox(_T("时间格式不正确"), _T("注意"));
					return;
				}
			default:
				break;
			}
		}
	}
	CString time = year+_T("-")+month+_T("-")+day;
	code = des.DESr(time+_T("-")+user,key);
	SetDlgItemText(IDC_EDIT3,code);

	//生成Excel
	CString sExcelFile, sPath;
	//获取主程序所在路径,存在sPath中
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\'); //从后往前查找字符\\，范返回位置
	sPath = sPath.Left(nPos);
	sExcelFile = sPath + _T("\\激活码统计");
	
	CFileFind fileFind;
	if (!(fileFind.FindFile(sExcelFile + _T(".xls")) || fileFind.FindFile(sExcelFile + _T(".xlsx"))))		//excel不存在
	{
		//初始化COM库
		if (CoInitialize(NULL) != 0)
		{
			AfxMessageBox(_T("初始化COM支持库失败！"));
			return;
		}

		//定义Excel六层对象
		CApplication app;
		CWorkbooks books;
		CWorkbook book;
		CWorksheets sheets;
		CWorksheet sheet;
		CRange range;

		//创建Excel 2000服务器(启动Excel) 
		if (!app.CreateDispatch(_T("Excel.Application"), NULL))
		{
			AfxMessageBox(_T("创建Excel服务失败!"));
			return;
		}

		COleVariant
			covTrue((short)TRUE),
			covFalse((short)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		//得到WorkBooks
		books = app.get_Workbooks();
		book = books.Add(covOptional);
		//book = books.Open(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//得到WorkSheets
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));

		//当为保存数据时，定义为
		VARIANT start;
		start.vt = VT_BSTR;
		start.bstrVal = ::SysAllocString(L"A1");
		VARIANT stop;
		stop.vt = VT_BSTR;
		stop.bstrVal = ::SysAllocString(L"D2");
		range = sheet.get_Range(start, stop);

		range.put_Item((_variant_t)1, (_variant_t)1, (_variant_t)_T("编号"));
		range.put_Item((_variant_t)1, (_variant_t)2, (_variant_t)_T("厂家"));
		range.put_Item((_variant_t)1, (_variant_t)3, (_variant_t)_T("到期时间"));
		range.put_Item((_variant_t)1, (_variant_t)4, (_variant_t)_T("激活码"));
		range.put_Item((_variant_t)2, (_variant_t)1, (_variant_t)_T("no.1"));
		range.put_Item((_variant_t)2, (_variant_t)2, (_variant_t)user);
		range.put_Item((_variant_t)2, (_variant_t)3, (_variant_t)time);
		range.put_Item((_variant_t)2, (_variant_t)4, (_variant_t)code);

		//book.Save();
		sheet.SaveAs(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//退出
		app.Quit();

		//释放对象
		range.ReleaseDispatch();
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		app.ReleaseDispatch();

		CoUninitialize();
	}
	else
	{
		//初始化COM库
		if (CoInitialize(NULL) != 0)
		{
			AfxMessageBox(_T("初始化COM支持库失败！"));
			return;
		}

		//定义Excel六层对象
		CApplication app;
		CWorkbooks books;
		CWorkbook book;
		CWorksheets sheets;
		CWorksheet sheet;
		CRange range;

		//创建Excel 2000服务器(启动Excel) 
		if (!app.CreateDispatch(_T("Excel.Application"), NULL))
		{
			AfxMessageBox(_T("创建Excel服务失败!"));
			return;
		}

		COleVariant
			covTrue((short)TRUE),
			covFalse((short)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		//得到WorkBooks
		books = app.get_Workbooks();
		//book = books.Add(covOptional);
		book = books.Open(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//得到WorkSheets
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));

		range = sheet.get_UsedRange();
		range = range.get_Rows();
		long m_iRowNum = range.get_Count();//获取已使用的行数
		CString id;
		id.Format(_T("%d"), m_iRowNum+1);

		//当为保存数据时，定义为
		VARIANT start;
		start.vt = VT_BSTR;
		CString a = _T("A") + id;
		start.bstrVal = ::SysAllocString(a.AllocSysString());
		VARIANT stop;
		stop.vt = VT_BSTR;
		a = _T("D") + id;
		stop.bstrVal = ::SysAllocString(a.AllocSysString());
		range = sheet.get_Range(start, stop);

		CString b;
		b.Format(_T("%d"), m_iRowNum );
		range.put_Item((_variant_t)1, (_variant_t)1, (_variant_t)(_T("no.")+b));
		range.put_Item((_variant_t)1, (_variant_t)2, (_variant_t)user);
		range.put_Item((_variant_t)1, (_variant_t)3, (_variant_t)time);
		range.put_Item((_variant_t)1, (_variant_t)4, (_variant_t)code);

		book.Save();
		//sheet.SaveAs(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//退出
		app.Quit();

		//释放对象
		range.ReleaseDispatch();
		sheet.ReleaseDispatch();
		sheets.ReleaseDispatch();
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		app.ReleaseDispatch();

		CoUninitialize();
	}
}


void CDESEncryptDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


//void CDESEncryptDlg::OnBnClickedCheckreset()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if (IsDlgButtonChecked(IDC_CHECKRESET))
//	{
//		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
//	}
//	else
//	{
//		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
//	}
//}



//void CDESEncryptDlg::OnEnChangeEdit3()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
