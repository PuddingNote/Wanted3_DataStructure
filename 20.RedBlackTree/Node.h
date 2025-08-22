#pragma once

// 노드의 색상을 나타내는 열거형.
enum class Color
{
	Red,
	Black
};

class Node
{
public:
	Node(int data, Color color = Color::Red);
	~Node() = default;

	// 데이터 필드.
	int GetData() const { return data; }
	void SetData(int newData) { data = newData; }

	// 색상.
	Color GetColor() const { return color; }
	void SetColor(Color newColor) { color = newColor; }
	const char* GetColorString() const;

	// 부모 노드.
	Node* GetParent() const { return parent; }
	void SetParent(Node* newParent) { parent = newParent; }

	// 왼쪽 자손 노드.
	Node* GetLeft() const { return left; }
	void SetLeft(Node* newLeft) { left = newLeft; }

	// 오른쪽 자손 노드.
	Node* GetRight() const { return right; }
	void SetRight(Node* newRight) { right = newRight; }

private:

	// 데이터 필드.
	int data = 0;

	// 색상.
	Color color = Color::Red;

	// 부모 노드.
	Node* parent = nullptr;

	// 왼쪽 자손 노드.
	Node* left = nullptr;

	// 오른쪽 자손 노드.
	Node* right = nullptr;
};