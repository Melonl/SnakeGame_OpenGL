#pragma once

class Cube {
public:
	float x;
	float y;
	bool head;

	Cube() = default;
	~Cube() = default;
	Cube(float xx = 0, float yy = 0, bool isHead = false);
	Cube(const Cube& cube);
	Cube& operator=(const Cube& cube);
	Cube& operator=(const Cube&& cube);
	bool is(float xx, float yy);
};