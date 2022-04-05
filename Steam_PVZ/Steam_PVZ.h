// Steam_PVZ.h: Steam_PVZ DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号

#define GAMENAME TEXT("Plants vs. Zombies")

// CSteamPVZApp
// 有关此类实现的信息，请参阅 Steam_PVZ.cpp
//

class CSteamPVZApp : public CWinApp
{
public:
	CSteamPVZApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

void __stdcall SetHook();
LRESULT WINAPI KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
static bool IsFullScreenWindow(HWND hWnd);