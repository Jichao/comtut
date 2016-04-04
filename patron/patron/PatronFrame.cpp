#include "stdafx.h"
#include "Resource.h"
#include "PatronFrame.h"
#include "base/DocWnd.h"

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


PatronFrame::PatronFrame(HINSTANCE hInst)
	: FrameWnd(hInst)
{
}

PatronFrame::~PatronFrame()
{
}

bool PatronFrame::Init()
{
	FrameWndInit init;
	init.iconId = IDI_PATRON;
	init.menuId = IDC_PATRON;
	init.wndMenuIndex = 1;
	init.accId = IDC_PATRON;
	init.title = L"Patron";
	if (!__super::Init(init))
		return false;
	if (!NewDoc())
		return false;
	return true;
}

bool PatronFrame::NewDoc()
{
	DocWnd* docWnd = new DocWnd(hInst_);
	if (!docWnd) {
		return false;
	}
	return docWnd->Init(clientWnd_);
}

bool PatronFrame::MessageHook(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* lr)
{
	if (__super::MessageHook(message, wParam, lParam, lr))
		return true;
	return false;
}

void PatronFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	auto wmId = LOWORD(wParam);
	auto wmEvent = HIWORD(wParam);
	// Parse the menu selections:
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst_, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd_, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hwnd_);
		break;
	case ID_FILE_NEW:
		NewDoc();
		break;
	}
}
