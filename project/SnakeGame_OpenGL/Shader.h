#ifndef SHADER_H
#define SHADER_H
#define GLEW_STATIC
#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件


class Shader {

public :
	Shader(const GLchar* vPath, const GLchar* fPath);
	void Use();
	void unUse();
	GLuint getID();
	GLuint getUniformLocation(const char* varName);
	void set1Int(const char* varName,int value);
	void set1Float(const char* varName,float value);
	

private :
	GLuint Program;

	GLuint compileShader(GLenum shaderType,const GLchar* shaderCode);
	GLuint createProgram(GLuint vertShader,GLuint fragShader);

};



#endif
