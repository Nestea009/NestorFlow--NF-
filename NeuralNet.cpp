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
        this->conections.insert(this->conections.end(), Connection());
        this->conections.back().weight = getRandomWeight();
        this->conections.back().deltaWeight = 0.0;  //Esto tampoco importa
        //cout << "Neuron " << myIndex << " connection " << i << " weight initialized to " << this->conections.back().weight << endl;
    }
}

Neuron::~Neuron() {
    // Se supone que se hace solo?
}

void Neuron::feedForward(const Layer &prevLayer) {
    // Takes the previous layer and adds the previous values, multiplied to its corresponding weight.
    // x = sum(w*x) from 0 until layerMAX
    double sum = 0;
    for(int i = 0; i < prevLayer.size(); i++) {
        sum += prevLayer.at(i).conections.at(prevLayer.at(i).myIndex).weight * prevLayer.at(i).outputVal;
        // Sin terminar
    }
}

// - - - Net - - - 

Net::Net(const vector<size_t> &topology) {
    err = -1;
    for (int i = 0; i < topology.size() - 1; i++) {
        this->layers.insert(this->layers.end(), Layer());
        for(int j = 0; j < topology.at(i); j++) {
            this->layers.back().insert(this->layers.back().end(), Neuron(topology.at(i+1), j));
        }
    }
    // Hay que handlear la ultima layer
    this->layers.insert(this->layers.end(), Layer());
    for (int i = 0; i < topology.back(); i++) {
        this->layers.back().insert(this->layers.back().end(), Neuron(0, i));
    }
}

Net::~Net() {
    // Nada?
}

void Net::feedForward(const vector<double> &inputVals) {
    for (int i = 0; i < this->layers.size(); i++) {
        for(int j = 1; j < this->layers.at(i).size(); i++) {
            // Empieza en 1 porque la input no necesita calcular
            this->layers.at(i).at(j).feedForward(this->layers.at(i-1));
        }
    }
}

void Net::backPropagation() {
    // It's very complicated
}

void Net::getResults(vector<double> &resultVals) const {
    
}

void Net::showStructure() const {
    cout << "Neural Network Structure:" << endl;
    for (size_t i = 0; i < layers.size(); ++i) {
        cout << " Layer " << i << " with " << layers[i].size() << " neurons." << endl;
        for (size_t j = 0; j < layers[i].size(); ++j) {
            cout << "  Neuron " << j << " has " << layers[i][j].conections.size() << " connections." << endl;
        }
    }
}
