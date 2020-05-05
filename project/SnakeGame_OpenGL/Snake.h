#pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>  

#include "Shader.h"
#include "Cube.h"

using namespace std;

enum Direct { Left, Up, Right, Down };

class Snake{


private :
	 
	
	const unsigned int ConstIndices[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	const float color[2][3] = {{ 1.0,1.0,0.19 },{ 1.0,1.0,0.19 } };
	vector<Cube> SnakeBody;//�������������������������cube����
	Shader shader;
	GLuint vao, vbo,ebo;
	atomic<enum Direct> d;
	enum Direct lastDirect;//���ڷ�ֹ��ͷ180��ת��
	bool eaten = false;//�Ƿ�Ե�ʳ��ı��

	void initVBs();
	
public :
	const float width = 0.05f;

	Snake(float x,float y);
	~Snake();
	void addBody(float x,float y, bool isHead);
	void setDirect(Direct d);
	void draw();
	bool contains(float x, float y);//���ڷ�ֹʳ��������������
	void eat();//�Ե�ʳ��
	Cube& GetHead();
	void update();//�����ߵ�״̬��ʹ���ƶ�

};