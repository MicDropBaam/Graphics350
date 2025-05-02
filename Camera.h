/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Camera.h>
Purpose: <To provide point of veiw through camera>
Language: <c++>
Platform: <Visual studio, window>
Project: <minji.kim, class CS350, Assignment 3, minji.kim_CS350_3>
Author: <Seraphina Kim, minji.kim, minji.kim>
Creation date: <March. 15th. 2019>
End Header --------------------------------------------------------*/

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

enum Cam_Moving 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Shader;

class Camera
{
public:

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), 
								glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
								float _yaw = YAW, float _pitch = PITCH);
	glm::mat4 GetViewMatrix();
	void Update(Shader* _shader);
	void ProcessKeyboard(Cam_Moving _direction, float _deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	void updateCameraVectors();

};
