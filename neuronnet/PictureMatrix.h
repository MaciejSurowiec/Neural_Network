#pragma once
#include <iostream>
#include "Matrix.h"
#define WIDTH 28
#define HEIGHT 28

class PictureMatrix
{
	Matrix image;
	Matrix label;
	int size_x;
	int size_y;
	void printLabel();
public:
	PictureMatrix(double** pix, int label);
	Matrix& getImage();
	Matrix getLabel();

	void Print();

};

