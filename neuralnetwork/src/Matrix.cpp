#include "Matrix.h"

Matrix::Matrix()
{	
	matrix = nullptr;
	size_x = 0; 
	size_y = 0;
}

Matrix::Matrix(int size_x, int size_y)
	:size_x(size_x), size_y(size_y)
{
	matrix = new double* [size_x];
	for (int x = 0; x < size_x; x++)
	{
		matrix[x] = new double[size_y];
	}

	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			matrix[j][i] = 0;
		}
	}
}

Matrix::Matrix(double** mat, int size_x, int size_y)
	:size_x(size_x), size_y(size_y),matrix(mat){}

Matrix::Matrix(const Matrix& other)
{
	size_x = other.size_x;
	size_y = other.size_y;
	matrix = new double* [size_x];
	for (int x = 0; x < size_x; x++)
	{
		matrix[x] = new double[size_y];
	}

	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			matrix[x][y] = other.Get(x, y);
		}
	}
}

bool Matrix::CheckSize(int x, int y)
{
	if (size_x == x && size_y == y) return true;
	else return false;
}

bool Matrix::CheckSize(Matrix& other)
{
	if (size_x == other.GetSizeX() && size_y == other.GetSizeY()) return true;
	else return false;
}

void Matrix::Set(double value, int x, int y)
{
	if (x < size_x && y < size_y && x >= 0 && y >= 0)
	{
		matrix[x][y] = value;
	}
}

void Matrix::Set(double** value, int x, int y)
{
	matrix = value;
	size_x = x;
	size_y = y;
}

void Matrix::Add(double value, int x, int y)
{
	matrix[x][y] += value;
}

void Matrix::SetSize(int x, int y)
{
	size_x = x;
	size_y = y;

	if (matrix == nullptr) { delete matrix; } //?

	matrix = new double* [size_x];

	for (int i = 0; i < size_x; i++)
	{
		matrix[i] = new double[size_y];
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

double& Matrix::Get(int x, int y) const { return matrix[x][y]; }

int Matrix::GetSizeX() { return size_x; }

int Matrix::GetSizeY() { return size_y; }

Matrix& Matrix::Square()
{
	Matrix temp(*this);

	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			temp.Set(pow(temp.Get(x, y), 2), x, y);
		}
	}
	return temp;
}

void Matrix::operator=(const Matrix& other)
{
	Matrix temp(other);
}

void Matrix::operator+=(const Matrix& other)
{
	for (int x = 0 ; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			matrix[x][y] += other.Get(x, y);
		}
	}
}

void Matrix::operator-=(const Matrix& other)
{
	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			matrix[x][y] -= other.Get(x, y);
		}
	}
}

Matrix& operator+(const Matrix& right, const Matrix& left)
{
	Matrix temp(right);
	temp += left;
	return temp;
}

Matrix& operator-( Matrix& right, Matrix& left)
{
	Matrix temp(right);
	temp -= left;
	return temp;
}

double* Matrix::operator[](int indeks) {  return matrix[indeks]; }

Matrix::~Matrix() 
{

	for (int i = 0; i < size_x; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix; 
}