#pragma once
#include <vector>
#include <iostream>
#include "Shader.h"
#include <thread>
#include <atomic>  

using namespace std;

enum Direct { Left, Up, Right, Down };

class Cube {
public:
	float x;
	float y;
	bool head;


	Cube(float xx,float yy,bool isHead):x(xx),y(yy),head(isHead) {}
	Cube(){}
	void operator=(const Cube& cube){
		x = cube.x;
		y = cube.y;
	}
	
	bool is(float xx, float yy) {
		bool res = false;
		if (x == xx && y == yy) {
			res = true;
		}
		return res;
	}
};

class Snake{


private :
	 
	
	const unsigned int ConstIndices[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	const float color[2][3] = {{ 1.0,1.0,0.19 },{ 1.0,1.0,0.19 } };
	vector<Cube> SnakeBody;//蛇身容器，保存所有蛇身方块的cube对象
	Shader shader;
	GLuint vao, vbo,ebo;
	atomic<enum Direct> d;
	enum Direct lastDirect;//用于防止蛇头180度转向
	bool eaten = false;//是否吃到食物的标记

	void initVBs();
	
public :
	const float width = 0.05f;

	Snake(float x,float y);
	~Snake();
	void addBody(float x,float y, bool isHead);
	void setDirect(Direct d);
	void draw();
	bool contains(float x, float y);//用于防止食物生成在蛇身上
	void eat();//吃到食物
	Cube& GetHead();
	void update();//更新蛇的状态，使蛇移动

};