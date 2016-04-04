#include "stdafx.h"
#include "ClientWnd.h"
#include "FrameWnd.h"

static const int kIdFirst = 100;

ClientWnd::ClientWnd(HINSTANCE hInst)
	: Window(hInst_)
{
	frameWnd_ = NULL;
}


ClientWnd::~ClientWnd()
{
}

bool ClientWnd::Init(FrameWnd* frameWnd)
{
	frameWnd_ = frameWnd;
	CLIENTCREATESTRUCT cs;
	cs.hWindowMenu = frameWnd->GetWindowMenu();
	cs.idFirstChild = kIdFirst;
	RECT rc;
	GetClientRect(frameWnd->GetHwnd(), &rc);
	hwnd_ = CreateWindowEx(NULL, L"MDICLIENT", NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL, CW_USEDEFAULT,
		CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, frameWnd->GetHwnd(), NULL, hInst_, (LPVOID)&cs);
	if (!hwnd_)
		return false;
	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);
	return true;
}

FrameWnd* ClientWnd::GetFrameWnd()
{
	return frameWnd_;
}
