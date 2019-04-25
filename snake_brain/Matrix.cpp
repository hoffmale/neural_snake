#include "Matrix.h"
#include <assert.h>
#include <random>


Matrix::Matrix() {}

Matrix::Matrix(int num_rows, int num_cols) :
	num_rows(num_rows),
	num_cols(num_cols),
	matrix(std::vector<std::vector<double>>(num_rows, std::vector<double>(num_cols)))
{
	std::uniform_real_distribution<double> unif(-1, 1);
	std::random_device rd;
	std::default_random_engine generator(rd());
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			double x = unif(generator);
			this->matrix[i][j] = x;
		}
	}
}

Matrix::Matrix(std::vector<std::vector<double>> const& matrix) :
	num_rows(matrix.size()),
	num_cols(matrix[0].size()),
	matrix(matrix) {}

void Matrix::set(int row, int column, double value)
{
	if (row < num_rows || column < num_cols)
		this->matrix[row][column] = value;
}

double Matrix::get(int row, int column)
{
	if (row >= num_rows || column >= num_cols)
		return (double)0;
	return this->matrix[row][column];
}

void Matrix::print()
{
	for (auto i = 0u; i < matrix.size(); ++i)
	{
		for (auto j = 0u; j < matrix[i].size(); ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}