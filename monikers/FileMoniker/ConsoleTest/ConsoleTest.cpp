// ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../GuiClient/PolylineTest.h"
#include "../GuiClient/BookServerTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	{
		//PolylineTest tester;
		//tester.testCompoundFile();
		//tester.writePersistFile();
		//tester.readPersistFile();
		//tester.writeFileMoniker();
		//tester.readFileMoniker();
	}

	{
		BookServerTest booktest;
		booktest.testWord();
		//booktest.createBook();
		//booktest.readBook();
		//booktest.createFileMoniker();
		//booktest.readFileMoniker();
		//booktest.readItemMoniker();
	}
	return 0;
}

