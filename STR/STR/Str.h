#pragma once

/******************************************************
File name: Str.h
Author: Liushuheng
Date: 2019/11/3
Des: 
******************************************************/
#include <set>

typedef unsigned int UINT;
static const UINT npos = -1;

class Str
{
public:
	Str();
	Str(const char* str);
	Str(const Str& str);
	Str(const Str& str, UINT pos, UINT length = npos);
	Str(const char* s, UINT n);
	~Str();

	Str& append(const Str& str);
	Str& assign(const Str& str);
	Str& erase(UINT pos = 0,UINT length = npos);
	Str& insert(UINT pos, const Str& str);
	Str& operator+=(const Str& str);
	Str& operator=(const Str& str);
	Str& replace(UINT pos, UINT length, const Str& str);

	char& at(UINT pos);
	char& back();
	char& front();
	char& operator[](UINT pos);
	
	UINT length()const;
	UINT size()const;
	UINT capacity()const noexcept;
	UINT compare(const Str& str)const noexcept;
	UINT copy(char* s, UINT length, UINT pos = 0)const;
	UINT find(const Str& str, UINT pos = 0)const noexcept;
	UINT rfind(const Str& str, UINT pos = npos)const;

	const char* c_str()const noexcept;
	const char* data()const noexcept;

	bool empty()const noexcept;

	Str substr(UINT pos = 0, UINT length = npos)const;

	void popback();
	void resize(UINT n);
	void pushback(char c);
	void reserve(UINT n = 0);
	void shrink_to_fit();
	void clear()noexcept;
private:

	static std::set<char*> setMem;
	static const UINT InitMemSize;    
	static const UINT NewAllocSize;    

	void _recap();
	void _Alloc(UINT size);
	void _Free();

	char* val;
	UINT len;
	UINT cap;
};

