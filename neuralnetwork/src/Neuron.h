#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <numbers>
#include <cmath>

class Neuron
{
private:

	Neuron** nextNeurons;
	Neuron** prevNeurons;
	double* weights;
	double bias;
	double value;
	int prevLayerSize;
	int nextLayerSize;
	double zValue;
	static constexpr int offset{ 100 };
	double* StringToDouble(std::string& line, int offset, int n);

public:
	
	Neuron(int prevLayerSize,int nextLayersize);
	void SetConnection(Neuron** prevLayer, Neuron** nextLayer);
	void SetNeuron(double* w, double& b);
	void SetNeuron(std::string wb);
	double GetWeight(int i);
	double GetBias();
	double GetValue();
	void CalculateValue();
	void SetValue(double d);
	void AddToBias(double val);
	void AddToWeight(double val, int indeks);
	void RandomSet();
	void Print();
	double GetZValue();
	~Neuron();
};
#endif