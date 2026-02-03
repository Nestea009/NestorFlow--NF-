#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <vector>
#include <iostream>
using namespace std;

struct Connection {
    double weight;
    double deltaWeight; // Para training o demás cosas se supone
};

class Neuron; // Forward declaration
typedef vector<Neuron> Layer;

class Neuron {
public:
    Neuron(int numOutputs, int myIndex);
    ~Neuron();
    void setOutputVal(double val) { outputVal = val; }
    double getOutputVal() const { return outputVal; }
    void feedForward(const Layer &prevLayer, const string &function);
    vector<Connection> conections;
    int myIndex;
private:
    static double activationFunction(const string &funcion);
    double gradient;
    double outputVal;
};

class Net {
public:
    Net(const vector<size_t> &topology);
    ~Net();
    void feedForward(const vector<double> &inputVals, const string &hiddenFunction, const string &outputFunction);
    void backPropagation();
    void getResults() const;
    void showStructure() const;
private:
    vector<Layer> layers; 
    double err;
    double learning_rate = 0.05; // Change it to modify how the AI learns
};

#endif