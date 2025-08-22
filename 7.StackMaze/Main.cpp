#include <iostream>
#include "Stack.h"

class Vector2
{
public:
	Vector2(int x = 0, int y = 0) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Vector2& pos)
    {
        return os << "(" << pos.x << ", " << pos.y << ")";
    }

public:
	int x = 0;
	int y = 0;
};

// 작은 맵.
const size_t MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] =
{
    {'1','1','1','1','1','1'},
    {'s','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','g'},
    {'1','1','1','1','1','1'}
};

// 가려는 위치가 이동 가능한지 확인하는 함수
bool IsValidLocation(int y, int x)
{
    if (y < 0 || y >= MAZE_SIZE || x < 0 || x >= MAZE_SIZE)
    {
        return false;
    }

    return map[y][x] == '0' || map[y][x] == 'g';
}

int main()
{
    int startX = 0;
    int startY = 0;

    for (int y = 0; y < MAZE_SIZE; ++y)
    {
        for (int x = 0; x < MAZE_SIZE; ++x)
        {
            std::cout << map[y][x] << " ";

            if (map[y][x] == 's')
            {
                startX = x;
                startY = y;
            }
        }

        std::cout << '\n';
    }

    Stack<Vector2> locationStack;
    locationStack.Push(Vector2(startX, startY));

    while (!locationStack.IsEmpty())
    {
        Vector2 current = locationStack.Pop();
        std::cout << current<< " ";

        // 도착했는지 확인
        if (map[current.y][current.x] == 'g')
        {
            std::cout << "\n미로 탐색 성공\n";

            std::cin.get();
            return 0;
        }

        // 탐색 이어가기
        map[current.y][current.x] = '.';
        
        if (IsValidLocation(current.y - 1, current.x))
        {
            locationStack.Push(Vector2(current.x, current.y - 1));
        }
        if (IsValidLocation(current.y + 1, current.x))
        {
            locationStack.Push(Vector2(current.x, current.y + 1));
        }
        if (IsValidLocation(current.y, current.x - 1))
        {
            locationStack.Push(Vector2(current.x - 1, current.y));
        }
        if (IsValidLocation(current.y, current.x + 1))
        {
            locationStack.Push(Vector2(current.x + 1, current.y));
        }
    }

    std::cout << "\n미로 탐색 실패\n";
    std::cin.get();
}