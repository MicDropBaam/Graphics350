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
