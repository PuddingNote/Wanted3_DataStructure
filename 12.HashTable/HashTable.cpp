#include "HashTable.h"

// 해시 함수(Hash Function).
// 파라미터로 전달받은 키를 활용해서 해시(숫자)를 생성하는 함수.
int GenerateKey(const std::string& keyString)
{
	// 생성될 키 변수.
	int key = 0;
	for (int ix = 0; ix < (int)keyString.length(); ++ix)
	{
		//key += keyString[ix] * (ix + 1);
		key = key * 31 + keyString[ix];
	}

	// 절대값으로 반환.
	// 해시테이블에 저장을 위해서는 키 값이 인덱스로 변환되어야 하는데,
	// 음수라면 문제가 되기 때문.
	// 최상위 비트가 1로 설정되면 음수로 판단하기 때문.
	//return key < 0 ? -key : key;
	return std::abs(key);
}

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

void HashTable::Add(const std::string& key, const std::string& value)
{
	// 키 생성.
	int keyValue = GenerateKey(key);

	// UI -> 이미지로 숫자를 표현할 때.
	// 0,1,2,3,4,5,6,7,8,9
	// 3421점
	// 3421 / 1000 -> 3, 3421 % 1000, 421.
	// 421 / 100 -> 4, 21.
	// 21 / 10 -> 2, 1.
	// 글자 흘리기.

	// 버킷 인덱스로 변환.
	int bucketIndex = keyValue % bucketCount;

	// 저장할 연결 리스트 가져오기.
	LinkedList<Entry>& list = table[bucketIndex];

	// 키가 같은 걸 허용할지? 허용하지 않을지?
	// STL의 경우에도 명시적으로 동일한 키를 허용하는 경우와 
	// 허용하지 않는 경우의 자료구조를 구분해서 제공.
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		// 키가 같은걸 허용하지 않음.
		if (list[ix]->data.key == key)
		{
			std::cout << "이미 동일한 키를 가진 데이터가 저장돼 있습니다.\n";
			return;
		}
	}

	// 해시테이블에 값 추가.
	list.PushLast(Entry(key, value));
}

void HashTable::Delete(const std::string& key)
{
	// 삭제 연산은 2단계의 복합 과정.
	// 1. 찾기.
	int keyValue = GenerateKey(key);

	// 버킷인덱스.
	int bucketIndex = keyValue % bucketCount;

	// 리스트 가져오기.
	LinkedList<Entry>& list = table[bucketIndex];

	// 동일한 키값을 가진 데이터 검색.
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		// 2. 삭제.
		if (list[ix]->data.key == key)
		{
			list.Delete(list[ix]->data);
			std::cout << "항목을 삭제했습니다.\n";
			return;
		}
	}

	// 삭제 실패.
	std::cout << "삭제할 데이터를 찾지 못했습니다.\n";
}

bool HashTable::Find(const std::string& key, Entry& outValue)
{
	int keyValue = GenerateKey(key);

	// 버킷인덱스.
	int bucketIndex = keyValue % bucketCount;

	// 리스트 가져오기.
	LinkedList<Entry>& list = table[bucketIndex];

	// 검색할 필요가 있는지 확인.
	if (list.Count() == 0)
	{
		std::cout << "해당 키로 데이터를 검색하지 못했습니다.\n";
		return false;
	}

	// 검색.
	for (int ix = 0; ix < (int)list.Count(); ++ix)
	{
		// 같은 키를 가진 데이트를 찾았으면,
		if (list[ix]->data.key == key)
		{
			// 출력할 파라미터에 값 저장.
			outValue = list[ix]->data;

			// 검색 성공 반환.
			return true;
		}
	}

	std::cout << "해당 키로 데이터를 검색하지 못했습니다.\n";
	return false;
}

// 출력.
void HashTable::Print()
{
	for (int ix = 0; ix < bucketCount; ++ix)
	{
		// 배열인덱스에 해당하는 연결리스트가 비었으면 다음으로 건너뜀.
		LinkedList<Entry>& list = table[ix];

		//if (table[ix].Count() == 0)
		if (list.Count() == 0)
		{
			continue;
		}

		//for (int jx = 0; jx < (int)table[ix].Count(); ++jx)
		for (int jx = 0; jx < (int)list.Count(); ++jx)
		{
			std::cout
				//<< "키: " << table[ix][jx]->data.key
				//<< " 값: " << table[ix][jx]->data.value
				//<< "\n";
				<< "키: " << list[jx]->data.key
				<< " 값: " << list[jx]->data.value
				<< "\n";
		}
	}
}

// 비었는지 확인.
bool HashTable::IsEmpty() const
{
	// 누적 데이터 수.
	int totalCount = 0;

	// 테이블 안의 연결 리스트를 순회하면서 각 리스트 요수의 수를 합산.
	for (int ix = 0; ix < bucketCount; ++ix)
	{
		totalCount += (int)table[ix].Count();
	}

	// 합산한 결과가 0이면 빈 상태.
	return totalCount == 0;
}