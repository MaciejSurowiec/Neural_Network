#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <cmath>
#define OFFSET 100

class Neuron
{
protected:

	Neuron** nextNeurons;
	Neuron** prevNeurons;
	double* weights;
	double bias;
	double value;
	int prevLayerSize;
	int nextLayerSize;
	double zn;
public:
	
	Neuron(int prevLayerSize,int nextLayersize);
	void setConnection(Neuron** prevLayer,Neuron** nextLayer);
	void setNeuron(double* w, double& b);
	void setNeuron(std::string wb);
	double getWeight(int i);
	double getBias();
	double getValue();
	void calculateValue();
	void setValue(double d);
	void addToBias(double val);
	void addToWeight(double val,int indeks);
	void randomSet();
	void Print();
	double getZ();
	~Neuron();
};
static double eul = std::exp(1);
#endif