
// DESEncrypt.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDESEncryptApp:
// �йش����ʵ�֣������ DESEncrypt.cpp
//

class CDESEncryptApp : public CWinApp
{
public:
	CDESEncryptApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDESEncryptApp theApp;