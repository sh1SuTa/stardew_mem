#pragma once
#include"XorStr.h"
#include <iostream>
#include <winnt.rh>
#include <wtypes.h>
#include"baseAddress/gameAddress.h"
#include"mem.h"

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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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



int main()
{

	initGame();
	char* 金币指针[9] = {};
	int64_t 金币值 = 0;
	std::cout << "金币值的地址：0x" << std::hex << reinterpret_cast<uintptr_t>(&金币值) << std::endl;
	mem::Read(address::g_handle, address::coreclrAddress + 0x0049D188, &金币指针[1], 8);
	mem::Read(address::g_handle, 金币指针[1] + 0x48, &金币指针[2], 8);
	mem::Read(address::g_handle, 金币指针[2] + 0x70, &金币指针[3], 8);
	mem::Read(address::g_handle, 金币指针[3] + 0x40, &金币指针[4], 8);
	mem::Read(address::g_handle, 金币指针[4] + 0x15c, &金币指针[5], 8);
	mem::Read(address::g_handle, 金币指针[5] + 0x18, &金币指针[6], 8);
	mem::Read(address::g_handle, 金币指针[6] + 0x408, &金币指针[7], 8);
	mem::Read(address::g_handle, 金币指针[7] + 0xbec, &金币值, 8);
	//std::cout << "金币指针[8] 的地址：" << std::dec << reinterpret_cast<uintptr_t>(金币指针[8]) << std::endl;
	std::cout << "金币值：" << std::dec<<金币值 << std::endl;
	std::cout << "请输入金币值：" << std::dec<<金币值 << std::endl;
	std::cin >> 金币值;
	
	mem::Write(金币指针[7] + 0xbec, &金币值, sizeof(金币值));




}
