#pragma once
#include"XorStr.h"
#include <iostream>
#include <winnt.rh>
#include <wtypes.h>
#include"baseAddress/gameAddress.h"
#include"mem.h"
#include"myImgui.h"
HANDLE hConsole;
void RandomTitle()
{
	constexpr int length = 25;
	const auto characters = TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`-=~!@#$%^&*()_+,./;'[]|{}:?甲乙丙丁戊己庚辛壬癸子丑寅卯辰巳午未申酉戌亥");
	TCHAR title[length + 1]{};
	for (int j = 0; j != length; j++)
	{
		title[j] += characters[rand() % 95];
	}
	SetConsoleTitle(title);
}

void initGame() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand((unsigned)time(NULL));
	RandomTitle();
	//获取窗口句柄
	address::g_hwnd = FindWindowA(XorStr("SDL_app"), XorStr("Stardew Valley"));

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << "HWND：" << address::g_hwnd << std::endl;
	//获取窗口对应的进程ID
	GetWindowThreadProcessId(address::g_hwnd, &address::g_pid);

	//获取窗口对应的进程句柄
	address::g_handle = OpenProcess(PROCESS_ALL_ACCESS, true, address::g_pid);
	//获取coreclr.dll模块的地址
	if (address::coreclrAddress = mem::GetModule(address::g_pid, L"coreclr.dll")) {
		std::cout << XorStr("获取coreclr.dll成功") << std::endl;
	}
	

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	printf("pid地址：%d\n", address::g_pid);
	printf("coreclrAddress地址：%p\n", address::coreclrAddress);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}


using namespace myImgui;
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initGame();
	

	
	char* 金币指针[9] = {};
	int64_t 金币值 = 0;
	std::cout << "金币值的地址：0x" << std::hex << reinterpret_cast<uintptr_t>(&金币值) << std::endl;
	mem::Read(address::g_handle, address::coreclrAddress + 0x0049D188, &金币指针[1], 8);
	mem::Read(address::g_handle, 金币指针[1] + 0xC8, &金币指针[2], 8);
	mem::Read(address::g_handle, 金币指针[2] + 0x68, &金币指针[3], 8);
	mem::Read(address::g_handle, 金币指针[3] + 0x90, &金币指针[4], 8);
	mem::Read(address::g_handle, 金币指针[4] + 0xdc4, &金币指针[5], 8);
	mem::Read(address::g_handle, 金币指针[5] + 0x10, &金币指针[6], 8);
	mem::Read(address::g_handle, 金币指针[6] + 0x4d0, &金币指针[7], 8);
	mem::Read(address::g_handle, 金币指针[7] + 0x33c, &金币值, 8);
	//std::cout << "金币指针[8] 的地址：" << std::dec << reinterpret_cast<uintptr_t>(金币指针[8]) << std::endl;
	std::cout << "金币值：" << std::dec<<金币值 << std::endl;
	std::cout << "请输入金币值：" << std::dec<<金币值 << std::endl;
	std::cin >> 金币值;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	if (mem::Write(金币指针[7] + 0x33c, &金币值, sizeof(金币值))) {
		std::cout << "修改成功,2秒后自动关闭  "  << std::endl;
	}
	else{
		std::cout << "修改失败！"  << std::endl;
	}
	
	char* 体力值指针[9] = {};
	float 体力值 = 0;
	float a = 400.4;
	mem::Read(address::g_handle, address::coreclrAddress + 0x49D188, &体力值指针[0], 8);
	mem::Read(address::g_handle, 体力值指针[0] + 0xC8, &体力值指针[1], 8);
	mem::Read(address::g_handle, 体力值指针[1] + 0x68, &体力值指针[2], 8);
	mem::Read(address::g_handle, 体力值指针[2] + 0x90, &体力值指针[3], 8);
	mem::Read(address::g_handle, 体力值指针[3] + 0xC74, &体力值指针[4], 8);
	mem::Read(address::g_handle, 体力值指针[4] + 0x10, &体力值指针[5], 8);
	mem::Read(address::g_handle, 体力值指针[5] + 0x4B8, &体力值指针[6], 8);
	mem::Read(address::g_handle, 体力值指针[6] + 0x194, &体力值, 4);
	std::cout << "体力值："  << 体力值 << std::endl;
	mem::Write(体力值指针[6] + 0x194, &a, sizeof(a));

	char* HP指针[9] = {};
	int HP值 = 999;
	mem::Read(address::g_handle, address::coreclrAddress + 0x4A29E8, &HP指针[0], 8);
	mem::Read(address::g_handle, HP指针[0] + 0x270, &HP指针[1], 8);
	mem::Write(HP指针[1] + 0xF4C, &HP值, 4);
	Sleep(2000);
	return 0;


}
