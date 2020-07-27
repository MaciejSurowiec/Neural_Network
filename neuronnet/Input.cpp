#include "Input.h"

int& chartoint(char* word, int bytes)
{
	int temp = 0;

	for (int j = 0; j < bytes; j++)
	{
		char c = word[j];
		bool b[8];

		for (int i = 0; i < 8; i++)
		{
			b[7 - i] = ((int)pow(2, i) & c) / (int)pow(2, i);
		}

		for (int i = 0; i < 8; i++)
		{
			temp <<= 1;
			temp += b[i];
		}
	}

	return temp;
}


int& chartoint(char c)
{
	int temp = 0;
	bool b[8];

	for (int i = 0; i < 8; i++)
	{
		temp += ((int)pow(2, i) & c);
	}


	return temp;
}


Input::Input()
{
	actual = NULL;
	image.open(IMAGE_PATH, std::ios_base::in | std::ios_base::binary);
	label.open(LABEL_PATH, std::ios_base::in | std::ios_base::binary);
	//getting primary values (magic number,width,height number of items)

	char* f = new char[4];
	for (int i = 0; i < 4; i++) { image>>f[i]; }
	for (int i = 0; i < 4; i++) { label>>f[i]; }

	for (int i = 0; i < 4; i++) { image>>f[i]; }
	items = chartoint(f, 4);

	for (int i = 0; i < 4; i++) { label>>f[i]; }
	items = chartoint(f, 4);

	for (int i = 0; i < 4; i++) {image>>f[i]; }
	width = chartoint(f, 4);

	for (int i = 0; i < 4; i++) { image>>f[i]; }
	height = chartoint(f, 4);

	conteiners = new Conteiner[items];
	for (int i = 0; i < items; i++)
	{
		conteiners[i].offset = i;
	}
	restart();
}

void Input::next()
{
	if (position >= items)  restart(); 
	
	if (actual != NULL) delete actual;

	actual = new PictureMatrix(getImage(), getLabel());
	position++;
	
}

PictureMatrix* Input::get() { return actual; }

int Input::getLabel()
{
	label.seekg(OFFSET_LABEL+conteiners[position].offset,label.beg);
	char c;
	label.get(c);
	return chartoint(c);
}

double** Input::getImage()
{
	image.seekg(OFFSET_IMAGE + conteiners[position].offset * WIDTH * HEIGHT, image.beg);
	char c=0;

	double** img = new double* [width];
	for (int i = 0; i < width; i++) img[i] = new double[height];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			image.get(c);
			img[x][y] = chartoint(c) / 255.0f;
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

void Input::restart()
{
	//array shufle
	position = 0;
	time_t tim;
	srand(time(&tim));
	
	for (int i=0;i<items;i++)
	{
		std::swap(conteiners[i], conteiners[rand() % items]);
	}
}
