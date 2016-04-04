#pragma once
#include <OleAuto.h>
class OleUtils
{
public:
	OleUtils();
	~OleUtils();
	static HRESULT SaveToStream(IPersistStreamInit* init, IStream* stream);
};

