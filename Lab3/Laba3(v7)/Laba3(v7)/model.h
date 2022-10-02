#pragma once

#include <array>
#include <vector>

#include "graphics.h"
#include "matrix.h"
#include "camera.h"

class Model
{
public:
	Model(std::vector<std::array<float, 3>> vertices);

	void Translate(float x, float y, float z);
	void Rotate(float roll, float pitch, float yaw);

	virtual void Draw(Graphics &g) = 0;

protected:
	Matrix vertices_;
};
