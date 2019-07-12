
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>



class ResourceManager {

public:

	class picInfo {
	public :

		int width = -1;
		int height = -1;
		int nrChannels = -1;
	};

	static unsigned char* loadImage(const char* filePath,picInfo& infoObj);
	static void reverse_Y_Pos(bool b);
	static std::string loadShaderFile(const char* filePath);

};


#endif