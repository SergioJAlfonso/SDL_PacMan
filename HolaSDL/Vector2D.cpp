#include "Vector2D.h"

Vector2D::Vector2D(int a, int b) {
	x = a;
	y = b;
}

Vector2D::Vector2D(const Vector2D& v) {
	x = v.x;
	y = v.y;
}

Vector2D Vector2D::operator+(Vector2D const& v){
	Vector2D sol(v.x + x, v.y + y);
	return sol;
}

Vector2D Vector2D::operator-(Vector2D const& v) {
	Vector2D sol(x - v.x, y - v.y);
	return sol;
}

int Vector2D::operator*(Vector2D const& v) {
	return(x * v.x + y * v.y);
}

Vector2D Vector2D::operator*(int e) {
	Vector2D sol(x * e, y * e);
	return sol;
}

bool Vector2D::operator==(Vector2D const& v){
	return(x == v.x && y == v.y);
}

//istream& operator>>(istream& is, Vector2D& v){
//	is >> v.x >> v.y;
//	return is;
//}

//ostream& operator<<(ostream& out, const Vector2D& v) {
//	out << v.x << " " << v.y;
//	return out;
//}

void Vector2D::set(int x, int y){
	this->x = x;
	this->y = y;
}

void Vector2D::setX(int x) {
	this->x = x;
}

void Vector2D::setY(int y) {
	this->y = y;
}