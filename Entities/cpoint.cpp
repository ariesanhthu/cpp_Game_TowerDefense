#include "cpoint.h"

bool cpoint::operator==(const cpoint& a) {
	return x == a.x && y == a.y;
}

float cpoint::distance(const cpoint& a) {
	return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
}

cpoint cpoint::operator+(const cpoint& other) {
	return { x + other.x, y + other.y, 0 };
}
cpoint cpoint::operator-(const cpoint& other) {
	return { x - other.x, y - other.y, 0 };
}
cpoint cpoint::operator*(const int& scale) {
	return { x*scale, y*scale, 0 };
}
cpoint cpoint::normalized() {
	int nx = x, ny = y;
	if (x != 0) nx /= abs(x);
	if (y != 0) ny /= abs(y);

	return { nx, ny, 0};
}