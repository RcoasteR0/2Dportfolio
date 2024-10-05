#include "stdafx.h"
#include "Gui.h"

Gui* Gui::instance = nullptr;

///////////싱글턴///////////
void Gui::Create()
{
	assert(instance == nullptr);

	instance = new Gui();
}

void Gui::Delete()
{
	SAFE_DELETE(instance);
}

Gui * Gui::Get()
{
	return instance;
}
///////////////////////////

LRESULT Gui::MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_Proc(handle, message, wParam, lParam);
}

void Gui::Resize()
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();
}

//fps출력
void Gui::PrintFrame()
{
	bool temp = true;
	ImGui::SetNextWindowPos({ WinMaxWidth - 150, 0 });	//우상단
	if (ImGui::Begin("FrameRate", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))	//배경, 타이틀바, 크기변경 없이
	{
		string frameStr = "Frame Rate : " + to_string((int)ImGui::GetIO().Framerate);	//Frame Rate : (현재 fps 값) 
		ImGui::TextColored(ImVec4(1, 1, 1, 1), frameStr.c_str());
	}
	ImGui::End();
}

void Gui::TextureRectGUIS(vector<class TextureRect*>& trVec, const char * name)
{
	if (trVec.size() <= 0) return;

	bool temp = true;
	if (ImGui::Begin(name), &temp)
	{
		for (UINT i = 0; i < trVec.size(); i++)
			trVec[i]->GUI(i);
	}
	ImGui::End();
}

//업데이트
void Gui::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

//랜더링
void Gui::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

//생성자
Gui::Gui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplWin32_Init(handle);
	ImGui_ImplDX11_Init(DEVICE, DC);

	ApplyStyle();
}

//소멸자
Gui::~Gui()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//GUI 스타일 설정
void Gui::ApplyStyle()
{
	ImGui::GetIO().ConfigWindowsResizeFromEdges = true;
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	float fontSize = 15.0f;
	float roundness = 2.0f;
	ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 text = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
	ImVec4 black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 backgroundVeryDark = ImVec4(0.08f, 0.086f, 0.094f, 1.0f);
	ImVec4 backgroundDark = ImVec4(0.117f, 0.121f, 0.145f, 1.0f);
	ImVec4 backgroundMedium = ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
	ImVec4 backgroundLight = ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
	ImVec4 highlightBlue = ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
	ImVec4 highlightBlueHovered = ImVec4(0.202f, 0.269f, 0.391f, 1.0f);
	ImVec4 highlightBlueActive = ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
	ImVec4 barBackground = ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
	ImVec4 bar = ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
	ImVec4 barHovered = ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
	ImVec4 barActive = ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.FramePadding = ImVec2(5, 5);
	style.ItemSpacing = ImVec2(6, 5);
	style.Alpha = 1.0f;
	style.WindowRounding = roundness;
	style.FrameRounding = roundness;
	style.PopupRounding = roundness;
	style.GrabRounding = roundness;
	style.ScrollbarSize = 20.0f;
	style.ScrollbarRounding = roundness;

	style.Colors[ImGuiCol_Text] = text;
	style.Colors[ImGuiCol_WindowBg] = backgroundDark;
	style.Colors[ImGuiCol_Border] = black;
	style.Colors[ImGuiCol_FrameBg] = bar;
	style.Colors[ImGuiCol_FrameBgHovered] = highlightBlue;
	style.Colors[ImGuiCol_FrameBgActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_TitleBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_TitleBgActive] = bar;
	style.Colors[ImGuiCol_MenuBarBg] = barBackground;
	style.Colors[ImGuiCol_ScrollbarBg] = barBackground;
	style.Colors[ImGuiCol_ScrollbarGrab] = bar;
	style.Colors[ImGuiCol_CheckMark] = white;
	style.Colors[ImGuiCol_SliderGrab] = bar;
	style.Colors[ImGuiCol_SliderGrabActive] = barActive;
	style.Colors[ImGuiCol_Button] = barActive;
	style.Colors[ImGuiCol_ButtonHovered] = highlightBlueActive;
	style.Colors[ImGuiCol_ButtonActive] = highlightBlue;
	style.Colors[ImGuiCol_Header] = highlightBlue;
	style.Colors[ImGuiCol_HeaderHovered] = highlightBlueHovered;
	style.Colors[ImGuiCol_HeaderActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Separator] = backgroundLight;
	style.Colors[ImGuiCol_ResizeGrip] = backgroundMedium;
	style.Colors[ImGuiCol_ResizeGripHovered] = highlightBlue;
	style.Colors[ImGuiCol_ResizeGripActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = highlightBlue;
	style.Colors[ImGuiCol_PlotHistogramHovered] = highlightBlueHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = highlightBlue;
	style.Colors[ImGuiCol_PopupBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_DragDropTarget] = backgroundLight;
}
