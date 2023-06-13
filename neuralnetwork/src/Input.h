#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>

#include "PictureMatrix.h"

class Input
{
	std::fstream image;
	std::fstream label;
	PictureMatrix* current;
	int items, width, height, position;
	int* offsets;

	int GetLabel();
	double** GetImage();
	void Restart();
	int16_t CharToInt(char* word, int bytes);
	int16_t CharToInt(char c);
	static constexpr double maxValue{ 255.0 };
	static constexpr int offsetImage{ 16 };
	static constexpr int offsetLabel{ 8 };
	const std::string labelPath{ "../t10k-labels.idx1-ubyte" };
	const std::string imagePath{ "../t10k-images.idx3-ubyte" };


public:
	
	Input();
	void Next();
	PictureMatrix* Get();
	~Input();
};

