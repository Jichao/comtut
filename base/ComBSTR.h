#pragma once

#include <string>

class ComBSTR
{
public:
	ComBSTR() {
		bstr_ = nullptr;
	}

	ComBSTR(BSTR t) {
		if (t) {
			bstr_ = SysAllocString(t);
		}
	}

	ComBSTR(const std::wstring& str) {
		bstr_ = SysAllocString(str.c_str());
	}

	ComBSTR& operator=(const std::wstring& str) {
		bstr_ = SysAllocString(str.c_str());
		return *this;
	}

	ComBSTR& operator=(ComBSTR& other) {
		if (bstr_) {
			SysFreeString(bstr_);
			bstr_ = nullptr;
		}
		if (other.bstr_) {
			bstr_ = SysAllocString(other.bstr_);
		}
		return *this;
	}

	ComBSTR& operator=(BSTR other) {
		if (bstr_) {
			SysFreeString(bstr_);
			bstr_ = nullptr;
		}
		if (other) {
			bstr_ = SysAllocString(other);
		}
		return *this;
	}

	~ComBSTR() {
		if (bstr_) {
			SysFreeString(bstr_);
		}
	}

	int Length() {
		if (!bstr_)
			return 0;
		return SysStringLen(bstr_);
	}

	BSTR Clone() {
		if (!bstr_)
			return nullptr;
		return SysAllocString(bstr_);
	}

	void CopyTo(BSTR* out) {
		*out = Clone();
	}

	void Clear() {
		if (bstr_) {
			SysFreeString(bstr_);
			bstr_ = NULL;
		}
	}

	operator BSTR() {
		return bstr_;
	}
	operator bool() {
		return !!bstr_;
	}
	BSTR* operator &() {
		return &bstr_;
	}

	HRESULT writeToStream(IStream* stream) {
		int count = Length();
		auto hr = stream->Write(&count, 4, 0);
		if (FAILED(hr))
			return hr;
		if (count) {
			return stream->Write(bstr_, Length() * 2, 0);
		}
		return S_OK;
	}

	HRESULT readFromStream(IStream* stream) {
		int count;
		auto hr = stream->Read(&count, 4, 0);
		if (FAILED(hr))
			return hr;
		if (bstr_) {
			SysFreeString(bstr_);
		}
		if (!count) {
			bstr_ = SysAllocString(L"");
		} else {
			WCHAR* buff = new WCHAR[count];
			auto hr = stream->Read(buff, count * 2, 0);
			if (FAILED(hr))
				return hr;
			bstr_ = SysAllocStringLen(buff, count);
		}
		return S_OK;
	}	
	bool operator==(LPCWSTR other) {
		return wcscmp(bstr_, other) == 0;
	}
private:
	BSTR bstr_;
};