#include "Network.h"

Network::Network(bool enableExtendedOutput) : 
	enableExtendedOutput(enableExtendedOutput)
{
	results = 0;
	layers = new Layer[networkSize];
	layers[inputLayer].SetLayer(pow(PictureMatrix::size, 2));//input
	
	//creating layers and neurons in them
	///////////////////////////////////////////////////////
	int i{ inputLayer + 1 };
	for (i; i < outputLayer; i++)
	{
		layers[i].SetLayer(hiddenLayerSize);
	}

	layers[outputLayer].SetLayer(outputSize);

	//connecting neighbor neurons
	////////////////////////////////////////////////////////

	for (int i = 0; i < networkSize; i++)
	{
		Layer* r = nullptr;
		Layer* l = nullptr;
		if (i + 1  < networkSize) r = layers + i + 1;
		if (i - 1 >= 0) l = layers + i - 1;

		layers[i].ConnectLayers(r, l);
	}

	for (int i = 0; i < networkSize; i++)
	{
		layers[i].SetNeurons();
	}

	//loading net values or creating random net when there's no file
	///////////////////////////////////////////////////////
	if (!Load()) CreateNewNetwork();
}

bool Network::isFileExist()
{
	std::ifstream f(pathToConfig);
	if (f.is_open())
	{
		f.close();
		return true;
	}
	else return false;
}

bool Network::Load()
{
	if (isFileExist()) 
	{
		std::ifstream con(pathToConfig);
		config.open(pathToConfig, std::ios_base::in);
		for (int i = 1; i < networkSize; i++)
		{
			for (int j = 0; j < layers[i].GetSize(); j++)
			{
				std::string line;
				getline(config, line);

				layers[i].GetLayer()[j]->SetNeuron(line);
			}
		}

		config.close();

		return true;
	}

	return false;
}

void Network::CreateNewNetwork()
{
	time_t t{};
	srand(time(&t));

	for(int i=1; i < networkSize; i++)
	{
		for (int j = 0; j < layers[i].GetSize(); j++)
		{
			layers[i].GetLayer()[j]->RandomSet();
		}
	}

	Save();
}

void Network::Save()
{
	config.open(pathToConfig, std::ios_base::out);
	for (int i = 1; i < networkSize; i++)//Input layer doesnt need weights or biases
	{
		for (int j = 0; j < layers[i].GetSize(); j++)
		{
			double bias{ layers[i].GetLayer()[j]->GetBias() };

			config << bias << ' ';

			for (int k = 0; k < layers[i - 1].GetSize(); k++)
			{
				double weight{ layers[i].GetLayer()[j]->GetWeight(k) };

				config << weight << ' ';
			}

			config << std::endl;
		}	
	}
	config.close();
}

void Network::CalculateTurn()
{
	double cost{ 0 };
	Matrix* tempWeights = new Matrix[networkSize];
	for (int i = outputLayer; i > 0; i--)
	{
		tempWeights[i].SetSize(layers[i - 1].GetSize(), layers[i].GetSize());
	}
	//w[layer][previous neuron][actual neuron]

	Matrix* tempBias = new Matrix[networkSize];
	tempBias[outputLayer].SetSize(1, hiddenLayerSize);
	for (int i = outputLayer; i > 0; i--)
	{
		tempBias[i].SetSize(1, layers[i - 1].GetSize());
	}

	for (int i = 0; i < batchSize; i++)
	{
		PictureMatrix* in = GetPicture();

		for (int i = 0; i < PictureMatrix::size; i++)
		{
			for (int j = 0; j < PictureMatrix::size; j++)
			{
				layers[inputLayer].GetLayer()[j + (i * PictureMatrix::size)]->SetValue(in->GetImage()[j][i]);
			}
		}

		for (int i = 1; i < networkSize; i++)
		{
			for (int j = 0; j < layers[i].GetSize(); j++)
			{
				layers[i].GetLayer()[j]->CalculateValue();
			}
		}

		if (enableExtendedOutput)
		{
			in->Print();
		}

		int result{ 0 };
		double temp{ 0 };

		for (int i = 0; i < outputSize; i++)//searching for most activated neuron
		{
			if (layers[outputLayer].GetLayer()[i]->GetValue() > temp)
			{
				result = i;
				temp = layers[outputLayer].GetLayer()[i]->GetValue();
			}

			if (enableExtendedOutput)
			{
				std::cout << i << ": " << layers[outputLayer].GetLayer()[i]->GetValue() << std::endl;
			}
		}

		if (in->GetLabel()[0][result] == 1) results++;

		for (int k = 0; k < layers[outputLayer].GetSize(); k++)
		{
			cost += pow(layers[outputLayer].GetLayer()[k]->GetValue() - in->GetLabel()[0][k], 2);
		}

		//learinng function turned off to check test examples
		//Learn(in->getLabel(),w,b);
	}
	//std::cout << cost << std::endl;
	for (int i = 1; i < networkSize; i++)
	{
		for (int k = 0; k < layers[i].GetSize(); k++)
		{
			for (int j = 0; j < layers[i - 1].GetSize(); j++)
			{
				layers[i].GetLayer()[k]->AddToWeight(tempWeights[i][j][k] / batchSize, j);
			}

			layers[i].GetLayer()[k]->AddToBias(tempBias[i][0][k] / batchSize);
		}
	}

	delete[] tempBias;
	delete[] tempWeights;
}

void Network::Learn(Matrix learn, Matrix* w, Matrix* b)
{
	Matrix* neuronsValues = new Matrix[networkSize]; //matrix with desirable values of each neuron
	neuronsValues[outputLayer].SetSize(1, outputSize);

	for (int i = inputLayer + 1; i < outputLayer; i++)
	{
		neuronsValues[i].SetSize(1, hiddenLayerSize);
	}

	for (int i = 0; i < outputSize; i++)
	{
		neuronsValues[outputLayer].Set(2.0f * (layers[outputLayer].
			GetLayer()[i]->GetValue() - learn[0][i]), 0, i);
	}

	for (int i = outputLayer; i >0; i--) //going backwards through net
	{
		for (int k = 0; k < layers[i].GetSize(); k++)
		{
			double z{ layers[i].GetLayer()[k]->GetZValue() };
			double g{ (pow(std::numbers::e, -1.0f * z)) / (pow((1 + pow(std::numbers::e, -1.0f * z)), 2)) };
			double f{ neuronsValues[i][0][k] };
			b[i].Add(-1.0f * (f * g), 0, k);

			for (int j = 0; j < layers[i - 1].GetSize(); j++)
			{
				double value{ (f * g * layers[i].GetLayer()[k]->GetWeight(j)) };
				if (i > 1) neuronsValues[i - 1].Add(value, 0, j);
				w[i].Add(-1.0f * (f * g * layers[i - 1].GetLayer()[j]->GetValue()), j, k);
			}
		}
	}

	delete[] neuronsValues;
}

PictureMatrix* Network::GetPicture()
{
	input.Next();
	return input.Get();
}

void Network::Calculate(int loops)
{
	for (int i = 0; i < loops; i++)
	{
		CalculateTurn();	
	}
	// save only while training
	//save();
	std::cout << "accuracy: " << results / (batchSize * loops) * 100.0f << "%";
}

Network::~Network()
{
	delete[] layers;
}
