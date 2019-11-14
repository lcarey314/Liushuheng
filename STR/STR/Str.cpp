/**************************************************************
File name: Str.h
Author: Liushuheng
Date: 2019/11/3
Des:
**************************************************************/
#include "Str.h"
#include<stdexcept>

std::set<char*> Str::setMem;
const UINT Str::InitMemSize = 16;     //初始capacity设置为16
const UINT Str::NewAllocSize = 16;     //超过16每次申请16

/***********************  private函数实现begin  **************/
void Str::_Alloc(UINT size) {
	val = new char[size];
	setMem.insert(val);
}

void Str::_Free() {
	setMem.erase(val);
}

// 保留原字符串内容，扩大capacity
void Str::_recap() {
	Str oldStr = Str(*this);
	_Free();
	_Alloc(cap);
	memcpy(val, oldStr.val, len);
}

/***********************  private函数实现end  *****************/
/***********************  构造函数实现begin  ******************/
Str::Str() {
	val = new char[InitMemSize];
	val[0] = '\0';
	len = 0;
	// 最后一个空字符不算入capacity
	cap = InitMemSize - 1;  
}

Str::Str(const char* str) {
	len = strlen(str);
	cap = NewAllocSize * (len / NewAllocSize + 1);
	_Alloc(cap);
	strcpy_s(val, cap, str);
	val[len] = '\0';
}

Str::Str(const Str& str) {
	len = str.len;
	cap = NewAllocSize * (len / NewAllocSize + 1);
    _Alloc(cap);
	memcpy_s(val, len, str.val, len);
	val[len] = '\0';
}

Str::Str(const Str& str, UINT pos, UINT length) {
	if (pos + length > str.len) {
		len = str.len - pos;
	}
	else {
		len = length;
	}

	cap = NewAllocSize * (len / NewAllocSize + 1);
	_Alloc(cap);
	memcpy_s(val, len, str.val + pos, len);
	val[len] = '\0';
}

Str::Str(const char* s, UINT n) {
	if (n > strlen(s)) {
		len = strlen(s);
	}
	else {
		len = n;
	}
	cap = NewAllocSize * (len / NewAllocSize + 1);
	_Alloc(cap);
	memcpy_s(val, len, s, len);
	val[len] = '\0';
}

/***********************  构造函数实现end  **********************/
/***********************  public成员函数实现begin  **************/
UINT Str::length()const {
	return len;
}

UINT Str::size()const {
	return len;
}

UINT Str::capacity()const noexcept {
	return cap;
}

UINT Str::compare(const Str& str)const noexcept {
	return (UINT)strcmp(val, str.val);
}

UINT Str::copy(char* s, UINT length, UINT pos)const {
	if (length + pos > len) {
		memcpy_s(s, len - pos, val + pos, len - pos);
		return len - pos;
	}
	else {
		memcpy_s(s, len, val + pos, len);
		return length;
	}
}

Str Str::substr(UINT pos, UINT length)const {
	return Str(*this, pos, length);
}

UINT Str::find(const Str& str, UINT pos)const noexcept {
	if (str.len > (len - pos)) {
		return npos;
	}
	UINT searchLen = len - str.len;
	for (UINT i = pos; i <= len - str.len; i++) {
		if (str.compare(this->substr(i, str.len)) == 0) {
			return i;
		}
	}
	return npos;
}

UINT Str::rfind(const Str& str, UINT pos)const {
	if (pos == npos) {
		pos = len - 1;
	}
	for (UINT i = pos; i >= str.len; i--) {
		if (str.compare(this->substr(i - str.len, str.len)) == 0) {
			return i;
		}
	}
	return npos;
}

char& Str::at(UINT pos) {
	if (pos >= len) {
		throw std::out_of_range("laobifeng");
	}
	return *(val + pos);
}
char& Str::back() {
	return *(val + (len - 1));
}

char& Str::front() {
	return *(val);
}

char& Str::operator[](UINT pos) {
	if (pos >= len) {
		throw std::out_of_range("laobifeng");
	}
	return *(val + pos);
}

void Str::resize(UINT n) {
	if (n > cap) {
		cap = NewAllocSize * (len / NewAllocSize + 1);
		_recap();
	}
	else {
	    val[n] = '\0';
	}
	len = n;
}

void Str::popback() {
	val[len - 1] = '\0';
	len = len - 1;
}

void Str::pushback(char c) {
	len = len + 1;
	if (len > cap) {
		cap = NewAllocSize * (len / NewAllocSize + 1);
		_recap();
	}
	else {
		val[len - 1] = c;
		val[len] = '\0';
	}
}

void Str::reserve(UINT n) {
	if (cap < n) {
		while (n > cap) {
			cap = cap + NewAllocSize;
		}
		_recap();
	}
}
void Str::shrink_to_fit() {
	cap = len;
	_recap();
}
void Str::clear()noexcept {
	len = 0;
	val[len] = '\0';
}

const char* Str::c_str()const noexcept {
	return val;
}

const char* Str::data()const noexcept {
	return val;
}

bool Str::empty()const noexcept {
	if (len == 0) {
		return true;
	}
	return false;
}

Str& Str::append(const Str& str) {
	len = len + str.len;
	if (len > cap) {
		cap = NewAllocSize * (len / NewAllocSize + 1);
		_recap();
	}
	memcpy(val + (len - str.len), str.val, str.len);
	val[len] = '\0';
	return *this;
}

Str& Str::assign(const Str& str) {
	len = str.len;
	cap = str.cap;
	_Free();
	_Alloc(cap);
	memcpy(val, str.val, len);
	val[len] = '\0';
	return *this;
}

Str& Str::erase(UINT pos, UINT length) {
	if (pos >= len) {
		throw std::out_of_range("laobifeng");
	}
	// >= len时pos后面全部置空
	if (pos + length >= len) {
		len = pos;
		val[len] = '\0';
	}
	//将需要置空后面位置字符前移length
	for (; pos + length < len; pos++) {
		val[pos] = val[pos + length];
	}

	len = len - length;
	val[len] = '\0';
	return *this;
}

Str& Str::insert(UINT pos, const Str& str) {
	if (pos >= len) {
		throw std::out_of_range("laobifeng");
	}
	len = len + str.len;
	if (len >= cap) {
		cap = NewAllocSize * (len / NewAllocSize + 1);
		_recap();
	}

	//插入位置后面的 len - pos 个字符后移 str.len
	for (UINT i = 0; i < len - pos; i++) {     
		val[pos + i + str.len] = val[pos + i];
	}
	//插入 str
	for (UINT i = 0; i < str.len; i++) {
		val[pos + i] = str.val[i];
	}
	val[len] = '\0';
	return *this;
}

Str& Str::operator+=(const Str& str) {
	return append(str);
}

Str& Str::operator=(const Str& str) {
	return assign(str);
}

Str& Str::replace(UINT pos, UINT length, const Str& str) {
	UINT cpyLen = length <= (len - pos) ? length: (len - pos);
	memcpy(val + pos, str.val, cpyLen);
	return *this;
}

Str::~Str() {
	_Free();
}

/***********************  public成员函数实现end  **************/


