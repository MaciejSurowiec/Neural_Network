#include "Layer.h"

Layer::Layer()
{
	nextLayer = NULL;
	prevLayer = NULL;
	layer = NULL;
}

Neuron* Layer::operator[](int indeks)
{
	return layer[indeks];
}

void Layer::setLayer(int s)
{
	size = s;
	layer = new Neuron * [size];
}

void Layer::connectLayers( Layer* nextL, Layer* prevL)
{
	nextLayer = nextL;
	prevLayer = prevL;
}

void Layer::setNeurons()
{
	for (int i = 0; i < size; i++)
	{
		int n = 0, p = 0;

		if(nextLayer!=NULL)n = nextLayer->getSize();
		if(prevLayer!=NULL)p = prevLayer->getSize();

		layer[i] = new Neuron(p,n);
		
		Neuron** next = NULL,**prev=NULL;
		if(nextLayer!=NULL)next= nextLayer->getLayer();

		if(prevLayer!=NULL)prev= prevLayer->getLayer();

		layer[i]->setConnection(prev, next);
	}
}

int Layer::getSize() { return size; }

Neuron** Layer::getLayer() { return layer; }
void Layer::Print()
{
	if (prevLayer != NULL)std::cout <<'p'<< prevLayer->getSize()<<' ';
	std::cout <<'t'<< size << ' ';
	if(nextLayer!=NULL)std::cout <<'n'<< nextLayer->getSize();
	
	std::cout<<std::endl;
}

Layer::~Layer()
{
	delete[] layer;
}