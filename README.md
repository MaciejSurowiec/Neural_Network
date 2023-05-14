# Simple C++ Neural Network

## Table of contents
* [General info](#general-info)
* [Network architecture](#Network-architecture)
* [Usage](#Usage)
* [Results](#Results)
* [to do](#to-do)
* [Liscense](#License)


## General info

This project is a simple neural network written in C++, for handwritten numbers recognition.
[MNIST database](http://yann.lecun.com/exdb/mnist) used for training and testing


## Network architecture

Network contains 4 layers:
- input layer of size 28x28
- 2 hidden layers each of size 16
- output layer of size 10

Every layer in the network is dense, and uses the Sigmoid Activation function.


## Usage 

To run this project, compile it using Visual Studio.
For now user Interface is simple and contains 2 options:
- extended or simple output
- how many batches to calculate


### Extended Output
If extended output is chosen program will display this for every test sample:
- label (number from 0 to 9)
- visual representation of that sample
- probability for each possible label


### Batches
Testing database contains 10,000 different samples, each testing batch contains 100 random samples. 
Users can choose from 1 to 100 batches.


## Results 
Acuracy for whole MNIST test dataset - 95.23%


## to do
- refactor and made it more modern
- create interface for learning 
- improve accuracy


## License
The code is licensed under the MIT license.

Yann LeCun and Corinna Cortes hold the copyright of [MNIST database](http://yann.lecun.com/exdb/mnist), which is a derivative work from original NIST datasets. MNIST database is made available under the terms of the [Creative Commons Attribution-Share Alike 3.0 license](https://creativecommons.org/licenses/by-sa/3.0/).
