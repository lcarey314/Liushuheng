/******************************************************
File name: test.cpp
Author: Liushuheng
Date: 2019/11/15
Des: Str¿‡≤‚ ‘Œƒº˛
******************************************************/

#include "pch.h"
#include "../Str.h"
TEST(STR_TEST, StrBasicTest_1) {
	Str str = "abc";
	EXPECT_EQ(str.length(), 3);
	EXPECT_EQ(str.capacity(), 15);
	EXPECT_EQ(str[2], 'c');
}

TEST(STR_TEST, StrModifyTest_1) {
	Str str = "liu";
	str.append("shu");
	EXPECT_EQ(str.compare("liushu"), 0);
	str.insert(6, "heng");
	EXPECT_EQ(str.compare("liushuheng"), 0);
}
