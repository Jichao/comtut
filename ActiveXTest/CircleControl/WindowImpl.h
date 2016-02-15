#pragma once
class WindowImpl
{
public:
	WindowImpl();
	~WindowImpl();
	static bool registerClass(HINSTANCE hInst);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static HWND GetWindow();
private:
	static HINSTANCE hInst_;
};

