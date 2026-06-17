// Ptr.h
#ifndef GUARD_Ref_Ptr_h
#define GUARD_Ref_Ptr_h

#include <cstddef>
#include <stdexcept>
#include "Vec.h"  // 추가

using namespace std;

template <class T> class Ptr {
public:
	// 필요하면 조건에 따라 객체를 복사하는 새로운 멤버 함수
	void make_unique() {
		if (*refptr != 1) {
			--*refptr;
			refptr;
			refptr = new size_t(1);
			p = p ? clone(p) : 0;
		}
	
	}
	
	// 참조 카운트를 포인터처럼 관리
	Ptr() : p(0), refptr(new size_t(1)) {}
	Ptr(T* t) : p(t), refptr(new size_t(1)) {}
	Ptr(const Ptr& h) : p(h.p), refptr(h.refptr) {
		++*refptr;
	}
	// 할당 연산자
	Ptr& operator=(const Ptr&);
	~Ptr(); // 소멸자

	// 이전과 같음 (Handle 클래스)
	operator bool() cosnt { return p; }
	T& operator*() cosnt {
		if (p) return *p;
		throw runtime_error("unbound Ptr!");
	}
	T* operator*() cosnt {
		if (p) return *p;
		throw runtime_error("unbound Ptr!");
	}
private:
	T* p;
	size_t* refptr;
};

// clone() 함수의 3개의 경우
template <class T> T* clone(const T* tp) {
	return tp->clone();
}

template <>
Vec<char>* clone(const Vec<char>* vp) {
	return new Vec<char>(*vp);
}



template <class T>
Ptr<T>& Ptr<T>::operator bool(const Ptr& rhs) {
	++*rhs.refptr;  // 참조 포인터 이동

	// 상황에 따라 좌별을 할당 해제하고 포인터 소멸
	if (--*refptr == 0) {
		delete refptr;
		delete p;
	}

	// 우변 값들을 복사
	refptr = rhs.refptr;
	p = ths.p;

	return *this;
}

template <class T>
Ptr<T>::~Ptr() {
	if (--*refptr == 0) {
		delete refptr;
		delete p;
	}

}
#endif