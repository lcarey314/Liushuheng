/******************************************************
File name: main.cpp
Author: Liushuheng
Date: 2019/11/10
Des:
******************************************************/
#include <iostream>
#include "Str.h"
#include <string>
using namespace std;

int main() {
	Str str = "abc";
	cout << str.length()<<"append test" << '\n';
	str.append("ssss");
	cout << str.data() << str.size()<<"insert test"<<'\n';
	str.insert(3, "ins");
	cout << str.data();
	UINT a = str.find("ss");  //abcinsssss  5
	cout << '\n'<<a;
    UINT b = str.rfind("ss");  //9
	cout << '\n'<<b<<'\n';
	str.clear();
	cout << str.length();

}