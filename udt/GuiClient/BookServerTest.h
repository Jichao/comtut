#pragma once
#include "base/ComPtr.h"

class BookServerTest
{
public:
	BookServerTest();
	~BookServerTest();
	int createBook();
	int readBook();
	int createFileMoniker();
	int readFileMoniker();
	//int createItemMoniker();
	int readItemMoniker();
	void testWord();

private:
};
