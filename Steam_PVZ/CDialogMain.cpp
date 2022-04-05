// CDialogMain.cpp: 实现文件
//

#include "pch.h"
#include "Steam_PVZ.h"
#include "CDialogMain.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "stdafx.h"

#define ID_MFZ 48

// CDialogMain 对话框

IMPLEMENT_DYNAMIC(CDialogMain, CDialogEx)
CDialogMain::CDialogMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, Sun(10000)
	, Plant_CD(FALSE)
	, Potato_Countdown(FALSE)
	, Bigmouthflower_Digestion(FALSE)
	, Money(999999)
	, Times(1)
	, Sun_Limit(FALSE)
	, Fog_Remove(FALSE)
	, Auto_Collect(FALSE)
	, See_Vase(FALSE)
	, Zombie_Weak(FALSE)
	, Plant_Invincible(FALSE)
	, Fast_Belt(FALSE)
	, Lock_Butter(FALSE)
	, Planting_Limit(FALSE)
	, Mushroom_Awake(FALSE)
	, Background_Running(FALSE)
{

}

CDialogMain::~CDialogMain()
{
}

void CDialogMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Sun);
	DDX_Text(pDX, IDC_EDIT1, Sun);
	DDX_Check(pDX, IDC_CHECK1, Plant_CD);
	DDX_Check(pDX, IDC_CHECK2, Potato_Countdown);
	DDX_Check(pDX, IDC_CHECK3, Bigmouthflower_Digestion);
	DDX_Text(pDX, IDC_EDIT2, Money);
	DDX_Control(pDX, IDC_COMBO1, Y1);
	DDX_Control(pDX, IDC_COMBO2, X1);
	DDX_Control(pDX, IDC_COMBO3, Y2);
	DDX_Control(pDX, IDC_COMBO4, X2);
	DDX_Control(pDX, IDC_COMBO5, Plants1);
	DDX_Control(pDX, IDC_COMBO6, Plants2);
	DDX_Text(pDX, IDC_EDIT3, Times);
	DDX_Check(pDX, IDC_CHECK4, Sun_Limit);
	DDX_Check(pDX, IDC_CHECK5, Fog_Remove);
	DDX_Check(pDX, IDC_CHECK7, Auto_Collect);
	DDX_Check(pDX, IDC_CHECK6, See_Vase);
	DDX_Check(pDX, IDC_CHECK9, Zombie_Weak);
	DDX_Check(pDX, IDC_CHECK10, Plant_Invincible);
	DDX_Check(pDX, IDC_CHECK11, Fast_Belt);
	DDX_Check(pDX, IDC_CHECK13, Lock_Butter);
	DDX_Check(pDX, IDC_CHECK12, Planting_Limit);
	DDX_Check(pDX, IDC_CHECK14, Mushroom_Awake);
	DDX_Check(pDX, IDC_CHECK8, Background_Running);
}


BEGIN_MESSAGE_MAP(CDialogMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogMain::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CDialogMain::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDialogMain::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDialogMain::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogMain::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CDialogMain::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogMain::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK4, &CDialogMain::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogMain::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK5, &CDialogMain::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialogMain::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK7, &CDialogMain::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK6, &CDialogMain::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK9, &CDialogMain::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CDialogMain::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CDialogMain::OnBnClickedCheck11)
	ON_BN_CLICKED(IDC_CHECK13, &CDialogMain::OnBnClickedCheck13)
	ON_BN_CLICKED(IDC_CHECK12, &CDialogMain::OnBnClickedCheck12)
	ON_BN_CLICKED(IDC_CHECK14, &CDialogMain::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_CHECK8, &CDialogMain::OnBnClickedCheck8)
END_MESSAGE_MAP()

// 写内存:修改代码
static bool WriteCode(DWORD dwAddr, const unsigned char code[], size_t len)
{
	DWORD dwOld;
	if (!VirtualProtect((LPVOID)dwAddr, len, PAGE_EXECUTE_READWRITE, &dwOld)) {
		return false;
	}

	memcpy_s((void*)dwAddr, len, code, len);

	DWORD dwNew;
	if (VirtualProtect((LPVOID)dwAddr, len, dwOld, &dwNew)) {
		return true;
	}
	return false;
}


// CDialogMain 消息处理程序


BOOL CDialogMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// 初始化列表

	// 起点
	// 行:最多6行
	for (int x = 1; x <= 6; ++x) 
	{
		CString str;
		str.Format(_T("%d"), x);
		Y1.AddString(str);
	}
	Y1.SetCurSel(0);

	// 列:最多9列
	for (int y = 1; y <= 9; ++y) 
	{
		CString str;
		str.Format(_T("%d"), y);
		X1.AddString(str);
	}
	X1.SetCurSel(0);

	// 终点
	// 行:最多6行
	for (int x = 1; x <= 6; ++x) 
	{
		CString str;
		str.Format(_T("%d"), x);
		Y2.AddString(str);
	}
	Y2.SetCurSel(5);

	// 列:最多9列
	for (int y = 1; y <= 9; ++y) 
	{
		CString str;
		str.Format(_T("%d"), y);
		X2.AddString(str);
	}
	X2.SetCurSel(8);

	// 所有植物
	{
		CString str[] = { _T(" 0:豌豆射手"), _T(" 1:向日葵"), _T(" 2:樱桃炸弹"), _T(" 3:坚果墙"),
						  _T(" 4:土豆雷"), _T(" 5:寒冰射手"), _T(" 6:大嘴花"), _T(" 7:双发射手"),

						  _T(" 8:小喷菇"), _T(" 9:阳光菇"), _T("10:大喷菇"), _T("11:墓碑吞噬者"),
						  _T("12:魅惑菇"), _T("13:胆小菇"), _T("14:寒冰菇"), _T("15:毁灭菇"),

						  _T("16:睡莲"), _T("17:窝瓜"), _T("18:三线射手"), _T("19:缠绕海草"),
						  _T("20:火爆辣椒"), _T("21:地刺"), _T("22:火炬树桩"), _T("23:高坚果"),

						  _T("24:海蘑菇"), _T("25:路灯花"), _T("26:仙人掌"), _T("27:三叶草"),
						  _T("28:裂荚射手"), _T("29:杨桃"), _T("30:南瓜头"), _T("31:磁力菇"),

						  _T("32:卷心菜投手"), _T("33:花盆"), _T("34:玉米投手"), _T("35:咖啡豆"),
						  _T("36:大蒜"), _T("37:叶子保护伞"), _T("38:金盏花"), _T("39:西瓜投手"),

						  _T("40:机枪射手"), _T("41:双子向日葵"), _T("42:忧郁蘑菇"), _T("43:香蒲"),
						  _T("44:“冰”瓜"), _T("45:吸金磁"), _T("46:地刺王"), _T("47:玉米加农炮"),

						  _T("48:模仿者"), _T("49:爆炸坚果"), _T("50:巨大坚果墙")
		};

		for (auto s : str)
		{
			Plants1.AddString(s);
		}
		Plants1.SetCurSel(0);
	}

	// 被模仿植物
	{
		CString str[] = { _T(" 0:豌豆射手"), _T(" 1:向日葵"), _T(" 2:樱桃炸弹"), _T(" 3:坚果墙"),
						  _T(" 4:土豆雷"), _T(" 5:寒冰射手"), _T(" 6:大嘴花"), _T(" 7:双发射手"),

			/*_T(" 8:小喷菇"), _T(" 9:阳光菇"), _T("10:大喷菇"), _T("11:墓碑吞噬者"),
			_T("12:魅惑菇"), _T("13:胆小菇"), _T("14:寒冰菇"), _T("15:毁灭菇"),*/

			_T("16:睡莲"), _T("17:窝瓜"), _T("18:三线射手"), _T("19:缠绕海草"),
			_T("20:火爆辣椒"), _T("21:地刺"), _T("22:火炬树桩"), _T("23:高坚果"),

			/*_T("24:海蘑菇"), _T("25:路灯花"), */_T("26:仙人掌"), _T("27:三叶草"),
			_T("28:裂荚射手"), _T("29:杨桃"), _T("30:南瓜头"), /*_T("31:磁力菇"),*/

			_T("32:卷心菜投手"), /*_T("33:花盆"),*/ _T("34:玉米投手"), _T("35:咖啡豆"),
			_T("36:大蒜"), _T("37:叶子保护伞"), _T("38:金盏花"), _T("39:西瓜投手")/*,

			_T("40:机枪射手"), _T("41:双子向日葵"), _T("42:忧郁蘑菇"), _T("43:香蒲"),
			_T("44:“冰”瓜"), _T("45:吸金磁"), _T("46:地刺王"), _T("47:玉米加农炮"),

			_T("48:模仿者"), _T("49:爆炸坚果"), _T("50:巨大坚果墙")*/
		};

		for (auto s : str)
		{
			Plants2.AddString(s);
		}
		Plants2.SetCurSel(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
// 异常: OCX 属性页应返回 FALSE
}


//设置阳光
void CDialogMain::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//阳光地址：[[[00731C50]+00000868]+00005578]
	DWORD* dwAddr = (DWORD*)0x00731C50;     //基地址
	dwAddr = (DWORD*)(*dwAddr + 0x00000868);     //一级偏移地址
	dwAddr = (DWORD*)(*dwAddr + 0x00005578);     //二级偏移地址，即当前阳光地址
	*dwAddr = Sun;

	UpdateData(FALSE);
}


//植物无CD
void CDialogMain::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	//004958C5   - 7E 14   - jle 004958DB     //未完成冷却时跳转，改为nop 90 90
	UpdateData(TRUE);
	DWORD Addr = 0x004958C5;

	if (Plant_CD)
	{
		//无CD  改为nop  //90 90
		UCHAR buf[2] = { 0x90,0x90 };
		WriteCode(Addr, buf, sizeof(buf));
	}
	else
	{
		//有CD  改为7E 14
		UCHAR buf[2] = { 0x7E,0x14 };
		WriteCode(Addr, buf, sizeof(buf));
	}
}


//土豆雷无倒计时
void CDialogMain::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	//00466203   - 0F85 FD010000   - jne 00466406     //未完成冷却时跳转，改为nop 90 90 90 90 90 90
	UpdateData(TRUE);
	DWORD Addr = 0x00466203;

	if (Potato_Countdown)
	{
		//无CD  改为nop  //90 90 90 90 90 90
		UCHAR buf[6] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteCode(Addr, buf, sizeof(buf));
	}
	else
	{
		//有CD  改为0F85 FD010000
		UCHAR buf[6] = { 0x0F,0x85,0xFD,0x01,0x00,0x00 };
		WriteCode(Addr, buf, sizeof(buf));
	}
}


//超级大嘴花
void CDialogMain::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	//00467905   - 75 5F   - jne 00467966     //未完成消化时跳转，改为nop 90 90
	UpdateData(TRUE);
	DWORD Addr = 0x00467905;

	if (Bigmouthflower_Digestion)
	{
		//无CD  改为nop nop //90 90
		UCHAR buf[2] = { 0x90,0x90 };
		WriteCode(Addr, buf, sizeof(buf));
	}
	else
	{
		//有CD  改为75 5F
		UCHAR buf[2] = { 0x75,0x5F };
		WriteCode(Addr, buf, sizeof(buf));
	}
}


//设置金钱
void CDialogMain::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//金钱偏移地址：[[[00731C50]+0000094C]+54]
	DWORD* dwAddr = (DWORD*)0x00731C50;     //基地址
	dwAddr = (DWORD*)(*dwAddr + 0x0000094C);     //一级偏移地址
	dwAddr = (DWORD*)(*dwAddr + 0x54);     //二级偏移地址，即当前阳光地址
	*dwAddr = Money;

	UpdateData(FALSE);
}


// 选择模仿者植物
void CDialogMain::OnCbnSelchangeCombo5()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = Plants1.GetCurSel();
	if (index == ID_MFZ)
	{
		Plants2.EnableWindow(TRUE);
	}
	else
	{
		Plants2.EnableWindow(FALSE);
	}
}


void CDialogMain::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwId = GetPlants2Id();
	for (int times = 0; times < Times; times++)
	{
		for (DWORD x = X1.GetCurSel(); x <= X2.GetCurSel(); x++)
		{
			for (DWORD y = Y1.GetCurSel(); y <= Y2.GetCurSel(); y++)
			{
				CropCall(Plants1.GetCurSel(), x, y, dwId);
			}
		}
	}
	UpdateData(FALSE);
}


DWORD CDialogMain::GetPlants2Id()
{
	CString str;
	int index = Plants2.GetCurSel();
	Plants2.GetLBText(index, str);
	if (str.IsEmpty()) {
		return 0xFFFFFFFF;
	}
	DWORD dwId = 0xFFFFFFFF;
	{
		// 查找数字, 转成 植物ID
		int index = str.Find(_T(":"));
		if (index < 0) {
			return 0xFFFFffff;
		}
		PTSTR szEndPtr;
		dwId = _tcstol(str.Mid(0, index).GetString(), &szEndPtr, 0xA);
	}
	return dwId;
}


static void CropCall(DWORD dwType, DWORD dwX, DWORD dwY, DWORD dwIDTarget)
{
	// 如果是模访者
	if (dwType == ID_MFZ) {
		_CropCall(dwType, dwX, dwY, dwIDTarget);
	}
	else {
		_CropCall(dwType, dwX, dwY);
	}
}

static void _CropCall(DWORD dwType, DWORD dwX, DWORD dwY, DWORD dwIDTarget)
{
	__try {
		__asm {
			pushad;
			pushfd;
			push dwIDTarget; // 如果模访者，则是被模访的植物的ID
			push dwType;      // 植物类型(ID)
			mov eax, dwY; // y坐标
			push dwX;      // x坐标

			mov ebp, 0x00731C50;
			mov ebp, dword ptr[ebp];
			add ebp, 0x00000868;
			mov ebp, dword ptr[ebp];
			push ebp;

			mov esi, 0x004105A0; // 调用CALL
			call esi;

			popfd;
			popad;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {

	}
}


//解除阳光限制
void CDialogMain::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	//0041F67F - 0F9E C0   - setle al         //改为mov al,1   -B0 01 90   或者nop 90 90 90
	//0041F632 - 7F 0C - jg 0041F640          //不够时跳转，改为nop 90 90
	//0041F634 - 2B F3 - sub esi, ebx         //减少阳光，改为nop 90 90
	UpdateData(TRUE);
	DWORD Addr1 = 0x0041F67F;
	DWORD Addr2 = 0x0041F632;

	if (Sun_Limit)
	{
		//无限制
		{
			UCHAR buf[3] = { 0xB0,0x01,0x90 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[4] = { 0x90,0x90,0x90,0x90 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
	}
	else
	{
		//有限制
		{
			UCHAR buf[3] = { 0x0F,0x9E,0xC0 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[4] = { 0x7F,0x0C,0x2B,0xF3 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
	}
}


//铲除植物
void CDialogMain::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	for (int times = 0; times < Times; times++)
	{
		for (DWORD x = X1.GetCurSel(); x <= X2.GetCurSel(); x++)
		{
			for (DWORD y = Y1.GetCurSel(); y <= Y2.GetCurSel(); y++)
			{
				RemovePlant(x, y);
			}
		}
	}
	UpdateData(FALSE);
}



static void RemovePlant(int row, int col)
{
	__try {
		DWORD dwBase = GetHitPlants(row, col);
		if (dwBase) {
			__asm {
				pushfd;
				pushad;

				mov ebp, dwBase;
				push ebp;
				mov eax, 0x0046DE50;
				call eax;

				popad;
				popfd;

			}
		}
		else {
			// 指定位置没有植物，什么也不做
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {

	}
}


// 获得某位置的值物
static DWORD GetHitPlants(int row, int col)
{
	int a = row, b = col;
	DWORD dwArr[10] = { 0 };
	__asm {
		pushfd;
		pushad;

		push b;
		push a;
		mov edx, 0x00731C50;
		mov edx, dword ptr[edx];
		mov edx, dword ptr[edx + 0x868];
		mov esi, edx;
		lea ebx, dwArr;
		mov eax, 0x00410830;
		call eax;

		popad;
		popfd;
	};
	return dwArr[3];
}

void CDialogMain::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	//0041DF4D - 3B F2 - cmp esi, edx            //改为- xor edx,edx     //31 D2
	UpdateData(TRUE);
	DWORD Addr = 0x0041DF4D;

	if (Fog_Remove)
	{
		//浓雾透视  改为- xor edx,edx //31 D2
		UCHAR buf[2] = { 0x31,0xD2 };
		WriteCode(Addr, buf, sizeof(buf));
	}
	else
	{
		//恢复  改为3B F2
		UCHAR buf[2] = { 0x3B,0xF2 };
		WriteCode(Addr, buf, sizeof(buf));
	}
}


//秒杀僵尸
void CDialogMain::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int zombie_struct_size = 0x168;
	
	int zombie_count_max = *(DWORD*)(*(DWORD*)(*(DWORD*)0x731c50 + 0x868) + (0xAC));
	DWORD zombie_offset = *(DWORD*)(*(DWORD*)(*(DWORD*)0x731c50 + 0x868) + 0xA8);

	for (int i = 0; i < zombie_count_max; i++)
	{
		if (!*(DWORD*)(zombie_offset+i*zombie_struct_size+0xEC))     // 没有消失
		{
			*(DWORD*)(zombie_offset + i * zombie_struct_size + 0x28) = 3;     // 3 秒杀
		}
	}
}


//自动收集资源
void CDialogMain::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	//004352F2   - 75 09   - jne 004352FD     //（判断是否点击）改为jmp 004352FD     //EB 09
	UpdateData(TRUE);
	DWORD Addr = 0x004352F2;

	if (Auto_Collect)
	{
		//自动收集资源  改为- 改为jmp 004352FD //EB 09
		UCHAR buf[1] = { 0xEB };
		WriteCode(Addr, buf, sizeof(buf));
	}
	else
	{
		//恢复  改为75 09
		UCHAR buf[1] = { 0x75 };
		WriteCode(Addr, buf, sizeof(buf));
	}
}


//罐子透视
void CDialogMain::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	//004531CA   - 85 C0   - test eax, eax     //改为mov ax,0033     //66 B8 3300
	//004531CC   - 7E 04   - jle 004531D2      //改为上行
	UpdateData(TRUE);
	DWORD Addr = 0x004531CA;

	if (See_Vase)
	{
		//罐子透视     改为mov ax,0033     //66 B8 3300
		{
			UCHAR buf[4] = { 0x66,0xB8,0x33,0x00 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复     改为85 C0  7E 04
		{
			UCHAR buf[4] = { 0x85,0xC0,0x7E,0x04 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
}


//一击必杀
void CDialogMain::OnBnClickedCheck9()
{
	// TODO: 在此添加控件通知处理程序代码
	//00545DFA - 2B 6C 24 20 - sub ebp, [esp + 20]      // _zombie_immune_damage   改为- sub ebp,ebp    //2B ED 90 90
	//00545B14 - 2B C8 - sub ecx, eax                   // _zombie_immune_type1    改为- sub ecx,ecx    //2B C9
	//0054576B - 7C 02 - jl 0054576F                    // _zombie_immune_type2    改为- movedx,eax     //8B D0
	//00547690 - 0F8D 48040000 - jnl 00547ADE           // _zombie_immune_ashes    改为- jo 00547ADE    //0F80 48040000
	UpdateData(TRUE);
	DWORD Addr1 = 0x00545DFB;
	DWORD Addr2 = 0x00545b15;
	DWORD Addr3 = 0x0054576B;
	DWORD Addr4 = 0x00547691;

	if (Zombie_Weak)
	{
		//一击必杀
		{
			UCHAR buf[3] = { 0xED,0x90,0x90 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0xC9 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
		{
			UCHAR buf[2] = { 0x8B,0xD0 };
			WriteCode(Addr3, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x80 };
			WriteCode(Addr4, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复
		{
			UCHAR buf[3] = { 0x6C,0x24,0x20 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0xC8 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
		{
			UCHAR buf[2] = { 0x7C,0x02 };
			WriteCode(Addr3, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x8D };
			WriteCode(Addr4, buf, sizeof(buf));
		}
	}
}


//植物无敌
void CDialogMain::OnBnClickedCheck10()
{
	// TODO: 在此添加控件通知处理程序代码
	//005447A0   - 83 46 40 FC   - add dword ptr[esi + 40], -04     // plant_immune_bite   改为- add dword ptr [esi+40],00   - 83 46 40 00
	//004207DF   - 74 0C   - je 004207ED                            // plant_immune_blast   改为- jmp 004207ED   - EB 0C
	//0053BEDA   - 75 42   - jne 0053BF1E                           // plant_immune_burn   改为- jmp 0053BF1E   - EB 42
	//00474FFB   - 29 50 40   - sub [eax+40],edx                    // plant_immune_pea   改为nop   - 90 90 90
	//004757B9   - 29 4E 40   - sub [esi+40],ecx                    // plant_immune_ball   改为nop   - 90 90 90
	//005433AB   - 74 53   - je 00543400                            // plant_immune_squish   改为- jmp 00543400   - EB 53
	//0046511A   - 75 09   - jne 00465125                           // plant_immune_spikeweed   改为- jo 00465125
	//00464F73   - 83 46 40 CE   - add dword ptr [esi+40],-32       // plant_immune_spikerock   改为- add dword ptr [esi+40],00   - 83 46 40 00
	//00468F60   - 53   - push ebx                                  // plant_immune_zomboss   改为- ret 0004   - C2 0400
	UpdateData(TRUE);
	DWORD Addr1 = 0x005447A3;
	DWORD Addr2 = 0x004207DF;
	DWORD Addr3 = 0x0053BEDA;
	DWORD Addr4 = 0x00474FFB;
	DWORD Addr5 = 0x004757B9;
	DWORD Addr6 = 0x005433AB;
	DWORD Addr7 = 0x0046511A;
	DWORD Addr8 = 0x00464F76;
	DWORD Addr9 = 0x00468F60;

	if(Plant_Invincible)
	{
		//植物无敌
		{
			UCHAR buf[1] = { 0x00 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0xEB };
			WriteCode(Addr2, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0xEB };
			WriteCode(Addr3, buf, sizeof(buf));
		}
		{
			UCHAR buf[3] = { 0x90,0x90,0x90 };
			WriteCode(Addr4, buf, sizeof(buf));
		}
		{
			UCHAR buf[3] = { 0x90,0x90,0x90 };
			WriteCode(Addr5, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0xEB };
			WriteCode(Addr6, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x70 };
			WriteCode(Addr7, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x00 };
			WriteCode(Addr8, buf, sizeof(buf));
		}
		{
			UCHAR buf[3] = { 0xC2,0x04,0x00 };
			WriteCode(Addr9, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复
		{
			UCHAR buf[1] = { 0xFC };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x74 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x75 };
			WriteCode(Addr3, buf, sizeof(buf));
		}
		{
			UCHAR buf[3] = { 0x29,0x50,0x40 };
			WriteCode(Addr4, buf, sizeof(buf));
		}
		{
			UCHAR buf[3] = { 0x29,0x4E,0x40 };
			WriteCode(Addr5, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x74 };
			WriteCode(Addr6, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x75 };
			WriteCode(Addr7, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0xCE };
			WriteCode(Addr8, buf, sizeof(buf));
		}
		{
			UCHAR buf[3] = { 0x53,0x55,0x8B };
			WriteCode(Addr9, buf, sizeof(buf));
		}
	}
}


//连续传送
void CDialogMain::OnBnClickedCheck11()
{
	// TODO: 在此添加控件通知处理程序代码
	//0042684E - 0F8F 82070000 - jg 00426FD6          //改为- jo 00426FD6   - 0F80 82070000
	//0049831E - 85 C0 - test eax, eax                   //改为- xor eax,eax   - 33 C0
	UpdateData(TRUE);
	DWORD Addr1 = 0x0042684F;
	DWORD Addr2 = 0x0049831E;

	if (Fast_Belt)
	{
		//连续传送
		{
			UCHAR buf[1] = { 0x80 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x33 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复
		{
			UCHAR buf[1] = { 0x8F };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[1] = { 0x85 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
	}
}


//锁定黄油
void CDialogMain::OnBnClickedCheck13()
{
	// TODO: 在此添加控件通知处理程序代码
	//00465522   - 75 3F   - jne 00465563     //改为- jo 00465563     //70 3F
	UpdateData(TRUE);
	DWORD Addr = 0x00465522;

	if (Lock_Butter)
	{
		//锁定黄油     改为- jo 00465563     //70 3F
		{
			UCHAR buf[1] = { 0x70 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复     改为75 3F
		{
			UCHAR buf[1] = { 0x75 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
}


//解除种植限制
void CDialogMain::OnBnClickedCheck12()
{
	// TODO: 在此添加控件通知处理程序代码
	//00421396   - 75 16   - jne 004213AE          //改为-jmp 0042144F     //E9 B4000000
	//0041334F   - 0F84 20090000   - je 00413C75   //正常时跳转，改为-jmp 00413C75     //E9 21090000   90
	UpdateData(TRUE);
	DWORD Addr1 = 0x00421396;
	DWORD Addr2 = 0x0041334F;

	if (Planting_Limit)
	{
		//解除种植限制     改为-jmp 00413C75     //E9 21090000   90
		{
			UCHAR buf[5] = { 0xE9,0xB4,0x00,0x00,0x00 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[6] = { 0xE9,0x21,0x09,0x00,0x00,0x90 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复     改为0F84 20090000
		{
			UCHAR buf[5] = { 0x75,0x16,0x90,0x90,0x90 };
			WriteCode(Addr1, buf, sizeof(buf));
		}
		{
			UCHAR buf[6] = { 0x0F,0x84,0x20,0x09,0x00,0x00 };
			WriteCode(Addr2, buf, sizeof(buf));
		}
	}
}


//蘑菇睡醒
void CDialogMain::OnBnClickedCheck14()
{
	// TODO: 在此添加控件通知处理程序代码
	//004641A2   - 74 1F   - je 004641C3     //改为-jmp 004641C3     //EB 1F
	UpdateData(TRUE);
	DWORD Addr = 0x004641A2;

	if (Mushroom_Awake)
	{
		//蘑菇睡醒     改为-jmp 004641C3     //EB 1F
		{
			UCHAR buf[1] = { 0xEB };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
	else
	{
		//恢复     改为74
		{
			UCHAR buf[1] = { 0x74 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
}


//允许后台运行
void CDialogMain::OnBnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	//005D87C9   - 74 40   - je 005D880B     //改为- jmp 005D87CB     //EB 00
	UpdateData(TRUE);
	DWORD Addr = 0x005D87C9;

	if (Background_Running)
	{
		//允许后台运行     改为- jmp 005D87CB     //EB 00
		{
			UCHAR buf[2] = { 0xEB,0x00 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
	else
	{
		//禁止后台运行     改为74 40
		{
			UCHAR buf[2] = { 0x74,0x40 };
			WriteCode(Addr, buf, sizeof(buf));
		}
	}
}
