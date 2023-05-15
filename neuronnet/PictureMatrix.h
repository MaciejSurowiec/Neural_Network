#pragma once
#include <iostream>
#include "Matrix.h"

class PictureMatrix
{
	Matrix image;
	Matrix label;

	void PrintLabel();
public:
	static constexpr int size{ 28 };

	PictureMatrix(double** pix, int label);
	Matrix& GetImage();
	Matrix GetLabel();

	void Print();

};

