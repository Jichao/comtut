#include "stdafx.h"
#include "DocWnd.h"

DocWnd::DocWnd(HINSTANCE hInst)
	: Window(hInst)
{
}

DocWnd::~DocWnd()
{
}

bool DocWnd::Init(ClientWnd* clientWnd)
{
	clientWnd_ = clientWnd;
	hwnd_ = CreateWindowEx(WS_EX_MDICHILD, kDocWndClassName, L"kekeke", MDIS_ALLCHILDSTYLES, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		clientWnd->GetHwnd(), 0, hInst_, this);
	if (!hwnd_)
		return false;
	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);
	return true;
}

LRESULT CALLBACK DocWnd::DocWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DocWnd* wnd = NULL;
	if (message == WM_CREATE) {
		wnd = reinterpret_cast<DocWnd*>(((LPMDICREATESTRUCT)((LPCREATESTRUCT)lParam)->lpCreateParams)->lParam);
		wnd->hwnd_ = hWnd;
	} else {
		wnd = reinterpret_cast<DocWnd*>(GetWindowLong(hWnd, GWL_USERDATA));
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
			return DefMDIChildProc(hWnd, message, wParam, lParam);
		}
	} else {
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
}

bool DocWnd::MessageHook(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr)
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
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd_, &ps);
		RECT rc;
		GetClientRect(hwnd_, &rc);
		auto hr = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
		FillRect(hdc, &rc, hr);
		EndPaint(hwnd_, &ps);
		break;
	}
	}
	return false;
}

void DocWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{

}
