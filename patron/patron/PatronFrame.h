#pragma once

#include "base/FrameWnd.h"

class PatronFrame : public FrameWnd
{
public:
	PatronFrame(HINSTANCE hInst);
	~PatronFrame();
	virtual bool MessageHook(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr);
	virtual void OnCommand(WPARAM wParam, LPARAM lParam);
	bool Init();
	bool NewDoc();
};
