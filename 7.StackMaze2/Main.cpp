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

//// ���� ��.
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

// ū ��.
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

// ������ ��ġ�� �̵� �������� Ȯ���ϴ� �Լ�
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

    // Ŀ�� ���߱�
    CONSOLE_CURSOR_INFO info = {};
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(handle, &info);

    // �ܼ� ��ġ ó������ �̵�
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

// ��ġ ��� �Լ�
void PrintLocation(int playerX, int playerY, unsigned long delay)
{
    Sleep(delay);

    ClearScreen();

    for (int y = 0; y < MAZE_SIZE; ++y)
    {
        for (int x = 0; x < MAZE_SIZE; ++x)
        {
            // �÷��̾� ��ġ ���
            if (x == playerX && y == playerY)
            {
                std::cout << "P ";
                continue;
            }

            // �������� �� �׸���
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

    // �̷� Ž��
    while (!locationStack.IsEmpty())
    {
        Vector2 current = locationStack.Pop();
        //std::cout << current << " ";

        PrintLocation(current.x, current.y, 500);

        // �����ߴ��� Ȯ��
        if (map[current.y][current.x] == 'g')
        {
            std::cout << "\n�̷� Ž�� ����\n";

            std::cin.get();
            return 0;
        }

        // Ž�� �̾��
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

    std::cout << "\n�̷� Ž�� ����\n";
    std::cin.get();
}