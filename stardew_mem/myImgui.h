#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
namespace myImgui {
	inline ID3D11Device* g_pd3dDevice = nullptr;
	inline ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	inline IDXGISwapChain* g_pSwapChain = nullptr;
	inline ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CreateRenderTarget();
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();