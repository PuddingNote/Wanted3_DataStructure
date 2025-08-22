#pragma once

#include <iostream>

/*
* ���ڿ� Ŭ����.
* ���� ���� �����͸� �����ϴ� Ŭ����.
*/

class String
{
public:
	String(const char* value = nullptr);
	String(const String& other);
	String(String&& other);

	~String();

	// ������ �����ε�.
	String& operator=(const String& other);
	String& operator=(String&& other);
	bool operator==(const String& other);
	String operator+(const String& other);

	// ���� �Լ�.
	friend std::ostream& operator<<(std::ostream& os, const String& string);

private:

	// ���� ��.
	int length = 0;

	// ���ڿ� ���� ������.
	char* data = nullptr;
};