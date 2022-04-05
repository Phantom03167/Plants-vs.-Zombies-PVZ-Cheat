// Steam PVZ Cheat.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "Steam PVZ Cheat.h"
#include "Steam PVZ CheatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSteamPVZCheatApp

BEGIN_MESSAGE_MAP(CSteamPVZCheatApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSteamPVZCheatApp 构造

CSteamPVZCheatApp::CSteamPVZCheatApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CSteamPVZCheatApp 对象

CSteamPVZCheatApp theApp;


// CSteamPVZCheatApp 初始化

BOOL CSteamPVZCheatApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager* pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	//注入dll
	//InjectDll(GAMENAME);

	//EnableDebugPrivilege();
	//setSteam_PVZHook();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CSteamPVZCheatDlg DLG;
	m_pMainWnd = &DLG;
	INT_PTR nResponse = DLG.DoModal();
	//INT_PTR nResponse = DLG.Create(IDD_STEAMPVZCHEAT_DIALOG);
	//DLG.ShowWindow(SW_HIDE);
	//DLG.RunModalLoop();

	

	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//提权
static bool EnableDebugPrivilege()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) {
		return   FALSE;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue)) {
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
		CloseHandle(hToken);
		return false;
	}
	return true;
}

HANDLE GetProcessHandleByTittle(CString str)
{
	HWND hwnd = FindWindow(NULL, str);
	if (hwnd == NULL) return NULL;
	DWORD dwpid = 0;
	GetWindowThreadProcessId(hwnd, &dwpid);
	if (dwpid == 0) return NULL;
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	return handle;
}

HANDLE InjectDll(CString wndname)
{
	int msg = 0;     //MessageBox消息标志

	//提权
	while (FALSE == EnableDebugPrivilege())
	{
		msg = MessageBox(NULL, TEXT("提权失败！"), NULL, MB_RETRYCANCEL);
		if (msg == 4) continue;
		else if (msg == 2) exit(0);
	}

	//获取进程句柄
	HANDLE handle = GetProcessHandleByTittle(wndname);
	while (handle == NULL)
	{
		msg = MessageBox(NULL, TEXT("游戏窗口未打开！"), NULL, MB_RETRYCANCEL);
		if (msg == 4)
		{
			handle = GetProcessHandleByTittle(wndname);
		}
		else if (msg == 2) exit(0);
	}

	CString dllpath = L"Steam_PVZ.dll";

	//在远程线程中分配（虚拟）内存
	LPVOID lpaddr = VirtualAllocEx(handle, NULL, dllpath.GetAllocLength() * 2 + 2, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (lpaddr == NULL)
	{
		MessageBox(NULL, TEXT("内存空间不够！"), NULL, MB_RETRYCANCEL);
		exit(0);
	}

	//在分配的内存中写入DLL路径
	while (FALSE == WriteProcessMemory(handle, lpaddr, dllpath, dllpath.GetAllocLength() * 2 + 2, NULL))
	{
		msg = MessageBox(NULL, TEXT("写入dll失败！"), NULL, MB_RETRYCANCEL);
		if (msg == 4) continue;
		else if (msg == 2) exit(0);
	}

	//获取LoadLibraryW函数地址
	PTHREAD_START_ROUTINE loadlibraryaddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");

	//创建远程线程，调用LoadLibraryW函数载入DLL
	HANDLE handle_dll = CreateRemoteThread(handle, NULL, 0, loadlibraryaddr, lpaddr, 0, NULL);
	if (handle_dll == NULL)
	{
		MessageBox(NULL, TEXT("创建远程线程失败失败！"), NULL, MB_RETRYCANCEL);
	}

	//等待线程时间，防止阻塞
	if (handle_dll && handle_dll != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(handle_dll, 1000);
	}
	
	//释放内存
	VirtualFreeEx(handle, lpaddr, dllpath.GetAllocLength() * 2 + 2, MEM_RELEASE);

	CloseHandle(handle);
	CloseHandle(handle_dll);

	return handle_dll;
}

void __stdcall setSteam_PVZHook()
{
	auto h = LoadLibrary(_T("Steam_PVZ.dll"));
	typedef void(__stdcall* PFun)();
	PFun SetHook = (PFun)GetProcAddress(h, "SetHook");
	if (SetHook) {
		SetHook();
	}
	FreeLibrary(h);
}