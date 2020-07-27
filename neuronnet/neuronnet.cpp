#include <iostream>
#include <fstream>
#include "Network.h"
#include "Matrix.h"


//training and test database provided by mnist http://yann.lecun.com/exdb/mnist/
//this neural network converts hand writen numbers to intigers 
//Config file is gives 95.23% of training examples right, while seeing them first time and with learning function off 
//but doing about 98% of train examples right so its room for improvement 


int main()
{
	Network net;
	//test 100 of 10000 to test all change 1 to 100 
	net.calculate(1);
}

//todo list:
//check for any memory leaks
//make program more user-friendly
//error handling: wrong or corrupted config file 