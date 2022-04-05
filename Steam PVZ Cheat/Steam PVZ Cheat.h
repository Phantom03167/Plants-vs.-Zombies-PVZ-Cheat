// Steam PVZ Cheat.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号

#define GAMENAME TEXT("Plants vs. Zombies")
//#define GAMENAME TEXT("植物大战僵尸中文版")

// CSteamPVZCheatApp:
// 有关此类的实现，请参阅 Steam PVZ Cheat.cpp
//

class CSteamPVZCheatApp : public CWinApp
{
public:
	CSteamPVZCheatApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CSteamPVZCheatApp theApp;

static bool EnableDebugPrivilege();
HANDLE GetProcessHandleByTittle(CString str);
HANDLE InjectDll(CString wndname);
static bool IsFullScreenWindow(HWND hWnd);
void __stdcall setSteam_PVZHook();