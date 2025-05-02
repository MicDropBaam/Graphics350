/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Light.cpp>
Purpose: <To provide depends on depth>
Language: <c++>
Platform: <Visual studio, window>
Project: <minji.kim, class CS350, Assignment 3, minji.kim_CS350_3>
Author: <Seraphina Kim, minji.kim, minji.kim>
Creation date: <March. 15th. 2019>
End Header --------------------------------------------------------*/

#pragma once
#include "glm/glm.hpp"
#include "Shader.h"

class Light
{
public:

	Light() {};
	~Light() {}

	int sphere_max = 1;

	glm::vec3 color;
	glm::vec3 position[16] = { glm::vec3(0.0f,0.0f,0.0f)};

	glm::vec3 lightColor[16] = { 
								 glm::vec3(0.1f,0.3f,0.5f), //sphere1
								 glm::vec3(0.6f,0.2f,0.0f), //2
								 glm::vec3(0.3f,0.9f,0.7f), //3
								 glm::vec3(0.7f,0.5f,0.1f), //4
								 glm::vec3(0.0f,0.6f,0.4f), //5
								 glm::vec3(0.5f,0.5f,0.4f), //6
								 glm::vec3(0.5f,0.2f,0.8f), //7
								 glm::vec3(0.4f,0.1f,0.1f), //8
								 glm::vec3(0.0f,0.3f,0.1f), //9
								 glm::vec3(0.1f,0.0f,0.5f), //10
								 glm::vec3(0.2f,0.0f,0.2f), //11
								 glm::vec3(0.4f,0.5f,0.7f), //12
								 glm::vec3(0.7f,0.1f,0.1f), //13
								 glm::vec3(0.3f,0.5f,0.9f), //14										 
								 glm::vec3(0.2f,0.4f,0.8f), //15
								 glm::vec3(0.7f,0.4f,0.6f), //16
	};

	glm::vec3 ambient[16] = { glm::vec3(0.15f,0.15f,0.15f)};
	glm::vec3 diffuse[16] = { glm::vec3(0.2f,0.2f,0.2f)};
	glm::vec3 specular[16] = { glm::vec3(1.0f, 1.0f, 1.0f)};

	float inner_angle[16] = { 7.5f};
	float outer_angle[16] = { 15.5f};
	float falloff[16] = { 1.f};

	float linear = 0.7f;
	float quadratic = 1.8f;
	float constant = 1.0f;
	float maxBrightness[16];

	int lightType = 0;
	float radius[16];

	void Update(Shader* shader)
	{
		shader->SetVec3("FragColor", color);
		shader->SetInt("sphere_max", sphere_max);
		shader->SetInt("LightType", lightType);

		//Sphere1
		for (int i = 0; i < 16; i++)
		{
			maxBrightness[i] = std::fmaxf(std::fmaxf(lightColor[i].r, lightColor[i].g), lightColor[i].b);
			radius[i] = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness[i]))) / (2.0f * quadratic);

			std::string num = std::to_string(i);

			//PointLight
			if (lightType == 0)
			{
				shader->SetVec3("lightColor[" + num + "]", lightColor[i]);
				shader->SetVec3("pointLights[" + num + "].position", position[i]);
				shader->SetVec3("pointLights[" + num + "].ambient", ambient[i]);
				shader->SetVec3("pointLights[" + num + "].diffuse", diffuse[i]);
				shader->SetVec3("pointLights[" + num + "].specular", specular[i]);
				shader->SetFloat("pointLights[" + num + "].constant", constant);
				shader->SetFloat("pointLights[" + num + "].linear", linear);
				shader->SetFloat("pointLights[" + num + "].quadratic", quadratic);
				shader->SetFloat("pointLights[" + num + "].Radius", radius[i]);
			}
			else if (lightType == 1)//Direction Light
			{
				shader->SetVec3("lightColor[" + num + "]", lightColor[i]);
				shader->SetVec3("dirLight[" + num + "].position", position[i]);
				shader->SetVec3("dirLight[" + num + "].direction", position[i]);
				shader->SetVec3("dirLight[" + num + "].ambient", ambient[i]);
				shader->SetVec3("dirLight[" + num + "].diffuse", diffuse[i]);
				shader->SetVec3("dirLight[" + num + "].specular", specular[i]);
			}
			else if (lightType == 2)//Spot Light
			{
				shader->SetVec3("spotLight[" + num + "].position", position[i]);
				shader->SetVec3("spotLight[" + num + "].direction", -position[i]);
				shader->SetVec3("spotLight[" + num + "].ambient", ambient[i]);
				shader->SetVec3("spotLight[" + num + "].diffuse", diffuse[i]);
				shader->SetVec3("spotLight[" + num + "].specular", specular[i]);
				shader->SetFloat("spotLight[" + num + "].constant", constant);
				shader->SetFloat("spotLight[" + num + "].linear", linear);
				shader->SetFloat("spotLight[" + num + "].quadratic", quadratic);
				shader->SetFloat("spotLight[" + num + "].cutOff", glm::cos(glm::radians(inner_angle[i])));
				shader->SetFloat("spotLight[" + num + "].outerCutOff", glm::cos(glm::radians(outer_angle[i])));
				shader->SetFloat("spotLight[" + num + "].falloff", falloff[i]);
				shader->SetFloat("spotLight[" + num + "].Radius", radius[i]);
			}
		}
	}
};