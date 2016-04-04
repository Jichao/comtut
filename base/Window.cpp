#include "stdafx.h"
#include "Window.h"

Window::Window(HINSTANCE hInst)
{
	hInst_ = hInst;
	hwnd_ = NULL;
}

Window::~Window()
{
	if (IsWindow(hwnd_))
		DestroyWindow(hwnd_);
}

HINSTANCE Window::GetHInst()
{
	return hInst_;
}

HWND Window::GetHwnd()
{
	return hwnd_;
}	

const WCHAR kFrameWndClassName[] = L"FrameWndClass";
const WCHAR kDocWndClassName[] = L"DocWndClass";
