#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"

class Layer
{
protected:
	int size;
	Neuron** layer;

public:
	Layer* nextLayer;
	Layer* prevLayer;

	Layer();

	Neuron* operator[](int indeks);

	void setLayer(int s);
	void connectLayers(Layer* nextL, Layer* prevL);

	void setNeurons();

	int getSize();
	Neuron** getLayer();
	void Print();
	~Layer();
};

#endif