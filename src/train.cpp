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
#include "back_propagation.h"

using namespace std;

int main() {
    ifstream data_set_file("data/training_dataset.csv");
    string coords;
    int i = 1;

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
        const float learning_rate = 0.01f;

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

        vector<Eigen::MatrixXf> new_weights = compute_new_weights(label, learning_rate, {a0, a1, a2, a3}, {W0, W1, W2}, {z0, z1, z2});
        vector<Eigen::VectorXf> new_biases = compute_new_biases(label, learning_rate, {a0, a1, a2, a3}, {W0, W1, W2}, {z0, z1, z2}, {b0, b1, b2});

        W0 = new_weights[0];
        W1 = new_weights[1];
        W2 = new_weights[2];

        b0 = new_biases[0];
        b1 = new_biases[1];
        b2 = new_biases[2];

        std::cout << "Sample: " << i << "/199949"
                  << " | x: " << x
                  << " | y: " << y
                  << " | Label: " << label
                  << " | Output: " << a3
                  << " | Cost: " << cost << "\n";
        i++;
    }

    ofstream weights_file("data/weights.txt");
    ofstream bias_file("data/biases.txt");

    weights_file << "#weights_layer_0" << "\n";
    weights_file << W0 << "\n";

    weights_file << "#weights_layer_1" << "\n";
    weights_file << W1 << "\n";

    weights_file << "#weights_layer_2" << "\n";
    weights_file << W2 << "\n";

    bias_file << "#biases_layer_0" << "\n";
    bias_file << b0 << "\n";

    bias_file << "#biases_layer_1" << "\n";
    bias_file << b1 << "\n";

    bias_file << "#biases_layer_2" << "\n";
    bias_file << b2 << "\n";

    return 0;
}
