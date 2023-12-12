#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/CMWindow.h"


int main()
{
	CMWindow* window;
	
	try
	{
		window = new CMWindow("CraftMine", false);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}

	window->start();

	delete window;
	return 0;
}
