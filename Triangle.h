/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Triangle.h>
Purpose: <Helper h.file for the triangle to draw dot of triangle>
Language: <c++>
Platform: <Visual studio, window>
Project: <minji.kim, class CS350, Assignment 3, minji.kim_CS350_3>
Author: <Seraphina Kim, minji.kim, minji.kim>
Creation date: <March. 15th. 2019>
End Header --------------------------------------------------------*/
#pragma once
#include "glm/glm.hpp"

class Triangle
{
public:
	glm::vec3 pt[3];
	glm::vec3 normal;
};