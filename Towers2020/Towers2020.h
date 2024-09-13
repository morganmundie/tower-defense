
// Towers2020.h : main header file for the Towers2020 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "Item.h"
#include "XmlNode.h"

/// CTowers2020App:
/// See Towers2020.cpp for the implementation of this class
class CTowers2020App : public CWinApp
{
public:
	CTowers2020App() noexcept;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = 0;
};

extern CTowers2020App theApp;
