
// DESEncryptDlg.cpp : ʵ���ļ�
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


// CDESEncryptDlg �Ի���




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


// CDESEncryptDlg ��Ϣ�������

BOOL CDESEncryptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	SetWindowText(_T("��Ȩ�ܹ�"));
/*	if (IsDlgButtonChecked(IDC_CHECKRESET))
	{
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	}*/
	key = _T("maxwall");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDESEncryptDlg::OnPaint()
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
HCURSOR CDESEncryptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDESEncryptDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if (user == _T(""))									//���벻����Ϊ��
	{
		MessageBox(_T("�û�������Ϊ��"), _T("ע��"));
		return;
	}
	if(year==_T("")||month==_T("")||day==_T("")||y>2050||y<2010||m<1||m>12)			//�ж����ڵĸ�ʽ
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
					MessageBox(_T("ʱ���ʽ����ȷ"), _T("ע��"));
					return;
				}
			case 4:
			case 6:
			case 9:
			case 11:
				if (d < 1 || d > 30)
				{
					MessageBox(_T("ʱ���ʽ����ȷ"), _T("ע��"));
					return;
				}
			case 2:
				if (d < 1 || d > 29)
				{
					MessageBox(_T("ʱ���ʽ����ȷ"), _T("ע��"));
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
					MessageBox(_T("ʱ���ʽ����ȷ"), _T("ע��"));
					return;
				}
			case 4:
			case 6:
			case 9:
			case 11:
				if (d < 1 || d > 30)
				{
					MessageBox(_T("ʱ���ʽ����ȷ"), _T("ע��"));
					return;
				}
			case 2:
				if (d < 1 || d > 28)
				{
					MessageBox(_T("ʱ���ʽ����ȷ"), _T("ע��"));
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

	//����Excel
	CString sExcelFile, sPath;
	//��ȡ����������·��,����sPath��
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\'); //�Ӻ���ǰ�����ַ�\\��������λ��
	sPath = sPath.Left(nPos);
	sExcelFile = sPath + _T("\\������ͳ��");
	
	CFileFind fileFind;
	if (!(fileFind.FindFile(sExcelFile + _T(".xls")) || fileFind.FindFile(sExcelFile + _T(".xlsx"))))		//excel������
	{
		//��ʼ��COM��
		if (CoInitialize(NULL) != 0)
		{
			AfxMessageBox(_T("��ʼ��COM֧�ֿ�ʧ�ܣ�"));
			return;
		}

		//����Excel�������
		CApplication app;
		CWorkbooks books;
		CWorkbook book;
		CWorksheets sheets;
		CWorksheet sheet;
		CRange range;

		//����Excel 2000������(����Excel) 
		if (!app.CreateDispatch(_T("Excel.Application"), NULL))
		{
			AfxMessageBox(_T("����Excel����ʧ��!"));
			return;
		}

		COleVariant
			covTrue((short)TRUE),
			covFalse((short)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		//�õ�WorkBooks
		books = app.get_Workbooks();
		book = books.Add(covOptional);
		//book = books.Open(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//�õ�WorkSheets
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));

		//��Ϊ��������ʱ������Ϊ
		VARIANT start;
		start.vt = VT_BSTR;
		start.bstrVal = ::SysAllocString(L"A1");
		VARIANT stop;
		stop.vt = VT_BSTR;
		stop.bstrVal = ::SysAllocString(L"D2");
		range = sheet.get_Range(start, stop);

		range.put_Item((_variant_t)1, (_variant_t)1, (_variant_t)_T("���"));
		range.put_Item((_variant_t)1, (_variant_t)2, (_variant_t)_T("����"));
		range.put_Item((_variant_t)1, (_variant_t)3, (_variant_t)_T("����ʱ��"));
		range.put_Item((_variant_t)1, (_variant_t)4, (_variant_t)_T("������"));
		range.put_Item((_variant_t)2, (_variant_t)1, (_variant_t)_T("no.1"));
		range.put_Item((_variant_t)2, (_variant_t)2, (_variant_t)user);
		range.put_Item((_variant_t)2, (_variant_t)3, (_variant_t)time);
		range.put_Item((_variant_t)2, (_variant_t)4, (_variant_t)code);

		//book.Save();
		sheet.SaveAs(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//�˳�
		app.Quit();

		//�ͷŶ���
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
		//��ʼ��COM��
		if (CoInitialize(NULL) != 0)
		{
			AfxMessageBox(_T("��ʼ��COM֧�ֿ�ʧ�ܣ�"));
			return;
		}

		//����Excel�������
		CApplication app;
		CWorkbooks books;
		CWorkbook book;
		CWorksheets sheets;
		CWorksheet sheet;
		CRange range;

		//����Excel 2000������(����Excel) 
		if (!app.CreateDispatch(_T("Excel.Application"), NULL))
		{
			AfxMessageBox(_T("����Excel����ʧ��!"));
			return;
		}

		COleVariant
			covTrue((short)TRUE),
			covFalse((short)FALSE),
			covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		//�õ�WorkBooks
		books = app.get_Workbooks();
		//book = books.Add(covOptional);
		book = books.Open(sExcelFile, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing);

		//�õ�WorkSheets
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));

		range = sheet.get_UsedRange();
		range = range.get_Rows();
		long m_iRowNum = range.get_Count();//��ȡ��ʹ�õ�����
		CString id;
		id.Format(_T("%d"), m_iRowNum+1);

		//��Ϊ��������ʱ������Ϊ
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

		//�˳�
		app.Quit();

		//�ͷŶ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


//void CDESEncryptDlg::OnBnClickedCheckreset()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}
