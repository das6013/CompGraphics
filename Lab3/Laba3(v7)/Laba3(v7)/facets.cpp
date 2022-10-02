#define _USE_MATH_DEFINES

#include <math.h>

#include "facets.h"

Facets::Facets(std::vector<std::array<float, 3>> vertices, std::vector<std::vector<uint32_t>> faces)
	: Model(vertices)
	, faces_(faces)
	, planes_(faces_.size())
{
	Matrix &v = vertices_;

	// mass center
	std::array<float, 3> c{};

	for (uint8_t i = 0; i < 3; i++)
	{
		for (auto &row : vertices_)
		{
			c[i] += row[i];
		}

		c[i] /= v.size();
	}

	// plane equation
	for (uint32_t j = 0; j < faces_.size(); j++)
	{
		auto &f = faces_[j];
		auto &p = planes_[j];

		p[0] = (v[f[2]][1] - v[f[0]][1]) * (v[f[1]][2] - v[f[0]][2]) - (v[f[1]][1] - v[f[0]][1]) * (v[f[2]][2] - v[f[0]][2]);
		p[1] = (v[f[1]][0] - v[f[0]][0]) * (v[f[2]][2] - v[f[0]][2]) - (v[f[2]][0] - v[f[0]][0]) * (v[f[1]][2] - v[f[0]][2]);
		p[2] = (v[f[2]][0] - v[f[0]][0]) * (v[f[1]][1] - v[f[0]][1]) - (v[f[1]][0] - v[f[0]][0]) * (v[f[2]][1] - v[f[0]][1]);
		p[3] = -(p[0] * v[f[0]][0] + p[1] * v[f[0]][1] + p[2] * v[f[0]][2]);

		if (p[0] * c[0] + p[1] * c[1] + p[2] * c[2] + p[3] < 0)
		{
			p[0] = -p[0];
			p[1] = -p[1];
			p[2] = -p[2];
			p[3] = -p[3];
		}
	}
}

void Facets::Draw(Graphics &g)
{
	Matrix vertices = vertices_ * Camera::view() * Camera::projection();

	for (uint32_t j = 0; j < faces_.size(); j++)
	{
		auto &f = faces_[j];
		auto &p = planes_[j];

		if (p[0] * Camera::x() + p[1] * Camera::y() + p[2] * Camera::z() < 0)
		{
			std::vector<std::array<float, 2>> points(f.size());

			for (uint32_t i = 0; i < f.size(); i++)
			{
				points[i][0] = vertices[f[i]][0];
				points[i][1] = vertices[f[i]][1];
			}

			uint8_t color = 50 + 150 * (j + 1) / faces_.size();

			g.DrawPoly(points, RGB(color, color, color));
		}
	}
}
