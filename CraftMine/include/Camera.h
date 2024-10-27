#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>

#include "Parameters.h"

#define PI 3.141592653589793238462643383279502884L 



typedef struct {
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;
} CameraVectors;



class Camera
{
private:
	double yawValue = 0.0f, pitchValue = 0.0f, rollValue = 0.0f;
	int lastX = -1, lastY = -1, xOffset, yOffset;
	glm::vec3 position;
	
	CameraVectors vectors{
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0),
	};

	glm::mat4 viewMatrix;

	void computeVectors();
	void rebuildViewMatrix();
	void computeDirection();

public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 pointToLook);
	Camera(const Camera&) = delete;

	~Camera();

	Camera& operator = (const Camera&) = delete;

	void move(glm::vec3 newLocation);
	void lookAt(glm::vec3 pointToLookAt);

	// les valeurs positives bougent la camera vers le haut et les négatives vers le bas
	void moveUpward(float offset);
	// les valeurs positives bougent la camera vers la droite et les négatives vers la gauche
	void moveSideWays(float offset);
	// les valeurs positives bougent la camera vers l'avant et les négatives vers l'arrière
	void moveForward(float offset);

	void yaw(float angleInRadians);
	void pitch(float angleInRadians);
	void roll(float angleInRadians);

	void proccessMouse(int x, int y);

	float getYaw() const;
	float getPitch() const;
	float getRoll() const;
	CameraVectors getVectors() const;
	glm::mat4 getViewMatrix() const;
	glm::vec3 getPosition() const;
};
