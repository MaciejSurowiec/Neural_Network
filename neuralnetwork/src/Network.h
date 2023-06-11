#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <numbers>
#include <string>
#include <iomanip>

#include "Layer.h"
#include "PictureMatrix.h"
#include "Matrix.h"
#include "Input.h"

class Network
{
private:
	Layer* layers;
	std::fstream config;
	Input input;
	void CalculateTurn();
	int results;
	bool enableExtendedOutput;
	void Save();
	void CreateNewNetwork();
	bool Load();
	void Learn(Matrix learn, Matrix* weights, Matrix* bias);
	PictureMatrix* GetPicture();
	const std::string pathToConfig{ "../Config.txt" };
	static constexpr int networkSize{ 4 };
	static constexpr int hiddenLayerSize{ 16 };
	static constexpr int inputLayer{ 0 };
	static constexpr int outputSize{ 10 };
	static constexpr int outputLayer{networkSize - 1};
	static constexpr double batchSize{ 100.0f };
	bool isFileExist();

public:
	Network(bool enableExtendedOutput);
	void Calculate(int loops);
	int Calculate(PictureMatrix image);

	~Network();

	//sigmoid function (1/(1+e^(-x)))
	//derivative of sigmoid function (e^(-x)/(1+e^(-x))^2 
};

