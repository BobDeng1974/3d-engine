#ifndef UGINE_SMARTPTR_H
#define UGINE_SMARTPTR_H

template<typename T> class WPtr;

class RC {
public:
	RC() : count(0) {}
	void Inc() { count++; }
	unsigned long Dec() { return --count; }
private:
	unsigned long count;
};

template<typename T>
class Ptr {
public:
	Ptr()									: data(0), ref(0) { ref = new RC(); ref->Inc(); }
	Ptr(T* p)								: data(p), ref(0) { ref = new RC(); ref->Inc(); }
	Ptr(T* p, RC* r)						: data(p), ref(r) { ref->Inc(); }
	Ptr(const Ptr<T>& p)					: data(p.data), ref(p.ref) { ref->Inc(); }
	Ptr(const WPtr<T>& p);
	~Ptr()									{ if ( ref->Dec() == 0 ) { delete data; delete ref; } }
	T& operator*() const					{ return *data; }
	T* operator->() const					{ return data; }
	Ptr<T>& operator=(const Ptr<T>& p)		{ if ( *this != p ) { if ( ref->Dec() == 0 ) { delete data; delete ref; } data = p.data; ref = p.ref; ref->Inc(); } return *this; }
	bool operator==(const Ptr<T>& p) const	{ return this->data == p.data; }
	bool operator!=(const Ptr<T>& p) const	{ return this->data != p.data; }
	bool operator==(const T* const p) const	{ return this->data == p; }
	bool operator!=(const T* const p) const	{ return this->data != p; }
	
	template <typename Y> Ptr<Y> UpCast();
	template <typename Y> Ptr<Y> DownCast();
	Ptr<const T> ConstCast() const { return Ptr<const T>(data, ref); }
private:
	T* data;
	RC* ref;

	friend class WPtr<T>;
};

template<typename T>
class WPtr {
public:
	WPtr()										: data(0), ref(0) {}
	WPtr(T* p)									: data(p), ref(0) {}
	WPtr(T* p, RC* r)							: data(p), ref(r) {}
	WPtr(const WPtr<T>& p)					: data(p.data), ref(p.ref) {}
	WPtr(const Ptr<T>& p)					: data(p.data), ref(p.ref) {}
	T& operator*() const						{ return *data; }
	T* operator->() const						{ return data; }
	WPtr<T>& operator=(const WPtr<T>& p)		{ data = p.data; ref = p.ref; return *this; }
	bool operator==(const WPtr<T>& p) const		{ return this->data == p.data; }
	bool operator!=(const WPtr<T>& p) const		{ return this->data != p.data; }
	bool operator==(const T* const p) const			{ return this->data == p; }
	bool operator!=(const T* const p) const			{ return this->data != p; }
	
	template <typename Y> WPtr<Y> UpCast();
	template <typename Y> WPtr<Y> DownCast();
	WPtr<const T> ConstCast() const { return WPtr<const T>(data, ref); }
private:
	T* data;
	RC* ref;

	friend class Ptr<T>;
};

template <typename T>
Ptr<T>::Ptr(const WPtr<T>& p) : data(p.data), ref(p.ref) {
	if ( !ref ) ref = new RC();
	ref->Inc();
}

template <typename T>
template <typename Y>
Ptr<Y> Ptr<T>::UpCast() {
	if ( static_cast<Y*>(data) )
		return Ptr<Y>(data, ref);
	else
		return Ptr<Y>();
}

template <typename T>
template <typename Y>
Ptr<Y> Ptr<T>::DownCast() {
	if ( dynamic_cast<Y*>(data) )
		return Ptr<Y>((Y*)data, ref);
	else
		return Ptr<Y>();
}

template <typename T>
template <typename Y>
WPtr<Y> WPtr<T>::UpCast() {
	if ( static_cast<Y*>(data) )
		return WPtr<Y>(data, ref);
	else
		return WPtr<Y>();
}

template <typename T>
template <typename Y>
WPtr<Y> WPtr<T>::DownCast() {
	if ( dynamic_cast<Y*>(data) )
		return WPtr<Y>((Y*)data, ref);
	else
		return WPtr<Y>();
}

#endif // UGINE_SMARTPTR_H