/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <BVHtree.h>
Purpose: <A set of geometric objects that is a boundary volume hierarchy>
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

enum TreeType { NODE, LEAF };

struct Node
{
	//Node for the tree
	struct Node *pRoot;
	struct Node *pLeft = 0;
	struct Node *pRight = 0;

	TreeType tree_type;

	std::vector<Rendering> objects;
	glm::vec3 bv_scale;
	glm::vec3 bv_scale_circle;
	glm::vec3 bv_mid;

	void DrawBox(int depth, Rendering* mod, Camera* camera, Shader* shader,
		float aspect, bool isUseBV, bool isUseRotation, int drawType);

	int numbOBJ;
	int tree_depth;
};

class Tree
{
public:

	void ComputeBV(std::vector<glm::vec3>& obj, glm::vec3& mid, glm::vec3& scale, glm::vec3& scale_circle);
	void PartObj(std::vector<glm::vec3>& obj, std::vector<glm::vec3>& left, std::vector<glm::vec3>& right, glm::vec3 &middle);
	void TopDownBV(Node **tree, std::vector<glm::vec3>& obj, int depth);

	float model_xMax = -FLT_MAX, model_xMin = FLT_MAX, model_yMax = -FLT_MAX, model_yMin = FLT_MAX, model_zMin = FLT_MAX, model_zMax = -FLT_MAX;
	float dist_x = 0, dist_y = 0, dist_z = 0;

	float modelVert_xmax = 0, modelVert_xmin = 0, 
		  modelVert_ymax = 0, modelVert_ymin = 0,
		  modelVert_zmax = 0, modelVert_zmin = 0;

	float longest_dis = 0;
	float xMid = 0, yMid = 0, zMid = 0;

};