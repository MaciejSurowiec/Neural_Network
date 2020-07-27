#pragma once
#include <math.h>

class Matrix
{
protected:
	int size_x;
	int size_y;
	double** matrix;

public:

	Matrix(int size_x, int size_y);
	Matrix(double** mat,int& size_x,int& size_y);
	Matrix(const Matrix& other);
	Matrix();

	void operator=(const Matrix& other);
	void operator+=(const Matrix& other);
	void operator-=(const Matrix& other);
	double* operator[](int indeks);

	Matrix& square();

	bool checkSize(Matrix& other);
	bool checkSize(int& x,int& y);

	void set(double value, int x, int y);
	void set(double** values, int& x, int& y);
	void add(double value, int x, int y);
	void setSize(int x, int y);

	double& get(int x, int y) const;

	int& getSizeX();
	int& getSizeY();
	~Matrix();


};

