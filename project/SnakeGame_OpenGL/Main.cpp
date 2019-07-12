
#include <iostream>
#include <fstream>

#include "Shader.h"
#include "ResourceManager.h"
#include"Level.h"

#include <GLFW/glfw3.h>


using namespace std;

GLFWwindow* window;
int h, w;

Level* level;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//按下esc
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//处理上下左右键
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		level->setDirect(Down);
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		level->setDirect(Up);
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		level->setDirect(Left);
	}
	
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		level->setDirect(Right);
	}



}

void initWindow() {

	//初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//利用GLFW创建OpenGL窗口以及contex
	window = glfwCreateWindow(600, 600, "Snake Game", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window"
			<< std::endl;
		glfwTerminate();
		exit(0);
		return;
	}
	glfwMakeContextCurrent(window);


	//初始化GLEW,GLEW会帮我们初始化各种OpenGL函数的指针
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GlEW"
			<< std::endl;
		exit(0);
		return;
	}

	//告诉OpenGL窗口数据
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	//设置按键回调
	glfwSetKeyCallback(window, key_callback);


}

int main() {

	initWindow();

	level = new Level;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();//处理事件，调用相应回调，如键盘输入等
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空颜色
		glClear(GL_COLOR_BUFFER_BIT );//使用设置的ClearColor清空屏幕

		
		level->draw();

		glfwSwapBuffers(window);//交换缓冲，绘制内容
	}

	glfwTerminate();

	delete level;
	return 0;
}