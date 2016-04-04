#pragma once

#include "Window.h"
#include "ClientWnd.h"

class DocWnd : public Window
{
public:
	DocWnd(HINSTANCE hInst);
	virtual ~DocWnd();

	bool Init(ClientWnd* clientWnd);
	static LRESULT CALLBACK DocWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual bool MessageHook(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr);

private:
	virtual void OnCommand(WPARAM wParam, LPARAM lParam);
	ClientWnd* clientWnd_;
};