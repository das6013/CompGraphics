#pragma once

#include "model.h"

class Wireframe : public Model
{
public:
	Wireframe(std::vector<std::array<float, 3>> vertices, std::vector<std::array<uint32_t, 2>> edges);

	void Draw(Graphics &g);

private:
	std::vector<std::array<uint32_t, 2>> edges_;
};
