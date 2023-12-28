#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/CMWindow.h"
#include "include/GLDynamicBuffer.h"


/*int main()
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
}*/

bool bufferUpdated = false;
bool bufferResized = false;

float data[] = {
	0.0f,  0.0f, 0.0f, // left  
	0.1f,  0.0f, 0.0f, // right 
	0.0f,  0.1f, 0.0f  // top   
};

std::vector<glm::vec3> positions = {
	glm::vec3(0.0f),
	glm::vec3(0.1f),
};


GLFWwindow* createWindow()
{
	if (!glfwInit())
		throw std::runtime_error("Initialization of GLFW failed\n");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 400, "Test", NULL, NULL);

	glfwSetWindowPos(window, 100, 100);

	if (window == NULL)
		throw std::runtime_error("GLFW window creation failed\n");

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD\n");

	glViewport(0, 0, 600, 400);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	return window;
}


void processInput(GLFWwindow* window, GLDynamicBuffer<glm::vec3>& buffer)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS and !bufferResized)
	{
		buffer.addRange({ glm::vec3(0.2f) });
		std::cout << "buffer resized\n";
		bufferResized = true;
	}
}


int main()
{
	GLFWwindow* window = createWindow();
	Shader* shader = new Shader("./res/shaders/test_vertex.glsl", "./res/shaders/test_fragment.glsl");

	GLDynamicBuffer<glm::vec3> dynamicBuffer(positions);
	//dynamicBuffer.addRange(positions);

	unsigned int VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, dynamicBuffer.getId());
	glEnableVertexArrayAttrib(VAO, 1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));

	glVertexAttribDivisor(1, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window, dynamicBuffer);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();
		glBindVertexArray(VAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, dynamicBuffer.size());
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}


/*
À FAIRE : 
	afficher le framerate
	Classe Chunk (en cours)
	Finir la classe GLBufferConfig
	Skybox
	Bloques destructibles

BUG :
	La limite de framerate dans la fonction run de CMWindow marche pas 
*/
