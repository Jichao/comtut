#pragma once

template <typename T>
class ComPtr 
{
	template <typename U> friend class ComQIPtr;
public:
	ComPtr() {
		pt_ = nullptr;
	}
	ComPtr(T* t) {
		if (t) {
			pt_ = t;
			pt_->AddRef();
		}
	}
	ComPtr(const ComPtr<T>& other) {
		pt_ = other.pt_;
		if (pt_) {
			pt_->AddRef();
		}
	}
	ComPtr<T>& operator=(ComPtr<T>& other) {
		if (other.pt_ == pt_)
			return *this;
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
		if (other == pt_)
			return *this;
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
	void CopyTo(T** other) {
		if (other) {
			*other = pt_;
			pt_->AddRef();
		}
	}
private:
	T* pt_;
};