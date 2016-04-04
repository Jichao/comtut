#include "stdafx.h"
#include "ClientWnd.h"
#include "FrameWnd.h"
#include "DocWnd.h"

FrameWnd::FrameWnd(HINSTANCE hInst)
	: Window(hInst)
{
	clientWnd_ = NULL;
}

FrameWnd::~FrameWnd()
{
}

bool FrameWnd::registerAllClasses(INT iconId, INT menuId)
{
	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = FrameWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst_;
	wcex.hIcon = LoadIcon(hInst_, MAKEINTRESOURCE(iconId));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(menuId);
	wcex.lpszClassName = kFrameWndClassName;
	if (!RegisterClassEx(&wcex))
		return false;

	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = kDocWndClassName;
	wcex.lpfnWndProc = DocWnd::DocWndProc;
	if (!RegisterClassEx(&wcex))
		return false;
	return true;
}

bool FrameWnd::Init(const FrameWndInit& init)
{
	init_ = init;
	if (!registerAllClasses(init.iconId, init.menuId))
		return false;
	auto menu = LoadMenu(hInst_, MAKEINTRESOURCE(init_.menuId));
	hwnd_ = CreateWindowEx(NULL, kFrameWndClassName, init.title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, menu, hInst_, this);
	if (!hwnd_)
		return false;
	clientWnd_ = new ClientWnd(hInst_);
	if (!clientWnd_->Init(this))
		return false;
	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);
	return true;
}

LRESULT CALLBACK FrameWnd::FrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	FrameWnd* wnd = NULL;
	if (message == WM_CREATE) {
		wnd = reinterpret_cast<FrameWnd*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
		wnd->hwnd_ = hWnd;
	} else {
		wnd = reinterpret_cast<FrameWnd*>(GetWindowLong(hWnd, GWL_USERDATA));
	}
	if (wnd) {
		LRESULT lr;
		if (wnd->MessageHook(message, wParam, lParam, &lr)) {
			return lr;
		} else {
			HWND hClient = NULL;
			if (wnd->clientWnd_) {
				hClient = wnd->clientWnd_->GetHwnd();
			}
			return DefFrameProc(hWnd, hClient, message, wParam, lParam);
		}
	} else {
		return DefFrameProc(hWnd, NULL, message, wParam, lParam);
	}
}

bool FrameWnd::MessageHook(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr)
{
	switch (message) {
	case WM_CREATE:
	{
		*lr = 1;
		SetWindowLong(hwnd_, GWL_USERDATA, (LONG)this);
		return true;
	}
	case WM_COMMAND:
	{
		OnCommand(wParam, lParam);
		break;
	}
	case WM_DESTROY:
		*lr = 0;
		PostQuitMessage(0);
		return TRUE;
	}
	return false;
}

void FrameWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{

}

HMENU FrameWnd::GetWindowMenu()
{
	//HMENU hmenu = LoadMenu(hInst_, MAKEINTRESOURCE(init_.menuId));
	HMENU hMenu = GetMenu(hwnd_);
	auto hWndMenu = GetSubMenu(hMenu, init_.wndMenuIndex);
	return hWndMenu;
}

void FrameWnd::MsgLoop()
{
	MSG msg;
	BOOL bRet;
	auto hAccel = LoadAccelerators(hInst_, MAKEINTRESOURCE(init_.accId));
	while ((bRet = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0) {
			if (!TranslateMDISysAccel(clientWnd_->GetHwnd(), &msg) &&
				!TranslateAccelerator(hwnd_, hAccel, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
	}
	return;
}
