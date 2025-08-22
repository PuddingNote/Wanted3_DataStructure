#pragma once

#include <iostream>
#include <string>
#include "Pair.h"
#include "LinkedList.h"

/*
* 작성자: 장세윤.
* 해시테이블 클래스.
* 키-값을 쌍으로 저장하는 자료구조.
*/

class HashTable
{
	// Type Alias(타입 재정의).
private:
	using Entry = TPair<std::string, std::string>;

public:
	HashTable();
	~HashTable();

	// 추가.
	void Add(const std::string& key, const std::string& value);

	// 삭제.
	void Delete(const std::string& key);

	// 검색.
	bool Find(const std::string& key, Entry& outValue);

	// 출력.
	void Print();

	// 비었는지 확인.
	bool IsEmpty() const;

private:

	// 버킷(Bucket) 정의.
	static const int bucketCount = 19;

	// 2차 자료구조 활용 (체이닝).
	LinkedList<Entry> table[bucketCount] = { };
};