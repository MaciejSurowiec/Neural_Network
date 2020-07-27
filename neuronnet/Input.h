#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include "PictureMatrix.h"


#define IMAGE_PATH "t10k-images.idx3-ubyte"
#define LABEL_PATH "t10k-labels.idx1-ubyte"
//t10k- checkup files
//train- training files 
#define OFFSET_IMAGE 16//offset couse by primary values
#define OFFSET_LABEL 8
class Input
{
	class Conteiner
	{
		public:
			int offset;
	};

	std::fstream image;
	std::fstream label;
	PictureMatrix* actual;
	int items,width,height,position;
	Conteiner* conteiners;
	int getLabel();
	double** getImage();
	void restart();

public:
	
	Input();
	void next();
	PictureMatrix* get();
	~Input();
};

