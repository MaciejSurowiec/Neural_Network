#include "Neuron.h"

Neuron::Neuron(int prevLayerSize, int nextLayerSize)
	:prevLayerSize(prevLayerSize), nextLayerSize(nextLayerSize)
{
	if(nextLayerSize > 0) nextNeurons = new Neuron*[nextLayerSize];
	if(prevLayerSize > 0) prevNeurons = new Neuron*[prevLayerSize];
	weights = new double[prevLayerSize];
}

double* Neuron::StringToDouble(std::string& line, int offset, int n)
{
	double* temp = new double[n];
	for (int i = 0; i < n; i++)temp[i] = 0;

	int index{ 0 };

	for (int i = 0; i < offset; i++)
	{
		while (line[index] != ' ') { index++; }

		index++;
	}

	for (int i = 0; i < n; i++)
	{
		int decimalPower{ 1 };
		bool flip{ false };
		bool isNegative{ false };
		bool isENotationUsed{ false };
		bool isPowerNegative{ false };
		int power{ 0 };
		if (line[index] == ' ') index++;

		while (line[index] != ' ' && index < line.size())
		{
			if (line[index] == 'e') isENotationUsed = true;
			else
			{
				if (isENotationUsed)
				{
					if (line[index] == '-') isPowerNegative = true;
					else
					{
						if (line[index] == '+') isPowerNegative = false;
						else
						{
							power *= 10;
							power += line[index] - '0';
						}
					}
				}
				else
				{
					if (line[index] == '.') flip = true;
					else
					{
						if (line[index] == '-') isNegative = true;
						else
						{
							if (!flip) //values before coma
							{
								temp[i] *= 10;
								temp[i] += line[index] - '0';
							}
							else
							{ //values after coma
								temp[i] += ((line[index] - '0') / pow(10, decimalPower));
								decimalPower++;
							}
						}
					}
				}
			}

			index++;
		}

		if (isNegative) temp[i] *= -1;

		if (isENotationUsed)
		{
			if (isPowerNegative) power *= -1;
			temp[i] *= pow(10, power);
		}
	}

	return temp;
}


void Neuron::CalculateValue()
{
	double x = bias;

	for (int i = 0; i < prevLayerSize; i++)
	{
		x += weights[i] * prevNeurons[i]->value;
	}

	zValue = x;
	value = 1 / (1 + pow(std::numbers::e, -1.0f * x)); // Sigmoid function
}

void Neuron::SetValue(double d) { value = d; }

double Neuron::GetZValue() { return zValue; }

void Neuron::SetNeuron(double* w, double& b)
{
	bias = b;
	weights = w;
}

void Neuron::SetNeuron(std::string line)
{
	bias = *StringToDouble(line, 0, 1);
	weights = StringToDouble(line, 1, prevLayerSize);
}

void Neuron::RandomSet() //values in range from -1 to 1
{
	bias = (static_cast<int>(rand()) % offset - offset / 2) / (offset / 2.0f);
	weights = new double[prevLayerSize];

	for (int i = 0; i < prevLayerSize; i++)
	{
		weights[i] = (static_cast<int>(rand()) % offset - offset / 2) / (offset / 2.0f);
	}
}

void Neuron::SetConnection(Neuron** prev, Neuron** next)
{
	nextNeurons = next;
	prevNeurons = prev;
}

double Neuron::GetBias() { return bias; }

double Neuron::GetWeight(int i) { return weights[i]; }

double Neuron::GetValue() { return value; }

void Neuron::AddToWeight(double val, int indeks)
{
	weights[indeks] += val;
}

void Neuron::AddToBias(double val)
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