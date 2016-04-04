#pragma once

template <typename T>
class ComQIPtr
{
public:
	ComQIPtr() {
		pt_ = nullptr;
	}
	ComQIPtr(T* t) {
		if (t) {
			pt_ = t;
			t->AddRef();
		}
	}
	template <typename O>
	ComQIPtr(O* other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = nullptr;
		if (other) {
			T* t = nullptr;
			other->QueryInterface(__uuidof(T), (void**)&t);
			pt_ = t;
		}
	}

	template <typename O>
	ComQIPtr(ComPtr<O>& other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = nullptr;
		if (other.pt_) {
			T* t = nullptr;
			other.pt_->QueryInterface(__uuidof(T), (void**)&t);
			pt_ = t;
		}
	}

	ComQIPtr<T>& operator=(ComQIPtr<T>& other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = other.pt_;
		if (pt_) {
			pt_->AddRef();
		}
		return *this;
	}
	template <typename O>
	ComQIPtr<T>& operator=(ComPtr<O>& other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = nullptr;
		if (other.pt_) {
			T* t = nullptr;
			other.pt_->QueryInterface(__uuidof(T), (void**)&t);
			pt_ = t;
		}
		return *this;
	}
	ComQIPtr<T>& operator=(T* other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = other;
		if (pt_) {
			pt_->AddRef();
		}
		return *this;
	}
	template <typename O>
	ComQIPtr<T>& operator=(O* other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = nullptr;
		if (other) {
			T* t = nullptr;
			other->QueryInterface(__uuidof(T), (void**)&t);
			pt_ = t;
		}
		return *this;
	}

	~ComQIPtr() {
		if (pt_) {
			pt_->Release();
		}
	}
	operator T*() {
		return pt_;
	}
	operator bool() {
		return !!pt_;
	}
	T** operator &() {
		return &pt_;
	}
	T* operator ->() {
		return pt_;
	}
	void CopyTo(T** other) {
		if (other) {
			*other = pt_;
			pt_->AddRef();
		}
	}
private:
	T* pt_;
};