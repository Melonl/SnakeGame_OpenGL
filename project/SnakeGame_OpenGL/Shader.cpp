#include "Shader.h"
#include "ResourceManager.h"
#include <iostream>

#include <fstream>
#include <sstream>



using namespace std;

Shader::Shader(const GLchar* vPath, const GLchar* fPath) {
	
	string vCode = ResourceManager::loadShaderFile(vPath);
	string fCode = ResourceManager::loadShaderFile(fPath);
	
	const GLchar* vsCode = vCode.c_str();
	const GLchar* fsCode = fCode.c_str();

	// 2. ������ɫ��
	GLuint vertex, fragment;
	

	// ������ɫ��
	vertex = compileShader(GL_VERTEX_SHADER,vsCode);

	// Ƭ����ɫ��
	fragment = compileShader(GL_FRAGMENT_SHADER, fsCode);


	// ��ɫ������
	this->Program = createProgram(vertex,fragment);
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);


}

void Shader::Use() {
	glUseProgram(this->Program);
}

void Shader::unUse()
{
	glUseProgram(0);
}

GLuint Shader::getID() {
	return this->Program;
}

GLuint Shader::compileShader(GLenum shaderType, const GLchar* shaderCode) {
	
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader,1,&shaderCode,NULL);
	glCompileShader(shader);
	GLint success;
	GLchar infoLog[512];
	// ��ӡ�����������еĻ���
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
	return shader;
}

GLuint Shader::createProgram(GLuint vertShader, GLuint fragShader) {

	GLint success;
	GLchar infoLog[512];

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertShader);
	glAttachShader(this->Program, fragShader);
	glLinkProgram(this->Program);
	// ��ӡ���Ӵ�������еĻ���
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	return this->Program;
}

GLuint Shader::getUniformLocation(const char* varName) {
	return glGetUniformLocation(this->Program,varName);
}

void Shader::set1Int(const char* varName, int value) {
	glUniform1i(glGetUniformLocation(this->Program, varName), value);
}
void Shader::set1Float(const char* varName, float value) {
	glUniform1f(glGetUniformLocation(this->Program, varName), value);
}