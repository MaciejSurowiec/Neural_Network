#include "PictureMatrix.h"


PictureMatrix::PictureMatrix(double** pix, int lab)
{
	size_x = WIDTH;
	size_y = HEIGHT;
	image.set(pix,size_x,size_y);

	label.setSize(1,10);

	for (int i = 0; i < 10; i++)
	{
		if (i == lab)label.set(1, 0, i);
		else label.set(0, 0, i);
	}
}

Matrix PictureMatrix::getLabel() { return label; }

Matrix& PictureMatrix::getImage() { return image; }

void PictureMatrix::Print()
{
	printLabel();
	for (int i=0;i<size_y;i++)
	{
		for (int j=0;j<size_x;j++)
		{
			if (image.get(j, i) > 0.8)std::cout << '#';
			else if (image.get(j, i) > 0.5)std::cout << '*';
			else std::cout << ' ';
		}
		std::cout << std::endl;
	}
}


void PictureMatrix::printLabel()
{
	int lab = 0;

	for (int i = 0; i < 10; i++)
	{
		if (label[0][i] == 1)lab = i;
	}

	std::cout << lab << std::endl;
}