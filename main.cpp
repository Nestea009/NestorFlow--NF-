#include "NeuralNet.hpp"
using namespace std;

int main() {

    Neuron myNeuron(3, 0);    
    Net myNet({4, 3, 6, 2});

    vector<double> inputs = {0.2, 0.5, 0.7, 0.8};

    myNet.feedForward(inputs, "ReLU", "sigmoid");
    myNet.getResults();
    

    return 0;
}