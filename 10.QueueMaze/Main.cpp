#include <iostream>
#include <Windows.h>
#include "Queue.h"

// 좌표를 나타내는 클래스.
class Vector2
{
public:
	Vector2(int x = 0, int y = 0)
		: x(x), y(y)
	{
	}

	// 출력 편의를 위해 연산자 오버로딩.
	friend std::ostream& operator<<(
		std::ostream& os,
		const Vector2& position)
	{
		return os << "(" << position.x << "," << position.y << ")";
	}

	int x = 0;
	int y = 0;
};

//// 작은 맵.
//const size_t MAZE_SIZE = 6;
//
//// map[y][x];
//// s: 시작지점.
//// g: 목표지점.
//// 1: 이동불가.
//// 0: 이동가능.
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//	{'1','1','1','1','1','1'},
//	{'s','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','g'},
//	{'1','1','1','1','1','1'}
//};

const size_t MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'s', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'g'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

// 가려는 위치가 이동 가능한지 확인하는 함수.
// 입력은 행(y), 열(x) 순서로.
bool IsValidLocation(int y, int  x)
{
	// 예외 처리.
	if (y < 0 || y >= MAZE_SIZE || x < 0 || x >= MAZE_SIZE)
	{
		return false;
	}

	// 확인.
	return map[y][x] == '0' || map[y][x] == 'g';
}

// 화면 지우기 함수.
void ClearScreen()
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 감추기.
	CONSOLE_CURSOR_INFO info = {};
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &info);

	// 콘솔 위치 처음으로 이동.
	SetConsoleCursorPosition(handle, { 0, 0 });

	// 가로/세로 모두에 빈칸 채우기.
	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << " ";
		}

		std::cout << "\n";
	}

	// 콘솔 위치 처음으로 이동.
	SetConsoleCursorPosition(handle, { 0, 0 });
}

// 위치 출력 함수.
void PrintLocation(int playerX, int playerY, unsigned long delay)
{
	// 밀리세컨드(1/1000초) 단위로 CPU 재우기.
	Sleep(delay);

	// 콘솔 화면 지우기.
	ClearScreen();

	// 맵과 플레이어 그리기.
	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			// 플레이어 위치 출력.
			if (x == playerX && y == playerY)
			{
				std::cout << "P ";
				continue;
			}

			// 나머지는 맵 그리기.
			std::cout << map[y][x] << " ";
		}

		std::cout << "\n";
	}
}

int main()
{
	// 시작위치 검색.
	int startX = 0;
	int startY = 0;

	for (int y = 0; y < MAZE_SIZE; ++y)
	{
		for (int x = 0; x < MAZE_SIZE; ++x)
		{
			std::cout << map[y][x] << " ";

			// 시작위치인지 확인.
			if (map[y][x] == 's')
			{
				startX = x;
				startY = y;
			}
		}

		std::cout << "\n";
	}

	// 시작 위치부터 탐색.
	// 큐에 삽입.
	//Stack<Vector2> locationStack;
	Queue<Vector2> locationQueue;
	locationQueue.Enqueue(Vector2(startX, startY));

	// 미로 탐색.
	while (!locationQueue.IsEmpty())
	{
		// 현재 위치 반환(출력을 위해).
		Vector2 current;
		locationQueue.Dequeue(current);
		//std::cout << current << " ";

		// 맵과 플레이어 위치 출력.
		PrintLocation(current.x, current.y, 500);

		// 도착했는지 확인.
		if (map[current.y][current.x] == 'g')
		{
			std::cout << "\n미로 탐색 성공\n";

			std::cin.get();
			return 0;
		}

		// 탐색 이어가기.
		map[current.y][current.x] = '.';

		// 앞으로 이동할 위치를 스택에 삽입.
		// 이 때 방향 우선순위는 정하기 나름.
		// 상/하/좌/우 순서로 큐에 삽입.
		// 탐색 순서: 우/좌/하/상 순서로 탐색.

		// 상.
		if (IsValidLocation(current.y - 1, current.x))
		{
			locationQueue.Enqueue(Vector2(current.x, current.y - 1));
		}

		// 하.
		if (IsValidLocation(current.y + 1, current.x))
		{
			locationQueue.Enqueue(Vector2(current.x, current.y + 1));
		}

		// 좌.
		if (IsValidLocation(current.y, current.x - 1))
		{
			locationQueue.Enqueue(Vector2(current.x - 1, current.y));
		}

		// 우.
		if (IsValidLocation(current.y, current.x + 1))
		{
			locationQueue.Enqueue(Vector2(current.x + 1, current.y));
		}
	}

	// 여기 도달하면 탐색 실패.
	std::cout << "\n미로 탐색 실패\n";
	std::cin.get();
}