# Simple C++ Neural Network

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Network architecture](#Network-architecture)
* [Usage](#Usage)
* [Results](#Results)
* [to do](#to-do)
* [Liscense](#License)


## General info

This project is a simple neural network written in C++, for handwritten numbers recognition.
[MNIST database](http://yann.lecun.com/exdb/mnist) used for training and testing. Simple GUI allows to test network by drawing examples. Works on Windows and Linux.


## Technologies
* C++20
* Visual Studio 2022
* Qt 6
* CMake

## Network architecture

Network contains 4 layers:
- input layer of size 28x28
- 2 hidden layers each of size 16
- output layer of size 10

Every layer in the network is dense, and uses the Sigmoid Activation function.


## Usage 

To run this project, build it using CMake. Then run the neuralnetwork executable.


#### Example output:
The white area on the left allows you to draw numbers. On the right, there are two buttons: one clears the drawing area, and the other runs the drawn number through the neural network and displays the result on the label below.

![example gui](/examples/gui.PNG)

![example gui 2](/examples/gui2.PNG)

## Results 
Acuracy for whole MNIST test dataset - 95.23%

Acuracy for drawn numbers works well, but only when number is drawn in center.

## to do
- algorithm to center drawn number
- create interface for learning 
- improve accuracy


## License
The code is licensed under the MIT license.

Yann LeCun and Corinna Cortes hold the copyright of [MNIST database](http://yann.lecun.com/exdb/mnist), which is a derivative work from original NIST datasets. MNIST database is made available under the terms of the [Creative Commons Attribution-Share Alike 3.0 license](https://creativecommons.org/licenses/by-sa/3.0/).
