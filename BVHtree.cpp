/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <BVHtree.cpp>
Purpose: <A set of geometric objects that is a boundary volume hierarchy>
Language: <c++>
Platform: <Visual studio, window>
Project: <minji.kim, class CS350, Assignment 3, minji.kim_CS350_3>
Author: <Seraphina Kim, minji.kim, minji.kim>
Creation date: <March. 15th. 2019>
End Header --------------------------------------------------------*/
#include "BVHtree.h"
#include <iostream>

void Tree::ComputeBV(std::vector<glm::vec3>& obj, glm::vec3& mid, glm::vec3& scale, glm::vec3& scale_circle)
{
	model_xMax = -100, model_xMin = 100, 
	model_yMin = 100, model_yMax = -100,
	model_zMin = 100, model_zMax = -100;

	dist_x = 0; dist_y = 0; dist_z = 0;

	for (unsigned int i = 0; i < obj.size(); i++)
	{
		if (obj[i].x > model_xMax)
			model_xMax = obj[i].x;
		if (obj[i].x < model_xMin)
			model_xMin = obj[i].x;
		if (obj[i].y > model_yMax)
			model_yMax = obj[i].y;
		if (obj[i].y < model_yMin)
			model_yMin = obj[i].y;
		if (obj[i].z > model_zMax)
			model_zMax = obj[i].z;
		if (obj[i].z < model_zMin)
			model_zMin = obj[i].z;
	}

	dist_x = glm::abs(model_xMax - model_xMin);
	dist_y = glm::abs(model_yMax - model_yMin);
	dist_z = glm::abs(model_zMax - model_zMin);

	if (dist_x > dist_y && dist_x > dist_z)
	{
		longest_dis = dist_x;
	}
	else if (dist_y > dist_x && dist_y > dist_z)
	{
		longest_dis = dist_y;
	}
	else if (dist_z > dist_x && dist_z > dist_y)
	{
		longest_dis = dist_z;
	}

	scale = glm::vec3(dist_x, dist_y, dist_z)*0.5f;
	scale_circle = glm::vec3(longest_dis, longest_dis, longest_dis) * 0.5f;

	mid = glm::vec3((model_xMax + model_xMin), (model_yMax + model_yMin), (model_zMax + model_zMin))*0.5f;
}

void Tree::PartObj(std::vector<glm::vec3>& obj, std::vector<glm::vec3>& left, std::vector<glm::vec3>& right, glm::vec3 &middle)
{
	glm::vec3 mid(0);
	
	//x
	if (longest_dis > dist_y && longest_dis > dist_z)
	{
		mid.x = middle.x;
		for (unsigned int i = 0; i < obj.size(); i++)
		{
			if (obj[i].x < mid.x)
			{
				left.push_back(obj[i]);
			}
			else
			{
				right.push_back(obj[i]);
			}
		}
	}
	//y
	else if (longest_dis > dist_x && longest_dis > dist_z)
	{
		mid.y = middle.y;
		for (unsigned int i = 0; i < obj.size(); i++)
		{
			if (obj[i].y < mid.y)
			{
				left.push_back(obj[i]);
			}
			else
			{
				right.push_back(obj[i]);
			}
		}
	}
	//z
	else if (longest_dis > dist_x && longest_dis > dist_y)
	{
		mid.z = middle.z;
		for (unsigned int i = 0; i < obj.size(); i++)
		{
			if (obj[i].z < mid.z)
			{
				left.push_back(obj[i]);
			}
			else
			{
				right.push_back(obj[i]);
			}
		}
	}
}

void Tree::TopDownBV(Node **tree, std::vector<glm::vec3>& obj, int depth)
{
	if (depth > 7)
	{
		return;
	}

	const int MIN_OBJECTS_PER_LEAF = 500;
	Node *pNode = new Node;
	*tree = pNode;

	ComputeBV(obj, pNode->bv_mid, pNode->bv_scale, pNode->bv_scale_circle);
	pNode->tree_depth = depth;
	pNode->numbOBJ = obj.size();

	if (pNode->numbOBJ <= MIN_OBJECTS_PER_LEAF)
	{
		pNode->tree_type = LEAF;
	}
	else
	{
		pNode->tree_type = NODE;
		std::vector<glm::vec3> left;
		std::vector<glm::vec3> right;

		PartObj(obj, left, right, pNode->bv_mid);

		TopDownBV(&(pNode->pLeft), left, depth + 1);
		TopDownBV(&(pNode->pRight), right, depth + 1);
	}
}

void Node::DrawBox(int depth, Rendering* mod, Camera * camera, Shader * shader, float aspect, bool isUseBV, bool isUseRotation, int drawType)
{
	mod->position = bv_mid;

	if (drawType == 0)
		mod->scale = bv_scale;
	else if (drawType == 1)
		mod->scale = bv_scale_circle * 1.1f;

	switch (depth)
	{
		case 1:
			mod->color = glm::vec3(1.f, 0.1f, 0.1f);
			break;
		case 2:
			mod->color = glm::vec3(1.f, 0.5f, 0.2f);
			break;
		case 3:
			mod->color = glm::vec3(1.f, 1.f, 0.5f);
			break;
		case 4:
			mod->color = glm::vec3(0.3f, 0.7f, 0.2f);
			break;
		case 5:
			mod->color = glm::vec3(0.3f, 0.6f, 0.9f);
			break;
		case 6:
			mod->color = glm::vec3(0.2f, 0.4f, 1.f);
			break;
		case 7:
			mod->color = glm::vec3(0.6f, 0.2f, 1.f);
			break;
		default:
			break;
	}

	if (depth == tree_depth)
	{
		mod->Render(camera, shader, aspect, mod->position, isUseBV, isUseRotation);
	}
	else
	{
		if (pLeft != nullptr)
			pLeft->DrawBox(depth, mod, camera, shader, aspect, isUseBV, isUseRotation, drawType);
		if (pRight != nullptr)
			pRight->DrawBox(depth, mod, camera, shader, aspect, isUseBV, isUseRotation, drawType);
	}
}
