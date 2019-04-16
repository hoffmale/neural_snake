#pragma once
#include <vector>
#include <iostream>


class Matrix
{
public:
	Matrix() {}																// Empty constructor		
	Matrix(int num_rows, int num_cols);										// Constructor	
	Matrix(std::vector<std::vector<double>> const& mat);
	Matrix(Matrix const& source);										    // Copy constructor


	
	Matrix multiply(double const& c) const;									// Scalar multiplication
	Matrix subtract(Matrix const& matrix1, Matrix const& matrix2) const;	// Subtraction of matrices
	Matrix multiply(Matrix const& matrix1, Matrix const& matrix2) const;	// Hadamard product (entrywise product)
	Matrix dot(Matrix const& matrix1, Matrix const& matrix2) const;		    // Dot product of 2 matrices
	Matrix transpose() const;												// Transpose matrix
	Matrix normalize(Matrix const& matrix1);								// Normalize a matrix such that the sum of each row is 1
	Matrix flatten(Matrix const& matrix1);									// Convert 2D matrix to 1D vector

	Matrix apply_function(double(*function)(double)) const;					// Used to apply a function to the entire matrix

	void print(std::ostream& flux);											// Print matrix

private:
	std::vector<std::vector<double>> matrix;
	int num_rows;
	int num_cols;

};

// Overload << operator to print
std::ostream& operator<<(std::ostream& flux, Matrix const& mat);