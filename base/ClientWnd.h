#pragma once

#include "Window.h"
class FrameWnd;

class ClientWnd : public Window
{
public:
	ClientWnd(HINSTANCE hInst);
	~ClientWnd();
	bool Init(FrameWnd* frameWnd);
	FrameWnd* GetFrameWnd();

private:
	FrameWnd* frameWnd_;
};

