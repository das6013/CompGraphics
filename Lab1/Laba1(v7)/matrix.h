#pragma once

#include <vector>
#include <numbers>

typedef std::vector<float> Row;

const float pi = 3.14;

class Matrix : public std::vector<std::vector<float>>
{
public:
	Matrix(uint32_t _rows, uint32_t _columns);
	Matrix(std::initializer_list<std::vector<float>> matrix);

	const Matrix operator*(const Matrix &obj) const;

private:
	uint32_t rows;
	uint32_t columns;
};
