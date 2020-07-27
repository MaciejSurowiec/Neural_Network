#include "Matrix.h"

Matrix::Matrix()
{	
	matrix = NULL;
	size_x = 0; 
	size_y = 0;
}

Matrix::Matrix(int size_x,int size_y):size_x(size_x),size_y(size_y)
{
	matrix = new double* [size_x];
	for (int x = 0; x < size_x; x++)
	{
		matrix[x] = new double[size_y];
	}

	for (int i=0;i<size_y;i++)
	{
		for (int j=0;j<size_x;j++)
		{
			matrix[j][i] = 0;
		}
	}
}

Matrix::Matrix(double** mat,int& size_x, int& size_y) :size_x(size_x), size_y(size_y),matrix(mat){}

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
			matrix[x][y] = other.get(x, y);
		}
	}
}

bool Matrix::checkSize(int& x, int& y)
{
	if (size_x == x && size_y == y) return true;
	else return false;
}

bool Matrix::checkSize( Matrix& other)
{
	if (size_x == other.getSizeX() && size_y == other.getSizeY())return true;
	else return false;
}


void Matrix::set(double value, int x,int y) //zakladam ze zanim bede robil seta to bede sprawdzal pozycje
{
	if (x<size_x&& y<size_y&& x>=0&& y>=0)
	{
		matrix[x][y] = value;
	}
}

void Matrix::set(double** value, int& x, int& y) //zakladam ze zanim bede robil seta to bede sprawdzal pozycje
{
	matrix = value;
	size_x = x;
	size_y = y;
}

void Matrix::add(double value, int x, int y)
{
	matrix[x][y] += value;
}

void Matrix::setSize(int x, int y)
{
	size_x=x;
	size_y=y;

	if (matrix == NULL) { delete matrix; }

	matrix = new double* [size_x];

	for (int i = 0; i < size_x; i++)
	{
		matrix[i] = new double[size_y];
	}

	for (int i=0;i<size_x;i++)
	{
		for (int j=0;j<size_y;j++)
		{
			matrix[i][j] = 0;
		}
	}
}


double& Matrix::get(int x, int y) const { return matrix[x][y]; }
int& Matrix::getSizeX() { return size_x; }
int& Matrix::getSizeY() { return size_y; }

Matrix& Matrix::square()
{
	Matrix temp(*this);

	for (int x=0;x<size_x;x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			temp.set(pow(temp.get(x,y),2),x,y);
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
	for (int x=0;x<size_x;x++)
	{
		for (int y=0;y<size_y;y++)
		{
			matrix[x][y] += other.get(x, y);
		}
	}
}

void Matrix::operator-=(const Matrix& other)
{
	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			matrix[x][y] -= other.get(x, y);
		}
	}
}

Matrix& operator+(const Matrix& right, const Matrix& left)
{
	Matrix temp(right);
	temp += left;
	return temp;
}

Matrix& operator-( Matrix& right,Matrix& left)//jakos nie dziala
{
	Matrix temp(right);
	temp -= left;
	return temp;
}


double* Matrix::operator[](int indeks) {  return matrix[indeks]; }

Matrix::~Matrix() { delete[] matrix; }

