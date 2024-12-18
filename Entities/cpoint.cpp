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
cpoint cpoint::normalized(float lenght, int speed) {
	int nx = x, ny = y;
	if (x != 0) nx = static_cast<int> (x / lenght * speed);
	if (y != 0) ny = static_cast<int> (y / lenght * speed);

	return { nx, ny, 0};
}