#include "pch.hpp"
#include "menu.hpp"

void c_menu::on_paint() {
	static int x = 0, y = 0;

	ImGui::SetNextWindowSize({ (float)ctx::menu_width, (float)ctx::menu_height }, ImGuiCond_Once);
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Once);

	if (!var::b_is_running)
		std::exit(0);

	if (ImGui::Begin("external", &var::b_is_running, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove))
	{
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			get_mouse_offset(x, y, ctx::hWnd);

		if (y >= 0 && y <= (ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y * 4) && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			set_position(x, y, ctx::menu_width, ctx::menu_height, ctx::hWnd);

		if (ImGui::BeginTabBar("##var::external::tabs"))
		{
			if (ImGui::BeginTabItem("aimbot")) {
				// aimbot
				ImGui::Text("aimbot");
				ImGui::Separator();
				ImGui::Checkbox("enable##aimbot", &config.aimbot.b_aim_enable);
				ImGui::SliderFloat("smooth", &config.aimbot.f_aim_smooth, 1.f, 360.f);
				ImGui::SliderFloat("fov", &config.aimbot.f_aim_fov, 1.f, 180.f);

				// triggerbot
				ImGui::Text("triggerbot");
				ImGui::Separator();
				ImGui::Checkbox("enable##triggerbot", &config.aimbot.b_trigger_enable);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("visuals")) {
				// glow
				ImGui::Text("visuals");
				ImGui::Separator();
				ImGui::Checkbox("enable##glow", &config.visuals.b_glow_enable);
				ImGui::Checkbox("health based", &config.visuals.b_glow_health_based);
				ImGui::Checkbox("visible only", &config.visuals.b_glow_visible_only);
				ImGui::ColorPicker4("color", (float*)&config.visuals.f_glow_color);

				ImGui::Text("skinchanger");
				ImGui::Separator();
				ImGui::Checkbox("enable##sc", &config.visuals.b_sc_enable);
				ImGui::Checkbox("set paint kit", &config.visuals.b_sc_set_paint_kit);

				static char paint_kit_buf[32];
				ImGui::InputText("paint kit", paint_kit_buf, IM_ARRAYSIZE(paint_kit_buf));

				var::skins::str_paint_kit = paint_kit_buf;

				ImGui::Combo("model", &config.visuals.i_sc_selected_model_index, var::skins::models.data(), (std::int32_t)var::skins::models.size());

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("misc")) {
				// bhop
				ImGui::Text("bhop");
				ImGui::Separator();
				ImGui::Checkbox("enable##misc", &config.misc.b_enable_bhop);

				// edge jump
				ImGui::Text("edge jump");
				ImGui::Separator();
				ImGui::Checkbox("enable##edgejump", &config.misc.b_enable_ej);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("config")) {
				ImGui::Text("Config settings");
				ImGui::Separator();

				if (ImGui::Button("Open config folder"))
				{
					if (PIDLIST_ABSOLUTE pidl; SUCCEEDED(SHParseDisplayName(config.get_path().wstring().data(), 0, &pidl, 0, 0)))
					{
						ITEMIDLIST id_null = { 0 };
						LPCITEMIDLIST pidl_null[1] = { &id_null };
						SHOpenFolderAndSelectItems(pidl, 1, pidl_null, 0);
						ILFree(pidl);
					}
				}

				constexpr auto& config_items = config.get_configs();
				static auto current_config = -1;

				if ((size_t)(current_config) >= config_items.size())
					current_config = -1;

				static char buffer[32];

				ImGui::Text("Configs");
				if (ImGui::ListBox("##var::external::config_list", &current_config, [](void* data, int idx, const char** out_text)
					{
						auto& vector = *(std::vector<std::string> *)(data);
						*out_text = vector[idx].c_str();
						return true;
					}, &config_items, (int)(config_items.size()), 5) && current_config != -1) strcpy_s(buffer, config_items[current_config].c_str());

					if (ImGui::InputText("##var::external::config_name", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
					{
						if (current_config != -1)
							config.rename(current_config, buffer);
					}

					if (ImGui::Button("Create", ImVec2(60, 25)))
						config.add(buffer);

					ImGui::SameLine();

					if (ImGui::Button("Reset", ImVec2(60, 25)))
						config.reset();

					ImGui::SameLine();

					if (current_config > -1)
					{
						if (ImGui::Button("Save", ImVec2(60, 25)))
							config.save(current_config);

						ImGui::SameLine();

						if (ImGui::Button("Load", ImVec2(60, 25)))
							config.load(current_config);

						ImGui::SameLine();

						if (ImGui::Button("Delete", ImVec2(60, 25)))
							config.remove(current_config);
					}

					ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("debug")) {

				ImGui::Text("debug");
				ImGui::Separator();
				static bool show_advanced_debug{ false };
				ImGui::Checkbox("Show advanced debug info", &show_advanced_debug);

				if (show_advanced_debug)
				{
					ImGui::Text("Information");
					ImGui::Separator();

					ImGui::Text("Application average: %.1f ms (%.1f fps)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}

void c_menu::set_position(int x, int y, int cx, int cy, HWND hwnd)
{
	POINT point; GetCursorPos(&point);

	auto flags = SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE;
	if (x != 0 && y != 0)
	{
		x = point.x - x;
		y = point.y - y;
		flags &= ~SWP_NOMOVE;
	}

	if (cx != 0 && cy != 0)
		flags &= ~SWP_NOSIZE;

	SetWindowPos(hwnd, nullptr, x, y, cx, cy, flags);
}

void c_menu::get_mouse_offset(int& x, int& y, HWND hwnd)
{
	POINT point; RECT rect;

	GetCursorPos(&point);
	GetWindowRect(hwnd, &rect);

	x = point.x - rect.left;
	y = point.y - rect.top;
}

bool c_menu::setup() {
	// Create application window
	ImGui_ImplWin32_EnableDpiAwareness();
	ctx::wc = {
		sizeof(ctx::wc),
		CS_CLASSDC,
		wnd_proc,
		0L, 0L,
		GetModuleHandle(NULL),
		NULL, NULL,
		NULL, NULL,
		L"Class",
		NULL
	};

	RegisterClassEx(&ctx::wc);
	ctx::hWnd = CreateWindow(
		ctx::wc.lpszClassName, L"",
		WS_POPUP,
		100, 100,
		ctx::menu_width, ctx::menu_height,
		NULL, NULL, 
		ctx::wc.hInstance,
		NULL
	);

	// Initialize Direct3D
	if (!create_device_d3d(ctx::hWnd))
	{
		cleanup_device_d3d();
		UnregisterClass(ctx::wc.lpszClassName, ctx::wc.hInstance);
		return false;
	}

	ShowWindow(ctx::hWnd, SW_SHOWDEFAULT);
	UpdateWindow(ctx::hWnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(ctx::hWnd);
	ImGui_ImplDX9_Init(dx::d3d_device);

	return true;
}

void c_menu::render() 
{
	// Our state
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	bool done = false;
	while (!done)
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				done = true;
		}

		if (done)
			break;

		// Start the Dear ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		on_paint();
		ImGui::EndFrame();

		dx::d3d_device->SetRenderState(D3DRS_ZENABLE, FALSE);
		dx::d3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		dx::d3d_device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		
		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
		dx::d3d_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
		
		if (dx::d3d_device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			dx::d3d_device->EndScene();
		}

		HRESULT result = dx::d3d_device->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && dx::d3d_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			reset_device();
	}

	this->destroy();
}

void c_menu::destroy() {
	// Destroy
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	cleanup_device_d3d();
	DestroyWindow(ctx::hWnd);
	UnregisterClass(ctx::wc.lpszClassName, ctx::wc.hInstance);
}

bool c_menu::create_device_d3d(HWND hWnd)
{
	if ((dx::d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&dx::d3d_param, sizeof(dx::d3d_param));
	dx::d3d_param.Windowed = TRUE;
	dx::d3d_param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dx::d3d_param.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
	dx::d3d_param.EnableAutoDepthStencil = TRUE;
	dx::d3d_param.AutoDepthStencilFormat = D3DFMT_D16;
	dx::d3d_param.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	// g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (dx::d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dx::d3d_param, &dx::d3d_device) < 0)
		return false;

	return true;
}

void c_menu::cleanup_device_d3d()
{
	if (dx::d3d_device) {
		dx::d3d_device->Release();
		dx::d3d_device = NULL;
	}

	if (dx::d3d) {
		dx::d3d->Release();
		dx::d3d = NULL;
	}
}

void c_menu::reset_device()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT hr = dx::d3d_device->Reset(&dx::d3d_param);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

LRESULT WINAPI c_menu::wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		case WM_SIZE:
			if (dx::d3d_device != NULL && wParam != SIZE_MINIMIZED)
			{
				dx::d3d_param.BackBufferWidth = LOWORD(lParam);
				dx::d3d_param.BackBufferHeight = HIWORD(lParam);
				reset_device();
			}
			return 0;

		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
