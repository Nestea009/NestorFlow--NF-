#include <iostream>
#include "NeuralNet.hpp"
using namespace std;

// - - - Neuron - - - 

Neuron::Neuron(int numOutputs, int myIndex) {
    // I don't think I need to use 'new' for anything here
    this->myIndex = myIndex;
    for(int i = 0; i<numOutputs; i++) {
        this->conections.insert(this->conections.end(), Connection());
        this->conections.back().weight = getRandomWeight();
        this->bias = getRandomBias();
        //this->conections.back().deltaWeight = 0.0;  //Esto tampoco importa
    }
}

double Neuron::activationFunction(const string &function) {
    if (function == "sigmoid") {
        return sigmoidFunction(this->outputVal);
    }
    else if (function == "ReLU") {
        if (this->outputVal < 0) {
            return 0;
        }
        else if (this->outputVal > 1) {
            return 1;
        }
        else {
            return this->outputVal;
        }
    }
    // Próximamente habrá más
    else {
        cout << "Not defined" << endl;
        return -1;
    }
}

Neuron::~Neuron() {
    // Se supone que se hace solo?
}

void Neuron::feedForward(const Layer &prevLayer, const string &function) {
    // Takes the previous layer and adds the previous values, multiplied to its corresponding weight.
    // x = sum(w*x) from 0 until layerMAX
    // Además, f(x) Función de Activación
    double sum = 0;
    for(int i = 0; i < prevLayer.size(); i++) {
        sum += prevLayer.at(i).conections.at(this->myIndex).weight * prevLayer.at(i).outputVal;
    }
    this->outputVal = sum + this->bias;
    this->outputVal = activationFunction(function);
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

void Net::feedForward(const vector<double> &inputVals,const string &hiddenFunction,const string &outputFunction) {
    // Hay que gestionar la input layer
    for (int a = 0; a < inputVals.size(); a++) {
        this->layers.front().at(a).setOutputVal(inputVals.at(a));
    }
    
    // Gestión de las Hidden Layers
    for (int i = 1; i < this->layers.size()-1; i++) {
        for(int j = 0; j < this->layers.at(i).size(); j++) {
            this->layers.at(i).at(j).feedForward(this->layers.at(i-1), hiddenFunction);
        }
    }

    // Gestión de la Output Layer
    for(int i = 0; i < this->layers.back().size(); i++) {
        this->layers.back().at(i).feedForward(this->layers.at(this->layers.size()-2), outputFunction);
    }
}

void Net::backPropagation() {

}

void Net::getResults() const {
    cout << "Results:::" << endl;
    for(int i = 0; i < this->layers.back().size(); i++) {
        cout << "Neuron number " << this->layers.back().at(i).myIndex << ": " << this->layers.back().at(i).getOutputVal() << endl;
    }
}

void Net::showStructure() const {
    cout << "Neural Network Structure:" << endl;
    for (size_t i = 0; i < layers.size(); ++i) {
        cout << " Layer " << i << " with " << layers[i].size() << " neurons." << endl;
        for (size_t j = 0; j < layers[i].size(); ++j) {
            cout << "  Neuron " << j << " has " << layers[i][j].conections.size() << " connections. Output = " << layers[i][j].getOutputVal() << endl;
        }
    }
}
