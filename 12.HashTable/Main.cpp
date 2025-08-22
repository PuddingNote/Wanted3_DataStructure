#include "HashTable.h"
#include <iostream>
#include <unordered_map>

int main()
{
	std::unordered_map<int, int> testMap;

	// 해시테이블 객체 생성.
	HashTable table;

	// 데이터 임시 추가.
	table.Add("Ronnie", "010-12345678");
	table.Add("Ronnie", "010-23897498");

	table.Add("Kevin", "010-29384792");
	table.Add("Baker", "010-23489798");
	table.Add("Taejun", "010-09234859");
	table.Add("Emily", "010-09809123");

	// 출력.
	table.Print();

	// 검색.
	TPair<std::string, std::string> find;
	if (table.Find("Baker", find)) // 검색 성공.
	{
		std::cout << "검색 결과: " << find.key << ", " << find.value << "\n";
	}

	// 삭제.
	table.Delete("Kevin");
	table.Delete("Ronnie");
	table.Delete("Test");

	table.Print();

	std::cin.get();
}