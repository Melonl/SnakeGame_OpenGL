#include "Snake.h"
#include <ctime>

void Snake::draw()
{
	//根据蛇的各个方块坐标动态计算顶点数据
	shader.Use();
	glBindVertexArray(vao);
	int size = SnakeBody.size();
	int constNum = 24;
	int bufferSize = size * sizeof(float)*constNum;//(3+3)*4
	float* vertices = (float*)malloc(bufferSize);
	for (int i = 0; i < size; i++) {
		vertices[i * constNum + 0] = SnakeBody[i].x + width;
		vertices[i * constNum + 1] = SnakeBody[i].y;
		vertices[i * constNum + 2] = 0;

		vertices[i * constNum + 6] = SnakeBody[i].x + width;
		vertices[i * constNum + 7] = SnakeBody[i].y - width;
		vertices[i * constNum + 8] = 0;

		vertices[i * constNum + 12] = SnakeBody[i].x;
		vertices[i * constNum + 13] = SnakeBody[i].y - width;
		vertices[i * constNum + 14] = 0;

		vertices[i * constNum + 18] = SnakeBody[i].x;
		vertices[i * constNum + 19] = SnakeBody[i].y;
		vertices[i * constNum + 20] = 0;

		for (int j = 0; j < 4; j++) {
			
			vertices[i * constNum + (2 * j + 1) * 3 + 0] = color[SnakeBody[i].head][0];
			vertices[i * constNum + (2 * j + 1) * 3 + 1] = color[SnakeBody[i].head][1];
			vertices[i * constNum + (2 * j + 1) * 3 + 2] = color[SnakeBody[i].head][2];
		}
	}
	glBufferData(GL_ARRAY_BUFFER,bufferSize , vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int indexBufferSize = sizeof(unsigned int)*size * 6;
	unsigned int* indices = (unsigned int*)malloc(indexBufferSize);
	for (int j = 0; j < 6; j++) {
		indices[j] = ConstIndices[j];
	}
	for (int i = 1; i < size; i++) {

		
		for (int j = 0; j < 6; j++) {
			indices[i * 6 + j] = indices[(i-1)*6 + j] + 4;
		}
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indices, GL_STATIC_DRAW);
	
	glDrawElements(GL_TRIANGLES, 6*size, GL_UNSIGNED_INT, 0);

	free(vertices);
	free(indices);

	glBindVertexArray(0);
	shader.unUse();

	
}

bool Snake::contains(float x, float y)
{
	bool res = false;
	for (unsigned int i = 0; i < SnakeBody.size(); i++) {
		if (SnakeBody[i].is(x, y)) {
			res = true;
			break;
		}
	}
	return res;
}

void Snake::eat()
{
	eaten = true;
}

Cube & Snake::GetHead()
{
	return SnakeBody[0];
}

void Snake::initVBs()
{
	//初始化vao vbo ebo(ibo)
	shader.Use();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ConstIndices), ConstIndices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	shader.unUse();
}

Snake::Snake(float x, float y):shader("shader/snake.vert", "shader/snake.frag")
{
	d  = lastDirect = Down;
	addBody(x, y, true);
	addBody(x, y + width, false);
	initVBs();
	
}

Snake::~Snake()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Snake::update()
{

	float x, y;
	x = SnakeBody[SnakeBody.size() - 1].x;
	y = SnakeBody[SnakeBody.size() - 1].y;

	for (unsigned int i = SnakeBody.size() - 1; i > 0; i--) {
		SnakeBody[i] = SnakeBody[i - 1];
	}

	/*
	cout << SnakeBody[0].x
		<< ","
		<< SnakeBody[0].y
		<< endl;
	*/

	switch (this->d) {
	case Down:
		SnakeBody[0].y -= width;
		break;

	case Up:
		SnakeBody[0].y += width;
		break;

	case Left:
		SnakeBody[0].x -= width;
		break;

	case Right:
		SnakeBody[0].x += width;
		break;
	default:
		cout << "error:"
			<< &d
			<< ","
			<< d
			<< endl;

		break;
	}
	if (SnakeBody[0].x > 0.96 || SnakeBody[0].x < -1.01) {
		SnakeBody[0].x < 0 ? SnakeBody[0].x += 2*width : 0;
		SnakeBody[0].x = -SnakeBody[0].x;
	}
	if (SnakeBody[0].y > 1.01 || SnakeBody[0].y < -0.96) {
		SnakeBody[0].y < 0 ? 0 : SnakeBody[0].y -= 2*width;
		SnakeBody[0].y = -SnakeBody[0].y;
	}
	/*
	cout << "length:"
		<< SnakeBody.size()
		<< endl;
	*/

	if (eaten) {
		eaten = false;
		SnakeBody.push_back(Cube(x,y,false));
	}

	
}

void Snake::addBody(float x, float y,bool isHead)
{
	SnakeBody.push_back(Cube(x,y,isHead));
}


void Snake::setDirect(Direct d)
{
	if (abs((int)d - (int)this->d) == 2) { return; }
	this->d = d;
}
