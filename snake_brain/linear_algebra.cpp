#include "Matrix.h"
#include "Utility.h"
#include <assert.h>


namespace np
{
	// Scalar multiplication
	Matrix multiply(Matrix& mat1, double c)
	{
		Matrix result(mat1.get_rows(), mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_rows(); ++j)
			{
				result.set(i, j, mat1.get(i, j) * c);
			}
		}
		return result;
	}

	// Hadamard product of matrices
	Matrix multiply(Matrix& mat1, Matrix& mat2, int slice)
	{
		assert(mat1.get_rows() == mat2.get_rows() && mat1.get_columns() == mat2.get_columns() - slice);
		Matrix result(mat2.get_rows(), mat2.get_columns() - slice);
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_rows(); ++j)
			{
				result.set(i, j, mat1.get(i, j) * mat2.get(i, j));
			}
		}
		return result;
	}

	// Hadamard product of vectors
	std::vector<double> multiply(std::vector<double>& vec1, std::vector<double>& vec2)
	{
		assert(vec1.size() == vec2.size());
		std::vector<double> result;
		for (auto i = 0u; i < vec1.size(); ++i)
		{
			result.push_back(vec1[i] * vec2[i]);
		}
		return result;
	}

	// Take dot product and sum all elements
	double multiply(Matrix& mat1, Matrix& mat2, int xslice, int yslice)
	{
		assert(mat2.get_rows() >= mat1.get_rows && mat2.get_columns() >= mat1.get_columns());
		double sum = 0;
		for (auto i = 0; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0; j < mat1.get_columns(); ++j)
			{
				sum += (mat1.get(i, j) * mat2.get(xslice + i, yslice + j));
			}
		}
		return sum;
	}

	// Dot products between two matrices
	Matrix dot(Matrix& mat1, Matrix& mat2, int slice)
	{
		assert(mat1.get_columns() == mat2.get_rows());

		Matrix result(mat1.get_rows(), mat1.get_columns() - slice);
		for (auto i = 0u; i < result.get_rows(); ++i)
		{
			for (auto j = 0u; j < result.get_rows(); ++j)
			{
				double x = 0;
				for (std::size_t k = 0; k < mat1.get_columns(); ++k)
				{
					x += (mat1.get(i, k) * mat2.get(k, j));
				}
				result.set(i, j, x);
			}
		}
		return result;
	}

	// Dot product of a matrix with a vector
	std::vector<double> dot(Matrix& mat1, std::vector<double>& vec1, int slice)
	{
		assert(mat1.get_columns() == vec1.size() - slice);
		std::vector<double> result;
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			double x = 0;
			for (auto j = 0u; j < mat1.get_columns() - slice; ++j)
			{
				x += (mat1.get(i, j) * vec1[j]);
			}
			result.push_back(x);
		}
		return result;
	}

	// Dot product of a 2 vectors
	double dot(std::vector<double>& vec1, std::vector<double>& vec2)
	{
		double result = 0;
		for (auto i = 0u; i < vec1.size(); ++i)
		{
			result += vec1[i] * vec2[i];
		}
		return result;
	}

	// Dot product of 2 vectors returning a Rank 1 Matrix
	Matrix dot(std::vector<double>& vec1, std::vector<double>& vec2, int slice)
	{
		Matrix mat(vec1.size(), vec2.size() - slice);
		for (int i = 0; i < mat.get_rows(); ++i)
		{
			for (int j = 0; j < mat.get_columns(); ++j)
			{
				mat.set(i, j, vec1[i] * vec2[j]);
			}
		}
		return mat;
	}

	// Add two matrices together
	Matrix add(Matrix& mat1, Matrix& mat2)
	{
		assert(mat1.get_rows() == mat2.get_rows() && mat1.get_columns() == mat2.get_columns());

		Matrix result(mat1.get_rows(), mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				result.set(i, j, mat1.get(i, j) + mat2.get(i, j));
			}
		}
		return result;
	}

	// Add two vectors
	std::vector<double> add(std::vector<double>& vec1, std::vector<double>& vec2)
	{
		assert(vec1.size() == vec2.size());

		std::vector<double> result;
		for (auto i = 0u; i < vec1.size(); ++i)
		{
			result.push_back(vec1[i] + vec2[i]);
		}
		return result;
	}

	// Subtract two matrices together
	Matrix subtract(Matrix& mat1, Matrix& mat2)
	{
		assert(mat1.get_rows() == mat2.get_rows() && mat1.get_columns() == mat2.get_columns());

		Matrix result(mat1.get_rows(), mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				result.set(i, j, mat1.get(i, j) - mat2.get(i, j));
			}
		}
		return result;
	}

	// Subtract two vectors
	std::vector<double> subtract(std::vector<double>& vec1, std::vector<double>& vec2)
	{
		assert(vec1.size() == vec2.size());

		std::vector<double> result;
		for (auto i = 0u; i < vec1.size(); ++i)
		{
			result.push_back(vec1[i] - vec2[i]);
		}
		return result;
	}

	// Transpose matrix
	Matrix transpose(Matrix& mat1)
	{
		Matrix result(mat1.get_rows(), mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				result.set(j, i, mat1.get(i, j));
			}
		}
		return result;
	}

	// Apply function to every element of matrix
	Matrix apply_function(Matrix& mat1, double(*function)(double))
	{
		Matrix result(mat1.get_rows(), mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				double val = (*function)(mat1.get(i, j));
				result.set(i, j, val);
			}
		}
		return result;
	}

	// Apply function to every element of the vector
	std::vector<double> apply_function(std::vector<double>& vec1, double(*function)(double))
	{
		std::vector<double> result;
		for (auto i = 0u; i < vec1.size(); ++i)
		{
			double val = (*function)(vec1[i]);
			result.push_back(val);
		}
		return result;
	}

	// Normalize a matrix such that the sum of each row is 1
	Matrix normalize(Matrix& mat1)
	{
		Matrix result(mat1.get_rows(), mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			double sum = 0;
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				sum += mat1.get(i, j);
			}
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				result.set(i, j, mat1.get(i, j) / sum);
			}
		}
		return result;
	}

	// Normalize a vector such that sum of each element is 1
	std::vector<double> normalize(std::vector<double>& vec1)
	{
		std::vector<double> result;
		double sum = 0;
		for (auto i = 0u; i < vec1.size(); ++i)
		{
			sum += vec1[i];
		}
		assert(sum != 0);
		for (auto i = 0u; i < vec1.size(); i++)
		{
			result.push_back(vec1[i] / sum);
		}
		return result;
	}

	// Flatten a 2D matrix to 1D vector
	std::vector<double> flatten(Matrix& mat1)
	{
		std::vector<double> result(mat1.get_rows() * mat1.get_columns());
		for (auto i = 0u; i < mat1.get_rows(); ++i)
		{
			for (auto j = 0u; j < mat1.get_columns(); ++j)
			{
				result[i*mat1.get_columns() + j] = mat1.get(i, j);
			}
		}
		return result;
	}

	// Return sum of all elements in matrix
	double element_sum(Matrix& mat1)
	{
		int sum = 0;
		for (int i = 0; i < mat1.get_rows(); ++i)
		{
			for (int j = 0; j < mat1.get_columns(); ++j)
			{
				sum += mat1.get(i, j);
			}
		}
		return sum;
	}

	// Return sum of all elements in vector
	double element_sum(std::vector<double>& vec1)
	{
		int sum = 0;
		for (int i = 0; i < vec1.size(); ++i)
		{
			sum += vec1[i];
		}
		return sum;
	}

	// Reshape a vector into a matrix
	Matrix reshape(std::vector<double>& vec1, Image_Shape shape)
	{
		assert(shape.num_rows * shape.num_colums == vec1.size());
		Matrix mat(shape.num_rows, shape.num_colums);
		for (int i = 0; i < shape.num_rows; ++i)
		{
			for (int j = 0; j < shape.num_colums; ++j)
			{
				mat.set(i, j, i*shape.num_rows + j);
			}
		}
		return mat;
	}
}