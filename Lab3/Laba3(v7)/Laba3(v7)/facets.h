#pragma once

#include <array>
#include <vector>

#include "graphics.h"
#include "matrix.h"
#include "model.h"

class Facets : public Model
{
public:
	Facets(std::vector<std::array<float, 3>> vertices, std::vector<std::vector<uint32_t>> faces);

	void Draw(Graphics &g);

private:
	std::vector<std::vector<uint32_t>> faces_;

	std::vector<std::array<float, 4>> planes_;
};
