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

//// 작은 맵.
//const size_t MAZE_SIZE = 6;
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//    {'1','1','1','1','1','1'},
//    {'s','0','1','0','0','1'},
//    {'1','0','0','0','1','1'},
//    {'1','0','1','0','1','1'},
//    {'1','0','1','0','0','g'},
//    {'1','1','1','1','1','1'}
//};

// 큰 맵.
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

// 가려는 위치가 이동 가능한지 확인하는 함수
bool IsValidLocation(int y, int x)
{
    if (y < 0 || y >= MAZE_SIZE || x < 0 || x >= MAZE_SIZE)
    {
        return false;
    }

    return map[y][x] == '0' || map[y][x] == 'g';
}

void ClearScreen()
{
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // 커서 감추기
    CONSOLE_CURSOR_INFO info = {};
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(handle, &info);

    // 콘솔 위치 처음으로 이동
    SetConsoleCursorPosition(handle, { 0,0 });

    for (int y = 0; y < MAZE_SIZE; ++y)
    {
        for (int x = 0; x < MAZE_SIZE; ++x)
        {
            std::cout << " ";
        }

        std::cout << '\n';
    }

    SetConsoleCursorPosition(handle, { 0,0 });
}

// 위치 출력 함수
void PrintLocation(int playerX, int playerY, unsigned long delay)
{
    Sleep(delay);

    ClearScreen();

    for (int y = 0; y < MAZE_SIZE; ++y)
    {
        for (int x = 0; x < MAZE_SIZE; ++x)
        {
            // 플레이어 위치 출력
            if (x == playerX && y == playerY)
            {
                std::cout << "P ";
                continue;
            }

            // 나머지는 맵 그리기
            std::cout << map[y][x] << " ";
        }

        std::cout << '\n';
    }
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

    // 미로 탐색
    while (!locationStack.IsEmpty())
    {
        Vector2 current = locationStack.Pop();
        //std::cout << current << " ";

        PrintLocation(current.x, current.y, 500);

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