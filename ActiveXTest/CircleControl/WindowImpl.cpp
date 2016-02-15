#include "stdafx.h"
#include "WindowImpl.h"

TCHAR szWindowClass[] = L"keke";			// the main window class name
HINSTANCE WindowImpl::hInst_;

WindowImpl::WindowImpl()
{
}


WindowImpl::~WindowImpl()
{
}

bool WindowImpl::registerClass(HINSTANCE hInstance)
{
	hInst_ = hInstance;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst_;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = szWindowClass;
	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK WindowImpl::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND WindowImpl::GetWindow()
{
	return CreateWindow(szWindowClass, L"", WS_CHILD,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst_, NULL);
}

