#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "Layer.h"
#include "PictureMatrix.h"
#include "Matrix.h"
#include "Input.h"
#include <iomanip>

#define PATH "Config.txt"
#define LAYERS_NUM 4
#define HIDDEN_SIZE 16
#define OUT_SIZE 10
#define OUTPUT LAYERS_NUM-1
#define INPUT 0
#define LOOP 100.0f

class Network
{
protected:
	Layer* layers;
	std::fstream config;
	Input input;
	void calculateTurn();
	int results;

public:
	Network();
	void save();
	void createNewNetwork();
	bool load();

	PictureMatrix* getPicture();
	void calculate(int loops);
	void Learn(Matrix learn,Matrix* w,Matrix* b);
	~Network();

	//sigmoid function (1/(1+e^(-x)))
	//derivative of sigmoid function (e^(-x)/(1+e^(-x))^2 


};

