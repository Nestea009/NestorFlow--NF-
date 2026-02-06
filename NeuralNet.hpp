#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

const double BIAS_PUNISH_RATE = 10.0;
const double WEIGHT_PUNISH_RATE = 1.0;

struct Connection {
    double weight;
    double deltaWeight; // Para training o demás cosas se supone
};

class Neuron; // Forward declaration
typedef vector<Neuron> Layer;

class Neuron {
public:
    vector<Connection> conections;
    int myIndex;
    double gradient;
    Neuron(int numOutputs, int myIndex, const string &activFunction);
    ~Neuron();
    void setOutputVal(double val) { outputVal = val; }
    double getOutputVal() const { return outputVal; }
    void feedForward(const Layer &prevLayer, const string &function);
    double LossFunctionOutput(const string &function, const double Value);
    double LossFunctionHidden(const string &function, const Layer &nextLayer);
private:
    double activationFunction();
    double activationFunctionDerivative();

    string activationFun;
    double outputVal;
    double bias;

    // Needs to be more randomized
    double getRandomWeight() {
        return (double(rand()) / double(RAND_MAX)) / WEIGHT_PUNISH_RATE;
    }
    double getRandomBias() {
        return (double(rand()) / double(RAND_MAX)) / BIAS_PUNISH_RATE;
    }
    static double sigmoidFunction(const double x) {
        return 1.0 / (1.0 + exp(-x));
    }
};

class Net {
public:
    Net(const vector<size_t> &topology, const string &hiddenFunction, const string &outputFunction);
    ~Net();
    void feedForward(const vector<double> &inputVals);
    void backPropagation(const vector<double> &correctVals, const string &outputLoss, const string &hiddenLoss);
    void getResults() const;
    void showStructure() const;
private:
    vector<Layer> layers; 
    double err;
    double learning_rate = 0.3; // Change it to modify how the AI learns
    string hiddenFunction;
    string outputFunction;
};

#endif