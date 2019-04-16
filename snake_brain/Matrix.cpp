
#include <algorithm>
#include <assert.h>
#include <sstream>
#include "Matrix.h"


Matrix::Matrix(int num_rows, int num_cols) :
	num_rows(num_rows),
	num_cols(num_cols),
	matrix(std::vector<std::vector<double>>(num_rows, std::vector<double>(num_cols))) {}

Matrix::Matrix(std::vector<std::vector<double>> const& matrix) :
	num_rows(matrix.size()),
	num_cols(matrix[0].size()),
	matrix(matrix) {}

Matrix::Matrix(Matrix const& source)
{
	for (int i = 0; i < source.num_rows; ++i)
	{
		for (int j = 0; j < source.num_cols; ++j)
		{

		}
	}
}

Matrix Matrix::multiply(double const& c) const
{
	Matrix result(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			result.matrix[i][j] = matrix[i][j] * c;
		}
	}
	return result;
}