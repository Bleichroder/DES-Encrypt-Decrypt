
// DESDecrypt.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDESDecryptApp: 
// �йش����ʵ�֣������ DESDecrypt.cpp
//

class CDESDecryptApp : public CWinApp
{
public:
	CDESDecryptApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDESDecryptApp theApp;