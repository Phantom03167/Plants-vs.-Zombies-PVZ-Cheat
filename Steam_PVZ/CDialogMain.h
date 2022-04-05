#pragma once
#include "afxwin.h"
#include "stdafx.h"


// CDialogMain 对话框

class CDialogMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMain)

public:
	CDialogMain(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogMain();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int Sun;
	int Money;
	BOOL Plant_CD;
	BOOL Potato_Countdown;
	BOOL Bigmouthflower_Digestion;
	BOOL Sun_Limit;
	BOOL Fog_Remove;
	BOOL Auto_Collect;
	BOOL Fast_Belt;
	BOOL Zombie_Weak;
	BOOL Plant_Invincible;
	BOOL See_Vase;
	BOOL Lock_Butter;
	BOOL Mushroom_Awake;
	BOOL Planting_Limit;
	BOOL Background_Running;
	CComboBox Y1;
	CComboBox X1;
	CComboBox Y2;
	CComboBox X2;
	CComboBox Plants1;
	CComboBox Plants2;
	int Times;
protected:
	HICON m_hIcon;
public:
	virtual BOOL OnInitDialog();
	DWORD GetPlants2Id();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck12();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck8();
};

static bool WriteCode(DWORD dwAddr, const unsigned char code[], size_t len);
static void CropCall(DWORD dwType, DWORD dwX, DWORD dwY, DWORD dwIDTarget = 0xFFFFFFFF);
static void _CropCall(DWORD dwType, DWORD dwX, DWORD dwY, DWORD dwIDTarget = 0xFFFFFFFF);
static void RemovePlant(int row, int col);
static DWORD GetHitPlants(int row, int col);