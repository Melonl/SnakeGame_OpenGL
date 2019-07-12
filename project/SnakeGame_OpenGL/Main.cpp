
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
	//����esc
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//�����������Ҽ�
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

	//��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//����GLFW����OpenGL�����Լ�contex
	window = glfwCreateWindow(600, 600, "Snake Game", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window"
			<< std::endl;
		glfwTerminate();
		exit(0);
		return;
	}
	glfwMakeContextCurrent(window);


	//��ʼ��GLEW,GLEW������ǳ�ʼ������OpenGL������ָ��
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GlEW"
			<< std::endl;
		exit(0);
		return;
	}

	//����OpenGL��������
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	//���ð����ص�
	glfwSetKeyCallback(window, key_callback);


}

int main() {

	initWindow();

	level = new Level;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();//�����¼���������Ӧ�ص�������������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������ɫ
		glClear(GL_COLOR_BUFFER_BIT );//ʹ�����õ�ClearColor�����Ļ

		
		level->draw();

		glfwSwapBuffers(window);//�������壬��������
	}

	glfwTerminate();

	delete level;
	return 0;
}