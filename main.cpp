#include "NeuralNet.hpp"
using namespace std;

int main() {

    /*
    * As an example of a first simple AI, I will try to make it learn how to differenciate
    * between numbers higher and lower than 0.5.
    */

    Net myNet({10, 50, 50, 50, 50, 50, 10}, "ReLU", "sigmoid");

    vector<double> inputs = {0.8, 0.1,0.2,0.9,0.4,0.6,0.3,0.7,0.5,0.05};
    vector<double> correctVals = {1, 0, 0, 1, 0, 1, 0, 1, 0, 0};

    for (int i = 0; i < 5000; i++) {
        myNet.feedForward(inputs);
        myNet.backPropagation(correctVals, "MSE", "MSE");
    }
    myNet.getResults();

    

    return 0;
}