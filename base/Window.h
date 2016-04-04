#pragma once

extern const WCHAR kFrameWndClassName[];
extern const WCHAR kDocWndClassName[];

class Window
{
public:
	Window(HINSTANCE hInst);
	virtual ~Window();

	HINSTANCE GetHInst();
	HWND GetHwnd();

protected:
	HINSTANCE hInst_;
	HWND hwnd_;
};

