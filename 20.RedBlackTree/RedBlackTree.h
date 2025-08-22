#pragma once

#include "Node.h"
#include <iostream>
#include <Windows.h>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// 검색.
	bool Find(int data, Node*& outNode);

	// 추가.
	bool Insert(int data);

	// 출력 함수.
	void Print(int depth = 0, int blackCount = 0);

private:

	// 노드 생성 함수.
	// 팩토리 패턴.
	Node* CreateNode(int data, Color color);

	/// <summary>
	/// 검색 재귀 함수. 
	/// </summary>
	/// <param name="data">검색할 값</param>
	/// <param name="node">현재 검색하는 노드</param>
	/// <param name="outNode">검색한 노드를 출력할 파라미터</param>
	bool FindRecursive(int data, Node* node, Node*& outNode);

	// 노드 삽입 재귀 함수.
	void InsertRecursive(Node* node, Node* newNode);

	// 노드 삽입 후 재정렬 처리 함수.
	void RestructureAfterInsert(Node* newNode);

	// 좌회전 함수.
	void RotateToLeft(Node* node);

	// 우회전 함수.
	void RotateToRight(Node* node);

	// 출력 재귀 함수.
	void PrintRecursive(Node* node, int depth, int blackCount);

	// 트리 파괴 재귀 함수.
	void DestroyRecursive(Node* node);

private:

	// 루트 노드.
	Node* root = nullptr;

	// Nil 노드.
	/*static */Node* nil = nullptr;
};

enum class TextColor
{
	// 콘솔 색상 정의.
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

// 콘솔 색상 변경 함수.
void SetTextColor(TextColor color);