#pragma once

/*
* 2차원에서 사각형 영역을 표시하는 클래스.
*/

class Bounds
{
public:
	Bounds(float x, float y, float width = 1.0f, float height = 1.0f)
		: x(x), y(y), width(width), height(height)
	{
	}

	Bounds(const Bounds& other)
		: x(other.x), y(other.y), width(other.width), height(other.height)
	{
	}

	// 겹침 판정 함수.
	bool Intersects(const Bounds& other) const;

	// Getter/Setter (게터/세터).
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	float MaxX() const { return x + width; }
	float MaxY() const { return y + height; }

private:
	// 위치 기준은 왼쪽 상단.
	float x = 0.0f;
	float y = 0.0f;
	float width = 1.0f;
	float height = 1.0f;
};