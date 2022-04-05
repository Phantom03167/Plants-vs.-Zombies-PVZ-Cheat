// Steam PVZ.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "Steam_PVZ.h"
#include "CDialogMain.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//全局变量
//消息钩子
HHOOK g_hook;

//交互界面对象
CDialogMain *dlg=nullptr;

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CSteamPVZApp

BEGIN_MESSAGE_MAP(CSteamPVZApp, CWinApp)
END_MESSAGE_MAP()


// CSteamPVZApp 构造

CSteamPVZApp::CSteamPVZApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CSteamPVZApp 对象

CSteamPVZApp theApp;

//// 辅助对话框
//CDialogMain* g_pDlg = nullptr;


// CSteamPVZApp 初始化

BOOL CSteamPVZApp::InitInstance()
{
	CWinApp::InitInstance();

		//创建交互界面窗口
	/*INT_PTR nResponse = dlg.Create(IDD_DIALOG1);
	dlg.ShowWindow(SW_SHOW);
	dlg.RunModalLoop();*/

	if (!AfxSocketInit()) 
	{
		AfxMessageBox(101);
		return FALSE;
	}

	return TRUE;
}

void __stdcall SetHook()
{
	// 游戏窗口句柄
	HWND hWndGame;
	hWndGame = FindWindow(NULL, GAMENAME);

	// 获取 游戏进程ID和窗口线程ID
	DWORD dwProcessId, dwThreadId;
	dwThreadId = ::GetWindowThreadProcessId(hWndGame, &dwProcessId);

	// 安装钩子
	g_hook = ::SetWindowsHookEx(WH_KEYBOARD,  // 键盘钩子
				KeyboardProc,  // 钩子过程
				GetModuleHandle(_T("Steam_PVZ.dll")), // 钩子函数所在的模块
				dwThreadId); // 游戏窗口线程ID
}

LRESULT WINAPI KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	// 当 "HOME"键抬起时，弹出窗口
	if (code == HC_ACTION && wParam == VK_HOME && GetKeyState(VK_HOME) < 0) 
	{
		if (!dlg) 
		{
			// 新建辅助窗口
			dlg = new CDialogMain;
			dlg->Create(IDD_DIALOG1);

			// 判断游戏是否全屏，如果不是全屏，移到外挂窗口到游戏窗口右侧
			// 否则提示用户去掉‘全屏’设置
			HWND hWndGame = ::FindWindow(NULL, GAMENAME);
			if (IsFullScreenWindow(hWndGame)) 
			{
				AfxMessageBox(_T("请去掉 游戏 ‘全屏’ 设置"));
			}
		}
		dlg->ShowWindow(SW_SHOW);
		return 0;
	}
	else 
	{
		return CallNextHookEx(NULL, code, wParam, lParam);
	}
}

static bool IsFullScreenWindow(HWND hWnd)
{
	bool bFullScreen = false;
	RECT rcApp, rcDesk;
	GetWindowRect(GetDesktopWindow(), &rcDesk);
	if (hWnd != GetDesktopWindow() && hWnd != GetShellWindow()) {
		GetWindowRect(hWnd, &rcApp);
		if (rcApp.left <= rcDesk.left
			&& rcApp.top <= rcDesk.top
			&& rcApp.right >= rcDesk.right
			&& rcApp.bottom >= rcDesk.bottom) {
			bFullScreen = true;
		}
	}
	return bFullScreen;
}