/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <OCtree.cpp>
Purpose: <Each internal node has exactly eight children by recursively subdividing.>
Language: <c++>
Platform: <Visual studio, window>
Project: <minji.kim, class CS350, Assignment 3, minji.kim_CS350_3>
Author: <Seraphina Kim, minji.kim, minji.kim>
Creation date: <March. 15th. 2019>
End Header --------------------------------------------------------*/

#include "OCtree.h"
#include <iostream>

OctreeNode* Octree(std::vector<Rendering*> mod, glm::vec3 center, float halfWidth, int stopdepth)
{
	float R_ = (rand() % 100) / 100.f;
	float G_ = (rand() % 100) / 100.f;
	float B_ = (rand() % 100) / 100.f;
	glm::vec3 color(R_, G_, B_);
	switch (stopdepth)
	{
		case 1:
			color = glm::vec3(R_, G_, B_);
			break;
		case 2:
			color = glm::vec3(R_, G_, B_);
			break;
		case 3:
			color = glm::vec3(R_, G_, B_);
			break;
		case 4:
			color = glm::vec3(R_, G_, B_);
			break;
		case 5:
			color = glm::vec3(R_, G_, B_);
			break;
		case 6:
			color = glm::vec3(R_, G_, B_);
			break;
		case 7:
			color = glm::vec3(R_, G_, B_);
			break;
		case 8:
			color = glm::vec3(R_, G_, B_);
			break;
		default:
			break;
	}

	int num_tri = GetTriangle(mod, center, halfWidth, color);
	if (num_tri < 300 || stopdepth < 0)
		return nullptr;

	// Construction
	OctreeNode *pNode = new OctreeNode;
	pNode->oc_center = center;
	pNode->oc_width = halfWidth;
	pNode->pObjList = NULL;

	// Contruct sub tree recursively
	glm::vec3 offset;
	float step = halfWidth * 0.5f;
	for (int i = 0; i < 8; i++) 
	{
		offset.x = ((i & 1) ? step : -step);
		offset.y = ((i & 2) ? step : -step);
		offset.z = ((i & 4) ? step : -step);
		pNode->pChild[i] = Octree(mod, center + offset, step, stopdepth - 1);
	}
	return pNode;
}

void OctreeNode::DrawBox(Rendering* mod, Camera* camera, Shader* shader,
	float aspect, bool isUseBV, bool isUseRotation, int stopdepth)
{
	mod->position = oc_center;
	mod->scale = glm::vec3(oc_width, oc_width, oc_width);

	float R_ = (rand() % 100) / 100.f;
	float G_ = (rand() % 100) / 100.f;
	float B_ = (rand() % 100) / 100.f;
	glm::vec3 color(R_, G_, B_);
	switch (stopdepth)
	{
		case 1:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 2:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 3:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 4:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 5:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 6:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 7:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		case 8:
			mod->color = glm::vec3(R_, G_, B_);
			break;
		default:
			break;
	}

	mod->Render(camera, shader, aspect, mod->position, isUseBV, isUseRotation);
	for (int i = 0; i < 8; ++i)
	{
		if (pChild[i])
			pChild[i]->DrawBox(mod, camera, shader, aspect, isUseBV, isUseRotation, stopdepth - 1);
	}
}

int GetTriangle(std::vector<Rendering*> mod, glm::vec3& center, float& halfWidth, glm::vec3 color)
{
	float range = halfWidth;
	int triangleNum = 0;
	glm::vec3 p1(0), p2(0), p3(0);
	for (unsigned int i = 0; i < mod.size(); i++)
	{
		for (unsigned int j = 0; j < mod[i]->vertex_indices.size(); j += 3)
		{
			bool in_1 = false, in_2 = false, in_3 = false;
			p1 = mod[i]->out_vertices[mod[i]->vertex_indices[j]] + mod[i]->position;
			p2 = mod[i]->out_vertices[mod[i]->vertex_indices[j + 1]] + mod[i]->position;
			p3 = mod[i]->out_vertices[mod[i]->vertex_indices[j + 2]] + mod[i]->position;

			if (p1.x <= center.x + range && p1.x >= center.x - range
				&& p1.y <= center.y + range && p1.y >= center.y - range
				&& p1.z <= center.z + range && p1.z >= center.z - range)
			{
				in_1 = true;
				mod[i]->octree_color[mod[i]->vertex_indices[j]] = color;
			}
			if (p2.x <= center.x + range && p2.x >= center.x - range
				&& p2.y <= center.y + range && p2.y >= center.y - range
				&& p2.z <= center.z + range && p2.z >= center.z - range)
			{
				in_2 = true;
				mod[i]->octree_color[mod[i]->vertex_indices[j + 1]] = color;
			}
			if (p3.x <= center.x + range && p3.x >= center.x - range
				&& p3.y <= center.y + range && p3.y >= center.y - range
				&& p3.z <= center.z + range && p3.z >= center.z - range)
			{
				in_3 = true;
				mod[i]->octree_color[mod[i]->vertex_indices[j + 2]] = color;
			}
			if (in_1 == true && in_2 == true && in_3 == true)
				triangleNum++;
		}
	}
	return triangleNum;
}

glm::vec3 GetCenter(std::vector<Rendering*> mod)
{
	glm::vec3 mid(0);
	float mod_xMax = -100, mod_xMin = 100, 
			mod_yMin = 100, mod_yMax = -100,
			mod_zMin = 100, mod_zMax = -100;
	float x_dist = 0, y_dist = 0, z_dist = 0;
	float dis = 0;

	for (unsigned int i = 0; i < mod.size(); i++)
	{
		if (mod[i]->position.x > mod_xMax)
			mod_xMax = mod[i]->position.x + mod[i]->aabb().x;
		if (mod[i]->position.x < mod_xMin)
			mod_xMin = mod[i]->position.x - mod[i]->aabb().x;
		if (mod[i]->position.y > mod_yMax)
			mod_yMax = mod[i]->position.y + mod[i]->aabb().y;
		if (mod[i]->position.y < mod_yMin)
			mod_yMin = mod[i]->position.y - mod[i]->aabb().y;
		if (mod[i]->position.z > mod_zMax)
			mod_zMax = mod[i]->position.z + mod[i]->aabb().z;
		if (mod[i]->position.z < mod_zMin)
			mod_zMin = mod[i]->position.z - mod[i]->aabb().z;
	}

	mid = glm::vec3((mod_xMax + mod_xMin), (mod_yMax + mod_yMin), (mod_zMax + mod_zMin))*0.5f;
	x_dist = glm::abs(mod_xMax - mod_xMin);
	y_dist = glm::abs(mod_yMax - mod_yMin);
	z_dist = glm::abs(mod_zMax - mod_zMin);

	if (x_dist > y_dist && x_dist > z_dist)
		dis = x_dist;
	else if (y_dist > x_dist && y_dist > y_dist)
		dis = y_dist;
	else if (z_dist > x_dist && z_dist > y_dist)
		dis = z_dist;

	return mid;
}

float GetLongest(std::vector<Rendering*> mod)
{
	glm::vec3 mid(0);
	float mod_xMax = -100, mod_xMin = 100, 
		  mod_yMin = 100, mod_yMax = -100,
		  mod_zMin = 100, mod_zMax = -100;
	float x_dist = 0, y_dist = 0, z_dist = 0;
	float dist = 0;

	for (unsigned int i = 0; i < mod.size(); i++)
	{
		if (mod[i]->position.x > mod_xMax)
			mod_xMax = mod[i]->position.x + mod[i]->aabb().x;
		if (mod[i]->position.x < mod_xMin)
			mod_xMin = mod[i]->position.x - mod[i]->aabb().x;
		if (mod[i]->position.y > mod_yMax)
			mod_yMax = mod[i]->position.y + mod[i]->aabb().y;
		if (mod[i]->position.y < mod_yMin)
			mod_yMin = mod[i]->position.y - mod[i]->aabb().y;
		if (mod[i]->position.z > mod_zMax)
			mod_zMax = mod[i]->position.z + mod[i]->aabb().z;
		if (mod[i]->position.z < mod_zMin)
			mod_zMin = mod[i]->position.z - mod[i]->aabb().z;
	}

	mid = glm::vec3((mod_xMax + mod_xMin), (mod_yMax + mod_yMin), (mod_zMax + mod_zMin))*0.5f;
	x_dist = glm::abs(mod_xMax - mod_xMin);
	y_dist = glm::abs(mod_yMax - mod_yMin);
	z_dist = glm::abs(mod_zMax - mod_zMin);

	if (x_dist > y_dist && x_dist > z_dist)
		dist = x_dist;
	else if (y_dist > x_dist && y_dist > y_dist)
		dist = y_dist;
	else if (z_dist > x_dist && z_dist > y_dist)
		dist = z_dist;

	return dist * 0.5f;
}


