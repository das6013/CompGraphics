#include "matrix.h"


//constructor rows and columnc
Matrix::Matrix(uint32_t _rows, uint32_t _columns)
	: std::vector<Row>(_rows, Row(_columns))
	, rows(_rows)
	, columns(_columns)
{

}

//conscructor matrix
Matrix::Matrix(std::initializer_list<Row> matrix)
	: std::vector<Row>(matrix)
	, rows(matrix.size())
	, columns(matrix.begin()->size())
{

}

//powe matrix
const Matrix Matrix::operator*(const Matrix &obj) const
{
	Matrix res(rows, obj.columns);

	for (uint32_t j = 0; j < res.rows; j++)
	{
		for (uint32_t i = 0; i < res.columns; i++)
		{
			for (uint32_t k = 0; k < columns; k++)
			{
				res[j][i] += (*this)[j][k] * obj[k][i];
			}
		}
	}

	return res;
}
