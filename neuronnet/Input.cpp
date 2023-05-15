#include "Input.h"

int16_t Input::CharToInt(char* word, int bytes)
{
	int16_t temp{ 0 };

	for (int j = 0; j < bytes; j++)
	{
		char c = word[j];
		bool b[8];

		for (int i = 0; i < 8; i++)
		{
			b[7 - i] = (static_cast<int>(pow(2, i)) & c) / static_cast<int>(pow(2, i));
		}

		for (int i = 0; i < 8; i++)
		{
			temp <<= 1;
			temp += b[i];
		}
	}

	return temp;
}

int16_t Input::CharToInt(char c)
{
	int16_t temp{ 0 };
	bool b[8];

	for (int i = 0; i < 8; i++)
	{
		temp += (static_cast<int>(pow(2, i)) & c);
	}


	return temp;
}

Input::Input()
{
	actual = NULL;
	image.open(imagePath, std::ios_base::in | std::ios_base::binary);
	label.open(labelPath, std::ios_base::in | std::ios_base::binary);
	//getting starting values (magic number, width, height number of items)

	char* f = new char[4];
	for (int i = 0; i < 4; i++) { image >> f[i]; }
	for (int i = 0; i < 4; i++) { label >> f[i]; }

	for (int i = 0; i < 4; i++) { image >> f[i]; }
	items = CharToInt(f, 4);

	for (int i = 0; i < 4; i++) { label >> f[i]; }
	items = CharToInt(f, 4);

	for (int i = 0; i < 4; i++) {image >> f[i]; }
	width = CharToInt(f, 4);

	for (int i = 0; i < 4; i++) { image >> f[i]; }
	height = CharToInt(f, 4);

	offsets = new int[items];
	for (int i = 0; i < items; i++)
	{
		offsets[i] = i;
	}

	Restart();
}

void Input::Next()
{
	if (position >= items)  Restart(); 
	
	if (actual != nullptr) delete actual;

	actual = new PictureMatrix(GetImage(), GetLabel());
	position++;
}

PictureMatrix* Input::Get() { return actual; }

int Input::GetLabel()
{
	label.seekg(offsetLabel + offsets[position], label.beg);
	char c{};
	label.get(c);
	return CharToInt(c);
}

double** Input::GetImage()
{
	image.seekg(offsetImage + offsets[position] * pow(PictureMatrix::size, 2), image.beg);
	char c{0};

	double** img = new double* [width];
	for (int i = 0; i < width; i++) img[i] = new double[height];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			image.get(c);
			img[x][y] = CharToInt(c) / maxValue;
		}
	}

	return img;
}

Input::~Input()
{
	image.close();
	label.close();
	delete actual;
}

void Input::Restart()
{ //array shufle
	position = 0;
	time_t t;
	srand(time(&t));
	
	for (int i = 0; i < items; i++)
	{
		std::swap(offsets[i], offsets[rand() % items]);
	}
}
