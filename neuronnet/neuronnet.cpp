#include <iostream>
#include <fstream>
#include "Network.h"
#include "Matrix.h"

// training and test database provided by mnist http://yann.lecun.com/exdb/mnist/
// this neural network converts hand writen numbers to intigers 
// included config file gives about 95.23% correctness rate for test examples

int main()
{
	bool enableExtendedOutput{ true };
	char c{};
	std::cout << "display extended output?(y/n)" << std::endl;
	std::cin >> c;

	if (c == 'n') 
	{
		enableExtendedOutput = false;
	}

	int numberOfBatches{ 0 };
	std::cout << std::endl << "how many butches calculate?(number from 1 to 100)" << std::endl;
	std::cin >> numberOfBatches;
	std::cout << std::endl;

	if (numberOfBatches <= 0)
	{
		numberOfBatches = 1;
	}
	else
	{
		if (numberOfBatches > 100)
		{
			numberOfBatches = 100;
		}
	}

	Network net(enableExtendedOutput);
	// test 100 of 10000 to test all change 1 to 100 
	net.Calculate(numberOfBatches);


	// To get the value of duration use the count()
	// member function on the duration object
}

// todo list:
// - check for any memory leaks
// - make program more user-friendly
// - error handling: wrong or corrupted config file 