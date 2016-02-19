#include "stdafx.h"
#include "GdiplusStarter.h"

using namespace Gdiplus;
GdiplusStarter::GdiplusStarter()
{
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

GdiplusStarter::~GdiplusStarter()
{
	GdiplusShutdown(gdiplusToken);
}
