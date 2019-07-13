#include "Food.h"
#include<cstdlib>

void Food::initVBs()
{
	shader.Use();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	shader.unUse();
}

Food::Food(float xx, float yy):shader("shader/food.vert","shader/food.frag")
{
	initVBs();
}

void Food::upgrade(float newx, float newy)
{
	x = newx;
	y = newy;
}

void Food::draw()
{
	shader.Use();
	glBindVertexArray(vao);
	int constNum = 24;
	int bufferSize = sizeof(float)*constNum;
	float* vertices = (float*)malloc(bufferSize);

	vertices[0] = x + width;
	vertices[1] = y;
	vertices[2] = 0;

	vertices[6] = x + width;
	vertices[7] = y - width;
	vertices[8] = 0;

	vertices[12] = x;
	vertices[13] = y - width;
	vertices[14] = 0;

	vertices[18] = x;
	vertices[19] = y;
	vertices[20] = 0;

	for (int j = 0; j < 4; j++) {

		vertices[(2 * j + 1) * 3 + 0] = color[0];
		vertices[(2 * j + 1) * 3 + 1] = color[1];
		vertices[(2 * j + 1) * 3 + 2] = color[2];
	}
		
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	free(vertices);

	glBindVertexArray(0);
	shader.unUse();
}
