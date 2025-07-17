#pragma once
#pragma once
#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include"baseAddress/gameAddress.h"

WINUSERAPI SHORT WINAPI GetAsyncKeyState(int vKey);

namespace mem
{
    inline char* GetModule(DWORD PID, const wchar_t* ģ������)
    {
        HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
        if (handle == INVALID_HANDLE_VALUE)
        {
            return nullptr;
        }

        MODULEENTRY32 module_info;
        ZeroMemory(&module_info, sizeof(module_info));
        module_info.dwSize = sizeof(module_info);

        bool ret = Module32First(handle, &module_info);
        if (!ret)
        {
            return nullptr;
        }

        do
        {
            //�ж�ģ�����Ƿ����
            if (wcscmp(ģ������, module_info.szModule) == 0)
            {
                //����ҵ��˾ʹ�ӡģ��ĵ�ַ �����ظ�ģ��ĵ�ַ
                //printf("%ws %llx\n", module_info.szModule, module_info.modBaseAddr);
                CloseHandle(handle);
                return (char*)(module_info.modBaseAddr);
            }
        } while (Module32Next(handle, &module_info));

        CloseHandle(handle);
        return nullptr;
    }
    inline bool Read(HANDLE ���̾��, char* �ڴ��ַ, void* ���ָ��, int ����ȡ�ֽ�)
    {
        SIZE_T ������;
        if (ReadProcessMemory(���̾��, �ڴ��ַ, ���ָ��, ����ȡ�ֽ�, &������))
            return true;
        return false;
    }
    inline bool Write(char* �ڴ��ַ, void* д������, int ��д���ֽ�)
    {
        SIZE_T ������;
        if (WriteProcessMemory(address::g_handle, �ڴ��ַ, д������, ��д���ֽ�, &������))
            return true;
        return false;
    }
}