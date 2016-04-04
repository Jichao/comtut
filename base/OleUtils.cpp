#include "stdafx.h"
#include <ocidl.h>
#include "OleUtils.h"


OleUtils::OleUtils()
{
}


OleUtils::~OleUtils()
{
}

HRESULT OleUtils::SaveToStream(IPersistStreamInit* init, IStream* stream)
{
	if (!init || !stream)
		return E_POINTER;
	CLSID clsid;
	auto hr = init->GetClassID(&clsid);
	if (FAILED(hr))
		return hr;
	hr = WriteClassStm(stream, clsid);
	if (FAILED(hr))
		return hr;
	return init->Save(stream, TRUE);
}
