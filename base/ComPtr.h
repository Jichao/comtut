#pragma once

template <typename T>
class ComPtr 
{
public:
	ComPtr() {
		pt_ = nullptr;
	}
	ComPtr(T* t) {
		if (t) {
			pt_ = t;
		}
	}
	ComPtr<T>& operator=(ComPtr<T>& other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = other.pt_;
		if (pt_) {
			pt_->AddRef();
		}
		return *this;
	}
	ComPtr<T>& operator=(T* other) {
		if (pt_) {
			pt_->Release();
		}
		pt_ = other;
		if (pt_) {
			pt_->AddRef();
		}
		return *this;
	}
	~ComPtr() {
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
private:
	T* pt_;
};