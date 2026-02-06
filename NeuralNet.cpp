#include <iostream>
#include "NeuralNet.hpp"
using namespace std;

// - - - Neuron - - - 

Neuron::Neuron(int numOutputs, int myIndex, const string &activFunction) {
    // I don't think I need to use 'new' for anything here
    this->myIndex = myIndex;
    this->bias = getRandomBias();
    this->gradientWeight = 0;
    this->activationFun = activFunction;
    for(int i = 0; i<numOutputs; i++) {
        this->conections.insert(this->conections.end(), Connection());
        this->conections.back().weight = getRandomWeight();
    }
}

Neuron::~Neuron() {
    // Se supone que se hace solo?
}

double Neuron::activationFunction() {
    if (this->activationFun == "sigmoid") {
        return sigmoidFunction(this->outputVal);
    }
    else if (this->activationFun == "ReLU") {
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

double Neuron::activationFunctionDerivative() {
    if (this->activationFun == "sigmoid") {
        return sigmoidFunction(this->outputVal) * (1 - sigmoidFunction(this->outputVal));
    }
    else if (this->activationFun == "ReLU") {
        if (this->outputVal < 0) {
            return 0;
        }
        else if (this->outputVal > 1) {
            return 0;
        }
        else {
            return 1;
        }
    }
    // Próximamente habrá más
    else {
        cout << "Not defined" << endl;
        return -1;
    }
}

double Neuron::LossFunctionOutput(const string &function, const double Value) {
    if (function == "MSE") {
        // Mean Squared Error
        double err = 0.5 * (this->outputVal - Value)*(this->outputVal - Value);
        this->gradientWeight = err * this->activationFunctionDerivative();
        this->gradientBias = err;
        return err;
    }
    else if (function == "MAE") {
        //Mean Absolute Error
        double err = abs(this->outputVal - Value);
        this->gradientWeight = err * this->activationFunctionDerivative();
        this->gradientBias = err;
        return err;
    }
    // Habrá más próximamente
    else {
        cout << "No implementado aún" << endl;
        return -1;
    }
}

double Neuron::LossFunctionHidden(const string &function, const Layer &nextLayer) {
    if (function == "MSE") {
        // Mean Squared Error
        double err = 0.0;
        for (int i = 0; i < nextLayer.size(); i++) {
            err += this->conections.at(i).weight * nextLayer.at(i).gradientWeight;
        }
        err /= nextLayer.size();
        err = 0.5 * err * err;
        this->gradientWeight = err * this->activationFunctionDerivative();
        this->gradientBias = err;
        return err;
    }
    else if (function == "MAE") {
        //Mean Absolute Error
        double err = 0.0;
        for (int i = 0; i < nextLayer.size(); i++) {
            err += abs(this->conections.at(i).weight * nextLayer.at(i).gradientWeight);
        }
        err /= nextLayer.size();
        this->gradientWeight = err * this->activationFunctionDerivative();
        this->gradientBias = err;
        return err;
    }
    // Habrá más en un futuro
    else {
        cout << "No implementado aún" << endl;
        return -1;
    }
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
    this->outputVal = this->activationFunction();
}

// - - - Net - - - 

Net::Net(const vector<size_t> &topology, const string &hiddenFunction, const string &outputFunction) {
    if (topology.size() < 2) {
        cout << "Error: The topology must have at least 2 layers (input and output)" << endl;
        exit(1);
    }
    
    err = -1;
    this->hiddenFunction = hiddenFunction;
    this->outputFunction = outputFunction;
    for (int i = 0; i < topology.size() - 1; i++) {
        this->layers.insert(this->layers.end(), Layer());
        for(int j = 0; j < topology.at(i); j++) {
            this->layers.back().insert(this->layers.back().end(), Neuron(topology.at(i+1), j, hiddenFunction));
        }
    }
    // Hay que handlear la ultima layer
    this->layers.insert(this->layers.end(), Layer());
    for (int i = 0; i < topology.back(); i++) {
        this->layers.back().insert(this->layers.back().end(), Neuron(0, i, outputFunction));
    }
}

Net::~Net() {
    // Nada?
}

void Net::feedForward(const vector<double> &inputVals) {
    if (inputVals.size() != this->layers.front().size()) {
        cout << "Error: The number of input values must be equal to the number of neurons in the input layer" << endl;
        exit(1);
    }

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

// Falta por probar
void Net::backPropagation(const vector<double> &correctVals, const string &outputLoss, const string &hiddenLoss) {
    if (correctVals.size() != this->layers.back().size()) {
        cout << "Error: The number of correct values must be equal to the number of neurons in the output layer" << endl;
        exit(1);
    }
    
    Layer outputLayer = this->layers.at(this->layers.size()-1);
    // 1º Err calc in Output
    for (int i = 0; i < this->layers.back().size(); i++) {
        this->layers.back().at(i).LossFunctionOutput(outputLoss, correctVals.at(i));
    }

    // 2º The Chain Rule
    for(int i = this->layers.size() - 2; i > 0; i--) {        
        for (int j = 0; j < this->layers.at(i).size(); j++) {
            this->layers.at(i).at(j).LossFunctionHidden(hiddenLoss, this->layers.at(i+1));
        }
    }

    // 3º Propagation (Hecho dentro de la LossFunction)
    // 4º Update the weights
    for (int layer = 0; layer < this->layers.size(); layer++) {
        for (int node = 0; node < this->layers.at(layer).size(); node++) {
            for (int connection = 0; connection < this->layers.at(layer).at(node).conections.size(); connection++) {
                this->layers.at(layer).at(node).conections.at(connection).weight = this->layers.at(layer).at(node).conections.at(connection).weight + (this->learning_rate * this->layers.at(layer).at(node).gradientWeight * this->layers.at(layer).at(node).getOutputVal());
                this->layers.at(layer).at(node).bias = this->layers.at(layer).at(node).bias + (this->learning_rate * this->layers.at(layer).at(node).gradientBias);
            }
        }
    }
}

void Net::getResults(const vector<double> &correctVals) const {
    cout << "Results:::" << endl;
    for(int i = 0; i < this->layers.back().size(); i++) {
        cout << "Neuron number " << this->layers.back().at(i).myIndex << ": " << this->layers.back().at(i).getOutputVal() << ", should be " << correctVals.at(i) << endl;
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
