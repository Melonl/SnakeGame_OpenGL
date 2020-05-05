
#include "Cube.h"

Cube::Cube(float xx, float yy, bool isHead) :x(xx), y(yy), head(isHead) {}

Cube::Cube(const Cube &cube)
{
	x = cube.x;
	y = cube.y;
	head = cube.head;
}

Cube& Cube::operator=(const Cube& cube) {
	x = cube.x;
	y = cube.y;
	head = cube.head;
	return *this;
}

Cube& Cube::operator=(const Cube&& cube) {
	x = cube.x;
	y = cube.y;
	head = cube.head;
	return *this;
}

bool Cube::is(float xx, float yy) {
	return x == xx && y == yy;
}