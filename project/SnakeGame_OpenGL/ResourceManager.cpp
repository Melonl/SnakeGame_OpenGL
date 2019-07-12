
#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;

unsigned char* ResourceManager::loadImage(const char* filePath, picInfo& infoObj) {

	return stbi_load(filePath, &infoObj.width, &infoObj.height, &infoObj.nrChannels, 0);

}

void ResourceManager::reverse_Y_Pos(bool b) {
	stbi_set_flip_vertically_on_load(b);
}

string ResourceManager::loadShaderFile(const char* filePath) {
	string code;
	ifstream file;

	//保证ifstream对象能抛出异常
	file.exceptions(ifstream::badbit);
	try {
		file.open(filePath);
		stringstream fStream;
		fStream << file.rdbuf();
		file.close();
		code = fStream.str();
	}
	catch (ifstream::failure e) {
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return code;
}
