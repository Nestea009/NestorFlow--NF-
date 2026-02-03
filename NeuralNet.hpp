#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

const double BIAS_PUNISH_RATE = 5.0;
const double WEIGHT_PUNISH_RATE = 1.0;

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
    double activationFunction(const string &funcion);
    double gradient;
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
    Net(const vector<size_t> &topology);
    ~Net();
    void feedForward(const vector<double> &inputVals, const string &hiddenFunction, const string &outputFunction);
    void backPropagation(const Layer &correctVals);
    void getResults() const;
    void showStructure() const;
    void LossFunction(const string &function) {
        if (function == "MSE") {
            // Mean Squared Error
        }
        else if (function == "MAE") {
            //Mean Absolute Error

        }
        else {
            cout << "No implementado aún" << endl;
        }
    }
private:
    vector<Layer> layers; 
    double err;
    double learning_rate = 0.05; // Change it to modify how the AI learns
};

#endif