#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <format>
#include <iomanip>

#include "read_weights.h"
#include "read_biases.h"
#include "forward_pass.h"
#include "cost_function.h"

using namespace std;

float prediction(float a3) {
    if (a3 >= 0.5f)
        return 1.0f;
    else
        return 0.0f;
}

int main() {
    ifstream data_set_file("data/testing_dataset.csv");
    string coords;
    int i = 1;
    int correct = 0;
    float total_cost = 0.0f;

    auto weights = read_weights();
    auto biases = read_biases();

    Eigen::MatrixXf W0 = weights[0];
    Eigen::MatrixXf W1 = weights[1];
    Eigen::MatrixXf W2 = weights[2];

    Eigen::VectorXf b0 = biases[0];
    Eigen::VectorXf b1 = biases[1];
    Eigen::VectorXf b2 = biases[2];

    while (getline(data_set_file, coords)) {
        stringstream ss(coords);
        float x,y;
        float label;
        char comma;

        ss >> x >> comma >> y >> comma >> label;
        Eigen::VectorXf a0(2);
        a0 << x, y;

        Eigen::VectorXf a1 = ReLU(weighted_sum(W0, a0, b0));
        Eigen::VectorXf a2 = ReLU(weighted_sum(W1, a1, b1));
        Eigen::VectorXf a3 = sigmoid(weighted_sum(W2, a2, b2));

        Eigen::VectorXf z0 = weighted_sum(W0, a0, b0);
        Eigen::VectorXf z1 = weighted_sum(W1, a1, b1);
        Eigen::VectorXf z2 = weighted_sum(W2, a2, b2);

        float cost = binary_cross_entropy(a3(0), label);
        total_cost += cost;

        if (prediction(a3[0]) == label)
            correct++;

        std::cout << "Sample: " << i
                  << " | x: " << x
                  << " | y: " << y
                  << " | Label: " << label
                  << " | Output: " << a3
                  << " | Cost: " << cost << "\n";
        i++;
    }
    float average_cost = total_cost/i;
    cout << "avearge_cost: " << average_cost << "\n";
    float accuracy = (static_cast<float>(correct) / (i - 1)) * 100.0f;
    cout << "correct predictions: " << correct << "\n";
    cout << "accuracy: " << accuracy << "%" << "\n";
    return 0;
}
