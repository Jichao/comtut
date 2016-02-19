#pragma once

class GdiplusStarter
{
public:
	GdiplusStarter();
	~GdiplusStarter();

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

