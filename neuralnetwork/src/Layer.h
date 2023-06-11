#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"

class Layer
{
private:
	int size;
	Neuron** layer;
	Layer* nextLayer;
	Layer* prevLayer;

public:
	Neuron* operator[](int indeks);

	Layer();
	void SetLayer(int s);
	void ConnectLayers(Layer* nextL, Layer* prevL);
	void SetNeurons();
	int GetSize();
	Neuron** GetLayer();
	void Print();
	~Layer();
};

#endif