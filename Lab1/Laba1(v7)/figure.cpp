#include <cmath>
#include <ranges>
#include <iostream>
#include "figure.h"
#include <vector>
using namespace std;

Figure::Figure(std::vector<std::array<int32_t, 2>> vertices, std::vector<std::array<uint32_t, 2>> edges)
	: vertices_(vertices.size(), 3)
	, edges_(edges)
{
	for (uint32_t j = 0; j < vertices_.size(); j++)
	{
		vertices_[j][0] = vertices[j][0];
		vertices_[j][1] = vertices[j][1];
		vertices_[j][2] = 1;
	}
}
// точка опоры
void Figure::SetPivot(uint32_t vertex)
{
	pivot_ = vertex;
}

//formula scale
void Figure::Scaling(float s1, float s2) 
{
	Matrix translation
	{
		{ s1, 0, 0 },
		{ 0, s2, 0 },
		{ 0, 0, 1 },
	};
	float offset_x = vertices_[pivot_][0];
	float offset_y = vertices_[pivot_][1];

	Translate(-offset_x, -offset_y);
	vertices_ = vertices_ * translation;
	Translate(offset_x, offset_y);
}

//formula sdviga 
void Figure::Translate(float x, float y)
{
	Matrix translation
	{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ x, y, 1 },
	};

	vertices_ = vertices_ * translation;
}


//rotate figure with matrix sin cos
void Figure::Rotate(float ang)
{
	ang *= pi / 180;

	float s = sin(ang);
	float c = cos(ang);

	Matrix rotation
	{
		{ c, s, 0 },
		{ -s, c, 0 },
		{ 0, 0, 1 },
	};

	float offset_x = vertices_[pivot_][0];
	float offset_y = vertices_[pivot_][1];

	Translate(-offset_x, -offset_y);
	vertices_ = vertices_ * rotation;
	Translate(offset_x, offset_y);

}

void Figure::Draw(Graphics &g)
{
	for (auto e : edges_)
	{
		g.DrawLine(vertices_[e[0]][0], vertices_[e[0]][1], vertices_[e[1]][0], vertices_[e[1]][1], RGB(255, 255, 255));
	}
	for (auto e : edges_)
	{
		g.DrawLine(vertices_[0][0], vertices_[0][1], vertices_[1][0], vertices_[1][1], RGB(0, 200, 0));
	}	
}

void Figure::DrawPoint(Graphics& g)
{
	for (auto e : edges_)
	{
		g.DrawLine(vertices_[e[0]][0], vertices_[e[0]][1], vertices_[e[1]][0], vertices_[e[1]][1], RGB(255, 255, 255));
	}
	for (auto e : edges_)
	{
		g.DrawLine(vertices_[0][0], vertices_[0][1], vertices_[1][0], vertices_[1][1], RGB(0, 200, 0));
	}
	g.SetPixel(vertices_[1][0], vertices_[1][1], RGB(0, 200, 0));
}
