
// InventoryManager.h : main header file for the InventoryManager application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "Resources/resource.h"       // main symbols
#include "Application/ApplicationContext.h"

// CInventoryManagerApp:
// See InventoryManager.cpp for the implementation of this class
//

class CInventoryManagerApp : public CWinAppEx
{
public:
	CInventoryManagerApp();

	ApplicationContext& GetContext();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()

private:
	ApplicationContext m_context;

	void RunTest();
};

extern CInventoryManagerApp theApp;
