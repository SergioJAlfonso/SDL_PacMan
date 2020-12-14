#pragma once
#include <iostream>
using namespace std;
class Vector2D {
private:
	int x, y;
public:
	Vector2D() : x(0), y(0) {};
	Vector2D(int a, int b);
	Vector2D(const Vector2D& v);
	int getX() const { return x; };
	int getY() const { return y; };
	void set(int x, int y);

	Vector2D operator+(Vector2D const &v);
	Vector2D operator-(Vector2D const& v);
	int operator*(Vector2D const& v);
	Vector2D operator*(int e);
	bool operator==(Vector2D const& v);
	//friend istream& operator>>(istream& is, Vector2D& v);
	friend ostream& operator<<(ostream& out, const Vector2D& v);
	void setX(int x);
	void setY(int y);
};
using Point2D = Vector2D;


