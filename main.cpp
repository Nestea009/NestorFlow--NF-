#include "NeuralNet.hpp"
using namespace std;

int main() {
    Net myNet({2, 6, 7, 2}, "ReLU", "sigmoid");

    vector<double> inputs = {0.2, 0.1};

    myNet.feedForward(inputs);
    myNet.showStructure();
    myNet.getResults();
    

    return 0;
}