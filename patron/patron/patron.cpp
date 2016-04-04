// patron.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "patron.h"
#include "PatronFrame.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	PatronFrame frame(hInstance);
	if (!frame.Init())
		return -1;
	frame.MsgLoop();
	return 0;
}



