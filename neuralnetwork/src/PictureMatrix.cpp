#include "PictureMatrix.h"


PictureMatrix::PictureMatrix(double** pix, int lab)
{
	image.Set(pix, size, size);

	label.SetSize(1, 10);

	for (int i = 0; i < 10; i++)
	{
		if (i == lab) label.Set(1.0f, 0, i);
		else label.Set(0.0f, 0, i);
	}
}

Matrix PictureMatrix::GetLabel() { return label; }

Matrix& PictureMatrix::GetImage() { return image; }

void PictureMatrix::Print()
{
	PrintLabel();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (image.Get(j, i) > 0.8) std::cout << '#';
			else if (image.Get(j, i) > 0.5) std::cout << '*';
			else std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

void PictureMatrix::PrintLabel()
{
	for (int i = 0; i < 10; i++)
	{
		if (label[0][i] == 1)
		{
			std::cout << i << std::endl;
			break;
		}
	}
}