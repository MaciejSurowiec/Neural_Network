#include "Network.h"

Network::Network()
{
	results = 0;
	layers = new Layer[LAYERS_NUM];
	layers[INPUT].setLayer(WIDTH * HEIGHT);//wejscie
	
	//creating layers and neurons in them
	///////////////////////////////////////////////////////
	int i = INPUT + 1;
	for (i; i < OUTPUT; i++)
	{
		layers[i].setLayer(HIDDEN_SIZE);
	}

	layers[OUTPUT].setLayer(OUT_SIZE);

	//connecting neighbors neurons
	////////////////////////////////////////////////////////

	for (int i = 0; i < LAYERS_NUM; i++)
	{
		Layer* r = NULL;
		Layer* l = NULL;
		if (i + 1  < LAYERS_NUM)r = layers+(i+1);
		if (i - 1 >= 0)l = layers + (i - 1);

		layers[i].connectLayers(r,l);
	}

	for (int i = 0; i < LAYERS_NUM; i++)
	{
		layers[i].setNeurons();
	}

	//loading net values or creating random net when theres no file
	///////////////////////////////////////////////////////
	if (!load()) createNewNetwork();
}

bool fileExist()
{
	std::ifstream f(PATH);
	if (f.is_open())
	{
		f.close();
		return true;
	}
	else return false;
}

bool Network::load()
{
	if (fileExist()) 
	{
		std::ifstream con(PATH);
		config.open(PATH, std::ios_base::in);
		for (int i = 1; i < LAYERS_NUM; i++)
		{
			for (int j = 0; j < layers[i].getSize(); j++)
			{
				std::string line;
				getline(config, line);

				layers[i].getLayer()[j]->setNeuron(line);
			}
		}

		config.close();

		return true;
	}

	return false;
}

void Network::createNewNetwork()
{
	time_t t;
	srand(time(&t));

	for(int i=1;i < LAYERS_NUM;i++)
	{
		for (int j = 0; j < layers[i].getSize(); j++)
		{
			layers[i].getLayer()[j]->randomSet();
		}
	}

	save();
}

void Network::save()
{
	config.open(PATH,std::ios_base::out);
	for (int i = 1; i < LAYERS_NUM; i++)//Input layer doesnt need weights or biases
	{
		for (int j = 0; j < layers[i].getSize(); j++)
		{
			
			double b = layers[i].getLayer()[j]->getBias();

			config <<b <<' ';

			for (int k = 0; k < layers[i - 1].getSize(); k++)
			{
				double w = layers[i].getLayer()[j]->getWeight(k);

				config <<  w<< ' ';
			}

			config << std::endl;
		}	
	}
	config.close();
}

void Network::calculateTurn()
{
	double cost = 0;
	Matrix* w;//temporary matrix for weights
	w = new Matrix[LAYERS_NUM];
	for (int i = OUTPUT; i > 0; i--)
	{
		w[i].setSize(layers[i - 1].getSize(), layers[i].getSize());
	}
	//w[layer][previous neuron][actual neuron]

	Matrix* b;//temporary matrix for biases
	b = new Matrix[LAYERS_NUM];
	b[OUTPUT].setSize(1, HIDDEN_SIZE);
	for (int i = OUTPUT; i > 0; i--)
	{
		b[i].setSize(1, layers[i - 1].getSize());
	}

	for (int i = 0; i < LOOP; i++)
	{
		PictureMatrix* in = getPicture();

		//geting input
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				layers[INPUT].getLayer()[j + (i * HEIGHT)]->setValue(in->getImage()[j][i]);
			}
		}

		for (int i = 1; i < LAYERS_NUM; i++)
		{
			for (int j = 0; j < layers[i].getSize(); j++)
			{
				layers[i].getLayer()[j]->calculateValue();
			}
		}

		in->Print();
		int result=0;
		double temp = 0.0f;
		for (int i = 0; i < OUT_SIZE; i++)//searching for most activated neuron
		{
			
			if (layers[OUTPUT].getLayer()[i]->getValue() > temp)
			{
				result = i;
				temp = layers[OUTPUT].getLayer()[i]->getValue();
			}

			std::cout << i << ": " << layers[OUTPUT].getLayer()[i]->getValue() << std::endl;
		}

		if (in->getLabel()[0][result] == 1)results++;

		for (int k = 0; k < layers[OUTPUT].getSize(); k++)
		{
			cost += pow(layers[OUTPUT].getLayer()[k]->getValue() - in->getLabel()[0][k], 2);
		}

		//learinng function off to check test examples
		//Learn(in->getLabel(),w,b);
	}
	//std::cout << cost << std::endl;
	for (int i = 1; i < LAYERS_NUM; i++)
	{
		for (int k = 0; k < layers[i].getSize(); k++)
		{
			for (int j = 0; j < layers[i - 1].getSize(); j++)
			{
				layers[i].getLayer()[k]->addToWeight(w[i][j][k]/LOOP, j);
			}

			layers[i].getLayer()[k]->addToBias(b[i][0][k]/LOOP);
		}
	}

	delete[] w;
	delete[] b;
}

void Network::Learn(Matrix learn,Matrix* w,Matrix* b)
{
	Matrix* y = new Matrix[LAYERS_NUM];//matrix with desirable value of each neuron
	y[OUTPUT].setSize(1,OUT_SIZE);

	for (int i = INPUT+1; i < OUTPUT; i++)
	{
		y[i].setSize(1, HIDDEN_SIZE);
	}

	for (int i = 0; i < OUT_SIZE;i++)
	{
		y[OUTPUT].set(2.0f*(layers[OUTPUT].getLayer()[i]->getValue()-learn[0][i]), 0, i);
	}

	//b[layer][0][actual neuron]

	for (int i = OUTPUT; i >0; i--)//going backwards through net
	{
		for (int k = 0; k < layers[i].getSize(); k++)
		{
			double z = layers[i].getLayer()[k]->getZ();
			double g = (pow(eul, -1.0f * z)) / (pow((1 + pow(eul, -1.0f * z)), 2));
			double f = y[i][0][k];
			b[i].add(-1.0f * (f * g), 0, k);

			for (int j = 0; j < layers[i - 1].getSize(); j++)
			{
				double valuey = (f * g * layers[i].getLayer()[k]->getWeight(j));
				if (i > 1)y[i - 1].add(valuey, 0, j);
				w[i].add(-1.0f * (f * g * layers[i - 1].getLayer()[j]->getValue()), j, k);
			}
		}
	}

	delete[] y;
}

PictureMatrix* Network::getPicture()
{
	input.next();
	return input.get();
}

void Network::calculate(int loops)
{
	for (int i = 0; i < loops; i++)
	{
		calculateTurn();

		//save function to check test examples
		//save();
	}

	std::cout << results / (LOOP * loops)*100.0f;
}

Network::~Network()
{
	delete[] layers;
}
