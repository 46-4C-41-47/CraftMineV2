#include <chrono>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/GLMap.h"
#include "include/CMWindow.h"


int main()
{
	std::unique_ptr<CMWindow> window;
	
	try
	{
		window = std::make_unique<CMWindow>("CraftMine", false);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}

	window->start();

	return 0;
}
