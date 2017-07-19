// ImGui Win32 + DirectX11 binding
// https://github.com/ocornut/imgui

struct ID3D11Device;
struct ID3D11DeviceContext;

IMGUI_API bool        ImGui_ImplDX11_Init(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
IMGUI_API void        ImGui_ImplDX11_Shutdown();
IMGUI_API void        ImGui_ImplDX11_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplDX11_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_ImplDX11_CreateDeviceObjects();

// Handler for Win32 messages, update mouse/keyboard data.
// You may or not need this for your implementation, but it can serve as reference for handling inputs.
// Commented out to avoid dragging dependencies on <windows.h> types. You can copy the extern declaration in your code.
/*
IMGUI_API LRESULT   ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
*/
