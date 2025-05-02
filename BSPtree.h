/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <BSPtree.h>
Purpose: <Recursively subdividing a binary space partitioning>
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

struct BSPNode
{
	BSPNode(std::vector<Triangle>& polygons) 
	{
		m_polygons = polygons;
	};
	BSPNode* m_front;
	BSPNode* m_back;
	std::vector<Triangle> m_polygons;
};

struct Plane
{
	glm::vec3 normal; 
	float dot;
};

enum Point_
{
	POINT_IN_FRONT_OF_PLANE,
	POINT_BEHIND_PLANE,
	POINT_ON_PLANE
};

enum Plane_
{
	COPLANAR_WITH_PLANE,
	IN_FRONT_OF_PLANE,
	BEHIND_PLANE,
	STRADDLING_PLANE
};

BSPNode *BSPTree(std::vector<Triangle>& polygons, std::vector<Rendering*>& mod, int depth,
	std::vector<int>& obj_index, std::vector<std::vector<unsigned>>& obj_indices);
Plane DecidePalne(std::vector<Triangle> &polygons);
Plane GetPlaneFromPolygon(Triangle poly);
int ClassifyPointToPlane(glm::vec3 p, Plane plane);
int ClassifyPolygonToPlane(Triangle poly, Plane plane);