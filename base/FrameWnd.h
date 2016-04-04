#pragma once 
#include "Window.h"

class ClientWnd;
class DocWnd;

struct FrameWndInit {
	INT iconId;
	INT menuId;
	INT wndMenuIndex;
	INT accId;
	std::wstring title;
};

class FrameWnd : public Window
{
public:
	FrameWnd(HINSTANCE hInst);
	virtual ~FrameWnd();
	bool Init(const FrameWndInit& init);
	virtual bool MessageHook(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr);
	HMENU GetWindowMenu();
	void MsgLoop();

protected:
	virtual void OnCommand(WPARAM wParam, LPARAM lParam);
	bool registerAllClasses(INT iconId, INT menuId);
	static LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	ClientWnd* clientWnd_;
	std::vector<DocWnd*> docs_;
	FrameWndInit init_;
};

