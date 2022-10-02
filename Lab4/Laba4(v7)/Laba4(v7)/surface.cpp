#include <cmath>
#include <algorithm>
#include <array>

#include "surface.h"

Surface::Surface(float x_min, float x_max, float z_min, float z_max, float (*equation)(float x, float z))
	: corners_
	{
		{ x_min, 0, z_min, 1 },
		{ x_max, 0, z_min, 1 }, // поверхность с областью определения
		{ x_min, 0, z_max, 1 },
		{ x_max, 0, z_max, 1 },
	}
	, rotation_(4, 4)
	, vertices_(steps_ * steps_, 4)
{
	uint32_t v = 0;

	float z = z_min;

	for (int32_t j = 0; j < steps_; j++)
	{
		float x = x_min;

		for (int32_t i = 0; i < steps_; i++)
		{
			vertices_[v][0] = x;
			vertices_[v][1] = equation(x, z);
			vertices_[v][2] = z;
			vertices_[v][3] = 1;

			v++;

			x += (x_max - x_min) / steps_;
		}

		z += (z_max - z_min) / steps_;
	}
}

// roll < 90
// pitch > -90
void Surface::SetAngles(float roll, float pitch)
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

	// pitch
	pitch *= pi / 180;

	s = sin(pitch);
	c = cos(pitch);

	Matrix R_y
	{
		{ c, 0, s, 0 },
		{ 0, 1, 0, 0 },
		{ -s, 0, c, 0 },
		{ 0, 0, 0, 1 },
	};

	rotation_ = R_y * R_x;
}

const Matrix Surface::Scale(const Matrix &vertices)
{
	Matrix corners = corners_ * rotation_;

	float norm_x = abs((*std::max_element(corners.begin(), corners.end(), [](const Row &a, const Row &b) { return abs(a[0]) < abs(b[0]); }))[0]);
	float norm_y = abs((*std::max_element(vertices.begin(), vertices.end(), [](const Row &a, const Row &b) { return abs(a[1]) < abs(b[1]); }))[1]);

	float k = std::min(Graphics::width / 2 / norm_x, Graphics::height / 2 / norm_y) - 1.0f;

	return vertices * Matrix
	{
		{ 100, 0, 0, 0 },
		{ 0, 100, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 1 },
	};
}

void Surface::Draw(Graphics &g)
{
	Matrix vertices = Scale(vertices_ * rotation_) * Camera::projection();

	// horizon
	std::array<int32_t, Graphics::width> upper;
	std::array<int32_t, Graphics::width> lower;

	upper.fill(Graphics::height - 1);
	lower.fill(0);

	std::array<int32_t, Graphics::width> upper_n(upper);
	std::array<int32_t, Graphics::width> lower_n(lower);

	// point
	int32_t x0, y0, x1, y1;
	bool flag_p, flag;

	// processing
	uint32_t v = 0;

	for (int32_t z = 0; z < steps_; z++)
	{

		for (int32_t x = 0; x < steps_; x++)
		{
			// current point
			x1 = round(vertices[v][0]);
			y1 = round(vertices[v][1]);

			flag = y1 < upper[x1] || y1 > lower[x1];

			// correct
			if (x != 0 && (flag_p || flag))
			{
				int32_t dx = abs(x1 - x0); // delta x
				int32_t xi = x0 < x1 ? 1 : -1; // x increment

				int32_t dy = -abs(y1 - y0);
				int32_t yi = y0 < y1 ? 1 : -1;

				int32_t de = dx + dy; // delta error

				while (true)
				{
					uint8_t flag = 0b00;

					if (upper[x0] > y0)
					{
						upper_n[x0] = y0;

						flag |= 0b01;
					}

					if (lower[x0] < y0)
					{
						lower_n[x0] = y0;

						flag |= 0b10;
					}

					if (flag == 0b11)
					{
						g.SetPixel(x0, y0, RGB(0, 200, 0)); // section
					}
					else if (flag & 0b01)
					{
						g.SetPixel(x0, y0, RGB(200, 200, 200)); // upper
					}
					else if (flag & 0b10)
					{
						g.SetPixel(x0, y0, RGB(0, 200, 200)); // lower
					}

					if (x0 == x1 && y0 == y1) break;

					int32_t de2 = 2 * de;

					if (de2 >= dy)
					{
						de += dy;
						x0 += xi;
					}

					if (de2 <= dx)
					{
						de += dx;
						y0 += yi;
					}
				}
			}
			else
			{
				x0 = x1;
				y0 = y1;
			}

			flag_p = flag;

			v++;
		}

		upper = upper_n;
		lower = lower_n;
	}

	// draw horizon
	//for (int32_t x = 0; x < Graphics::width; x++)
	//{
	//	g.SetPixel(x, upper[x], RGB(0, 200, 200));
	//	g.SetPixel(x, lower[x], RGB(200, 0, 200));
	//}
}

