#pragma once
#include"Shader.h"

class Food{

	friend class Level;

private:
	float x, y;
	Shader shader;
	GLuint vao, vbo, ebo;
	const unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	const float color[3] = { 1.0,0.078,0.57};//食物方块颜色

	void initVBs();

public:
	const float width = 0.05f;

	Food(float xx,float yy);
	void upgrade(float newx, float newy);//更新坐标
	void draw();

	
};
