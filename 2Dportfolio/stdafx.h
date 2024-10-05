#pragma once

#define NOMINMAX

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <Windows.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <iostream>
#include <fstream>
using namespace std;

//DirectX
#include <D3Dcompiler.h>
#include <D3D11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "DirectTex/DirectXTex.h"
#pragma comment (lib, "DirectTex/directxtex.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")

#pragma comment(lib,"FMod/fmodex_vc.lib")

// 자료형 이름 간략화
typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX Matrix;
typedef D3DXCOLOR Color;

#include "Utilities/Singleton.h"

#include "Systems/Graphics.h"

#include "Song.h"

#define DC Graphics::Get()->GetDC()
#define DEVICE Graphics::Get()->GetDevice()
#define JUDGEMENT Judgement::Get()

#define ASSERT(target) assert(SUCCEEDED(target));

#define SAFE_DELETE(target){if(target){delete (target); target = nullptr;}}
#define SAFE_DELETE_ARRAY(target){if(target){delete[] (target); target = nullptr;}}
#define SAFE_RELEASE(target){if(target){target->Release(); target = nullptr;}}

#define WinMaxWidth 1280
#define WinMaxHeight 720

#define Red Color(1, 0, 0, 1)		//빨강
#define Green Color(0, 1, 0, 1)		//초록
#define Blue Color(0, 0, 1, 1)		//파랑
#define Black Color(0, 0, 0, 1)		//검정
#define White Color(1, 1, 1, 1)		//하양
#define Yellow Color(1, 1, 0, 1)	//노랑
#define Magenta Color(1, 0, 1, 1)	//마젠타
#define Cyan Color(0, 1, 1, 1)		//청록

extern HWND handle;

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/Resources/VertexType.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"
#include "Renders/Resources/ConstBuffer.h"
#include "Renders/Resources/ViewFactory.h"
#include "Renders/Resources/Texture2D.h"

#include "Systems/Time.h"
#include "Systems/Mouse.h"
#include "Systems/Keyboard.h"
#include "Systems/GUI/Gui.h"
#include "Systems/Camera.h"

#include "Utilities/Math.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/Animator.h"
#include "Utilities/FileStream.h"
#include "Utilities/Judgement.h"
#include "Utilities/Setting.h"

#include "Scene/Scene.h"