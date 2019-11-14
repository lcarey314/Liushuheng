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
	Str str = "liu";
	str.append("shu");
	cout << str.compare("liushu");
	
}