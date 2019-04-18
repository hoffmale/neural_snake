#pragma once
#include <vector>
#include <iostream>


class Matrix
{
public:
	Matrix();
	Matrix(int num_rows, int num_cols);
	Matrix(std::vector<std::vector<double>> const& matrix);
	void set(int row, int column, double value);
	double get(int row, int column);
	int get_rows() const{ return num_rows; };
	int get_columns() const { return num_cols; };
	void print();

private:
	std::vector<std::vector<double>> matrix;
	int num_rows;
	int num_cols;

};

