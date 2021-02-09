#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <SDL_image.h>
#include "Texture.h"
#include "RayCastDemo.h"

int main(int argc, char* argv[])
{
	try
	{
		RayCastDemo demo(640, 480, 240, 320);
		demo.start();
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
