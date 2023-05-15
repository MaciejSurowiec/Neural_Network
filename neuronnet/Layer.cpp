#include "Layer.h"

Layer::Layer()
{
	nextLayer = nullptr;
	prevLayer = nullptr;
	layer = nullptr;
}

Neuron* Layer::operator[](int indeks)
{
	return layer[indeks];
}

void Layer::SetLayer(int s)
{
	size = s;
	layer = new Neuron * [size];
}

void Layer::ConnectLayers( Layer* nextL, Layer* prevL)
{
	nextLayer = nextL;
	prevLayer = prevL;
}

void Layer::SetNeurons()
{
	for (int i = 0; i < size; i++)
	{
		int n{ 0 }, p{ 0 };

		if(nextLayer != nullptr) n = nextLayer->GetSize();
		if(prevLayer != nullptr) p = prevLayer->GetSize();

		layer[i] = new Neuron(p, n);
		
		Neuron** next = nullptr, **prev = nullptr;
		if(nextLayer != nullptr) next = nextLayer->GetLayer();

		if(prevLayer != nullptr) prev = prevLayer->GetLayer();

		layer[i]->SetConnection(prev, next);
	}
}

int Layer::GetSize() { return size; }

Neuron** Layer::GetLayer() { return layer; }

void Layer::Print()
{
	if (prevLayer != nullptr) std::cout << 'p' << prevLayer->GetSize() << ' ';
	std::cout << 't' << size << ' ';
	if(nextLayer!= nullptr) std::cout << 'n' << nextLayer->GetSize();
	
	std::cout << std::endl;
}

Layer::~Layer()
{
	delete[] layer;
}