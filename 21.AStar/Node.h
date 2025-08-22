#pragma once

#include <iostream>

// 좌표 다루기 위한 구조체.
// c++ 원칙상 struct/class 차이가 없음.
// 접근 한정자(제한자/visibility) struct public/class private 기본.
// 코딩 표준(struct - 데이터 전용 / class 객체).
struct Position
{
	Position(int x = 0, int y = 0)
		: x(x), y(y)
	{
	}

	// 비교 연산자 오버로딩.
	bool operator==(const Position& other)
	{
		return x == other.x && y == other.y;
	}

	int x = 0;
	int y = 0;
};

class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr)
		: position(x, y), parent(parentNode)
	{
	}

	Position operator-(const Node& other)
	{
		return Position(
			position.x - other.position.x,
			position.y - other.position.y
		);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x
			&& position.y == other.position.y;
	}

public:
	Position position;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Node* parent = nullptr;
};