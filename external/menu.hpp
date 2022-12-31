#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <d3d9.h>

#include "weapon.hpp"

#pragma comment(lib, "imgui.lib")
#pragma comment(lib, "d3d9.lib")

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace dx {
	// Data
	static LPDIRECT3D9              d3d = {};
	static LPDIRECT3DDEVICE9        d3d_device = {};
	static D3DPRESENT_PARAMETERS    d3d_param = {};
}

namespace ctx {
	inline HWND hWnd = {};
	inline WNDCLASSEXW wc = {};
	inline int menu_width = { 600 }, menu_height = { 350 };
}

class c_menu
{
private:
	static LRESULT WINAPI wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void set_position(int x, int y, int cx, int cy, HWND hwnd);
	void get_mouse_offset(int& x, int& y, HWND hwnd);

private:
	bool create_device_d3d(HWND hWnd);
	void cleanup_device_d3d();
	void on_paint();
	static void reset_device();

public:
	c_menu() = default;
	~c_menu() = default;

	bool setup();
	void render();
	void destroy();
};

inline auto g_menu = std::unique_ptr<c_menu>();