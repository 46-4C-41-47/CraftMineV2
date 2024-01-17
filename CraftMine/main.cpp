#include <iostream>
#include <stdexcept>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/CMWindow.h"
#include "include/GLDynamicBuffer.h"


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


/*int main()
{
	std::map<int, int> m;
	std::pair<std::map<int, int>::iterator, bool> pos;
	
	for (int i = 0; i < 5; i++)
	{
		if (pos.first < m.emplace(0, 0).first)
		{

		}
	}

	std::cout << pos.first->second << "\n";
	
	for (std::map<int, int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << "key : " << it->first << ", value : " << it->second << "\n";
}*/


/*
À FAIRE : 
	afficher le framerate
	Classe Chunk (en cours)
	Finir la classe GLBufferConfig
	Skybox
	Bloques destructibles

À TESTER :
	GLVector::remove
	GLMap::GLMap
	GLMap::add
	GLMap::remove

BUG :
	La limite de framerate dans la fonction run de CMWindow marche pas 
	Impossible d'utiliser la bibliothèque FastNoise avec plusieurs instances de Chunk
*/
