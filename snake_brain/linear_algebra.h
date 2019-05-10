#pragma once
#include "Matrix.h"
#include "Utility.h"
#include <assert.h>


namespace np
{
	Matrix multiply(Matrix& mat1, double c);													// Scalar multiplication

	Matrix multiply(Matrix& mat1, Matrix& mat2, int slice);										// Hadamard product of matrices

	std::vector<double> multiply(std::vector<double>& vec1, std::vector<double>& vec2);			// Hadamard product of vectors

	double multiply(Matrix& mat1, Matrix& mat2, int xslice, int yslice);						// Take dot product and sum all elements

	Matrix dot(Matrix& mat1, Matrix& mat2, int slice);											// Dot product of 2 matrices

	std::vector<double> dot(Matrix& mat1, std::vector<double>& vec1, int slice);			    // Dot product of matrix and vector

	double dot(std::vector<double>& vec1, std::vector<double>& vec2);							// Dot product of 2 vectors

	Matrix dot(std::vector<double>& vec1, std::vector<double>& vec2, int slice);				// Dot product of 2 vectors returning a Rank 1 Matrix

	Matrix add(Matrix& mat1, Matrix& mat2);														// Add two matrices

	std::vector<double> add(std::vector<double>& vec1, std::vector<double>& vec2);				// Add two vectors

	Matrix subtract(Matrix& mat1, Matrix& mat2);												// Subtract two matrices

	std::vector<double> subtract(std::vector<double>& vec1, std::vector<double>& vec2);			// Subtract two vectors

	Matrix transpose(Matrix& mat1);																// Take transpose of matrix

	Matrix apply_function(Matrix& mat1, double(*function)(double));								// Apply a function to every element of the matrix

	std::vector<double> apply_function(std::vector<double>& vec1, double(*function)(double));	// Apply a function to every element of the vector

	Matrix normalize(Matrix& mat1);																// Normalize a matrix such that the sum of each row is 1

	std::vector<double> normalize(std::vector<double>& vec1);									// Normalize a vector such that sum of each element is 1

	std::vector<double> flatten(Matrix& mat1);													// Flatten a 2D matrix to 1D vector

	double maximum(Matrix & mat1, unsigned int xptr, int yptr,									// Maximum of matrix within boundaries specified by (xptr, yptr, window). 
                   Image_Shape window, Image_Shape& index);										// Set the index of maximum element in index variable

	double element_sum(Matrix& mat1);															// Return sum of all elements in matrix

	double element_sum(std::vector<double>& vec1);												// Return sum of all elements in vector

	Matrix reshape(std::vector<double>& vec1, Image_Shape shape);								// Reshape a vector into a matrix
}