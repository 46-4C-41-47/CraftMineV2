#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

/*
À FAIRE : 
	Classe Chunk
	Skybox
	bloques destructibles

BUG :
	La limite de framerate dans la fonction run de CMWindow marche pas 
*/
