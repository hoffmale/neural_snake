
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

//Matrix::Matrix(Matrix const& source)
//{
//	for (int i = 0; i < source.num_rows; ++i)
//	{
//		for (int j = 0; j < source.num_cols; ++j)
//		{
//			
//		}
//	}
//}

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

Matrix Matrix::add(Matrix const& matrix1, Matrix const& matrix2) const
{
	assert(num_rows == matrix1.num_rows && num_cols == matrix1.num_cols &&
		num_rows == matrix2.num_rows && num_cols == matrix2.num_cols);

	Matrix result(matrix1.num_rows, matrix1.num_cols);
	for (int i = 0; i < result.num_rows; ++i)
	{
		for (int j = 0; j < result.num_cols; ++j)
		{
			result.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::subtract(Matrix const& matrix1, Matrix const& matrix2) const
{
	assert(num_rows == matrix1.num_rows && num_cols == matrix1.num_cols &&
		num_rows == matrix2.num_rows && num_cols == matrix2.num_cols);

	Matrix result(matrix1.num_rows, matrix1.num_cols);
	for (int i = 0; i < result.num_rows; ++i)
	{
		for (int j = 0; j < result.num_cols; ++j)
		{
			result.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::multiply(Matrix const& matrix1, Matrix const& matrix2) const
{
	assert(num_rows == matrix1.num_rows && num_cols == matrix1.num_cols &&
		num_rows == matrix2.num_rows && num_cols == matrix2.num_cols);

	Matrix result(matrix2.num_rows, matrix2.num_cols);
	for (int i = 0; i < result.num_rows; ++i)
	{
		for (int j = 0; j < result.num_cols; ++j)
		{
			result.matrix[i][j] = matrix1.matrix[i][j] * matrix2.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::dot(Matrix const& matrix1) const
{
	assert(num_rows == matrix1.num_cols);
	int m_cols = matrix1.num_cols;
	double w = 0;
	Matrix result(matrix1.num_rows, m_cols);
	for (int i = 0; i < result.num_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			for (int k = 0; k < result.num_cols; ++k)
			{
				w += matrix[i][k] * matrix1.matrix[k][j];
			}
			result.matrix[i][j] = w;
		}
	}
	return result;
}

Matrix Matrix::transpose() const
{
	Matrix result(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			result.matrix[i][j] = matrix[j][i];
		}
	}
	return result;
}

Matrix Matrix::normalize(Matrix const& matrix1)
{
	Matrix result(matrix1.num_rows, matrix1.num_cols);
	for (int i = 0; i < result.num_rows; ++i)
	{
		double sum = 0;
		for (int j = 0; j < result.num_cols; ++j)
		{
			sum += matrix1.matrix[i][j];
		}
		for (int k = 0; k < num_cols; ++k)
		{
			result.matrix[i][k] = matrix1.matrix[i][k] / sum;
		}
	}
	return result;
}

Matrix Matrix::flatten(Matrix const& matrix1)
{
	Matrix result(matrix1.num_rows*matrix1.num_cols, 1);
	for (int i = 0; i < result.num_rows; ++i)
	{
		for (int j = 0; j < result.num_cols; ++j)
		{
			result.matrix[i*result.num_cols][j] = matrix[i][j]
		}
	}
	return result;
}

Matrix Matrix::apply_function(double(*function)(double)) const
{
	Matrix result(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			result.matrix[i][j] = (*function)(matrix[i][j]);
		}
	}
	return result;
}

void Matrix::fill()
{
	Matrix result(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			result.matrix[i][j] = 1 + i;
		}
	}
}

void Matrix::print() const {
	for (unsigned i = 0; i < matrix.size(); i++) {
		for (unsigned j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

