/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <OCtree.h>
Purpose: <Each internal node has exactly eight children by recursively subdividing.>
Language: <c++>
Platform: <Visual studio, window>
Project: <minji.kim, class CS350, Assignment 3, minji.kim_CS350_3>
Author: <Seraphina Kim, minji.kim, minji.kim>
Creation date: <March. 15th. 2019>
End Header --------------------------------------------------------*/
#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <math.h>
#include "Render.h"
#include "Camera.h"
#include "Shader.h"

struct OctreeNode
{
	OctreeNode() {}
	glm::vec3 oc_center;
	float oc_width; // Half the width of the node volume
	
	OctreeNode *pChild[8];
	Rendering *pObjList;
	
	void DrawBox(Rendering* mod, Camera* camera, Shader* shader,
		float aspect, bool isUseBV, bool isUseRotation, int stopdepth);
};

struct Object
{
	glm::vec3 center; // Center point
	Rendering *pNextObject;
};

OctreeNode* Octree(std::vector<Rendering*> mod, glm::vec3 center, float halfWidth, int stopdepth);
glm::vec3 GetCenter(std::vector<Rendering*> mod);
int GetTriangle(std::vector<Rendering*> mod, glm::vec3& center, float& halfWidth, glm::vec3 color);
float GetLongest(std::vector<Rendering*> mod);
