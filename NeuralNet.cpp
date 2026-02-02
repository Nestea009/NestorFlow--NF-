#include <iostream>
#include "NeuralNet.hpp"
using namespace std;

// Needs to be more randomized
double getRandomWeight() {
    return (double(rand()) / double(RAND_MAX));
}


// - - - Neuron - - - 

Neuron::Neuron(int numOutputs, int myIndex) {
    // I don't think I need to use 'new' for anything here
    this->myIndex = myIndex;
    for(int i = 0; i<numOutputs; i++) {
        cout << "Number between 0 and 1: " << getRandomWeight() << endl;
    }
}

Neuron::~Neuron() {
    // Se supone que se hace solo?
}

void Neuron::feedForward(const Layer &prevLayer) {
    // Takes the previous layer and adds the previous values, multiplied to its corresponding weight.
    // x = sum(w*x) from 0 until layerMAX

}

// - - - Net - - - 

void Net::backPropagation() {
    // It's very complicated
}

void Net::getResults(vector<double> &resultVals) const {
    
}

