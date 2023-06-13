#pragma once
#include <numbers>
#include <cmath>

class Matrix
{
private:
	int size_x;
	int size_y;
	double** matrix;

public:

	Matrix(int size_x, int size_y);
	Matrix(double** mat, int size_x, int size_y);
	Matrix(const Matrix& other);
	Matrix();

	void operator=(const Matrix& other);
	void operator+=(const Matrix& other);
	void operator-=(const Matrix& other);
	double* operator[](int indeks);

	Matrix& Square();

	bool CheckSize(Matrix& other);
	bool CheckSize(int x, int y);

	void Set(double value, int x, int y);
	void Set(double** values, int x, int y);
	void Add(double value, int x, int y);
	void SetSize(int x, int y);

	double& Get(int x, int y) const;

	int GetSizeX();
	int GetSizeY();
	~Matrix();


};

