#include "NeuralNet.hpp"
using namespace std;

int main() {

    /*
    * As an example of a first simple AI, I will try to make it learn how to differenciate
    * between numbers higher and lower than 0.5.
    */

    Net myNet({5, 10, 10, 10, 10, 10, 5}, "ReLU", "sigmoid");

    vector<double> inputs = {0.1, 0.9, 0.4, 0.6, 0.8};
    vector<double> correctVals = {0, 1, 0, 1, 1};

    myNet.feedForward(inputs);
    myNet.backPropagation(correctVals, "MSE", "MSE");
    myNet.getResults(correctVals);
    for (int i = 0; i < 1000; i++) {
        myNet.feedForward(inputs);
        myNet.backPropagation(correctVals, "MSE", "MSE");
        if (i % 500 == 0) {
            myNet.halfLearningRate();
        }
    }
    myNet.getResults(correctVals);


    

    return 0;
}