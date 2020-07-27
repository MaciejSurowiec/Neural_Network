#include "Neuron.h"

Neuron::Neuron(int prevLayerSize, int nextLayerSize):prevLayerSize(prevLayerSize), nextLayerSize(nextLayerSize)
{
	if(nextLayerSize>0)nextNeurons = new Neuron*[nextLayerSize];
	if(prevLayerSize>0)prevNeurons = new Neuron*[prevLayerSize];
	weights = new double[prevLayerSize];
}

double* stringToDouble(std::string line, int offset, int n)//offset number of chars to skip
{
	double* temp = new double[n];
	for (int i = 0; i < n; i++)temp[i] = 0;

	int off = 0;

	for (int i = 0; i < offset; i++)
	{
		while (line[off] != ' ') { off++; }

		off++;
	}

	for (int i = 0; i < n; i++)
	{
		int licz = 1;
		bool flip = false;
		bool less = false;
		bool ee = false;
		bool lesse = false;
		int p=0;
		if (line[off] == ' ')off++;

		while (line[off] != ' ' && off < line.size())
		{
			if (line[off] == 'e')ee = true;//if e is in number
			else
			{
				if (ee)
				{
					if (line[off] == '-')  lesse = true;//if power is negative
					else
					{
						if (line[off] == '+')lesse = false;//if power is positive
						else
						{//value of power
							p *= 10;
							p += line[off] - '0';
						}
					}
				}
				else
				{
					if (line[off] == '.')flip = true;
					else
					{
						if (line[off] == '-')less = true;
						else
						{
							if (!flip)//values before coma
							{
								temp[i] *= 10;
								temp[i] += line[off] - '0';
							}
							else
							{//values after coma
								temp[i] += ((line[off] - '0') / pow(10, licz));
								licz++;
							}
						}
					}
				}
			}

			off++;
		}
		if (less)temp[i] *= -1;
		if (ee)
		{
			if (lesse)p *= -1;
			temp[i]*=pow(10, p);
		}

	}
	return temp;
}


void Neuron::calculateValue()
{
	double x = bias;

	for (int i=0;i< prevLayerSize;i++)
	{
		x += weights[i] * prevNeurons[i]->value;
	}
	zn = x;
	value = 1 / (1 + pow(eul, -1.0f * x));
}

void Neuron::setValue(double d){value = d;}

double Neuron::getZ() { return zn; }

void Neuron::setNeuron(double* w, double &b)
{
	bias = b;
	weights = w;
}

void Neuron::setNeuron(std::string line)
{
	bias = *stringToDouble(line, 0, 1);
	weights = stringToDouble(line, 1, prevLayerSize);
}

void Neuron::randomSet()//values in range from -1 to 1
{
	bias = ((int)rand()%OFFSET-OFFSET/2)/(OFFSET/2.0f);
	weights = new double[prevLayerSize];

	for (int i = 0; i < prevLayerSize; i++)
	{
		weights[i] = ((int)rand() % OFFSET - OFFSET / 2)/(OFFSET/2.0f);
	}
}

void Neuron::setConnection(Neuron** prev, Neuron** next)
{
	nextNeurons = next;
	prevNeurons = prev;
}

double Neuron::getBias() { return bias; }

double Neuron::getWeight(int i) { return weights[i]; }

double Neuron::getValue() { return value; }

void Neuron::addToWeight(double val,int indeks)
{
	weights[indeks] += val;
}

void Neuron::addToBias(double val)
{
	bias += val;
}

void Neuron::Print()
{
	std::cout << bias << ' ';

	for (int i = 0; i < prevLayerSize; i++)
	{
		std::cout << weights[i] << " ";
	}
	std::cout << std::endl;
}
Neuron::~Neuron()
{
	delete[] weights;
}