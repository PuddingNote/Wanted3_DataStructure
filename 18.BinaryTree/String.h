#pragma once

#include <iostream>

/*
* 문자열 클래스.
* 원시 문자 포인터를 관리하는 클래스.
*/

class String
{
public:
	String(const char* value = nullptr);
	String(const String& other);
	String(String&& other);

	~String();

	// 연산자 오버로딩.
	String& operator=(const String& other);
	String& operator=(String&& other);
	bool operator==(const String& other);
	String operator+(const String& other);

	// 편의 함수.
	friend std::ostream& operator<<(std::ostream& os, const String& string);

private:

	// 문자 수.
	int length = 0;

	// 문자열 저장 포인터.
	char* data = nullptr;
};