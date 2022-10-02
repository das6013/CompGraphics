#include <cmath>
#include <ranges>

#include "model.h"

Model::Model(std::vector<std::array<float, 3>> vertices)
	: vertices_(vertices.size(), 4)
{
	for (uint32_t j = 0; j < vertices_.size(); j++)
	{
		vertices_[j][0] = vertices[j][0];
		vertices_[j][1] = vertices[j][1];
		vertices_[j][2] = vertices[j][2];
		vertices_[j][3] = 1;
	}
}

void Model::Translate(float x, float y, float z)
{
	Matrix translation
	{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ x, y, z, 1 },
	};

	vertices_ = vertices_ * translation;
}

void Model::Rotate(float roll, float yaw, float pitch)
{
	float s, c;

	// roll
	roll *= pi / 180;

	s = sin(roll);
	c = cos(roll);

	Matrix R_x
	{
		{ 1, 0, 0, 0 },
		{ 0, c, -s, 0 },
		{ 0, s, c, 0 },
		{ 0, 0, 0, 1 },
	};

	// yaw
	yaw *= pi / 180;

	s = sin(yaw);
	c = cos(yaw);

	Matrix R_y
	{
		{ c, 0, s, 0 },
		{ 0, 1, 0, 0 },
		{ -s, 0, c, 0 },
		{ 0, 0, 0, 1 },
	};

	// pitch
	pitch *= pi / 180;

	s = sin(pitch);
	c = cos(pitch);

	Matrix R_z
	{
		{ c, -s, 0, 0 },
		{ s, c, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 },
	};

	vertices_ = vertices_ * R_x * R_y * R_z;
}
