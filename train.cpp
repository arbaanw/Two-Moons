#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <format>
#include <iomanip>

#include "read_weights.h"
#include "forward_pass.h"
#include "cost_function.h"
#include "back_propagation.h"

using namespace std;

int main() {
    ifstream data_set_file("data_set.csv");
    string coords;
    int i = 1;

    while (getline(data_set_file, coords)) {
        auto weights = read_weights();

        Eigen::MatrixXf W0 = weights[0];
        Eigen::MatrixXf W1 = weights[1];
        Eigen::MatrixXf W2 = weights[2];

        Eigen::VectorXf b0 = Eigen::VectorXf::Zero(10);
        Eigen::VectorXf b1 = Eigen::VectorXf::Zero(10);
        Eigen::VectorXf b2 = Eigen::VectorXf::Zero(1);

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

        ofstream file("weights.txt");

        file << "#weights_layer_0" << "\n";
        file << new_weights[0] << "\n";

        file << "#weights_layer_1" << "\n";
        file << new_weights[1] << "\n";

        file << "#weights_layer_2" << "\n";
        file << new_weights[2] << "\n";

        std::cout << "Sample: " << i << "/199949"
                  << " | x: " << x
                  << " | y: " << y
                  << " | Label: " << label
                  << " | Output: " << a3
                  << " | Cost: " << cost << "\n";
        i++;
    }
    return 0;
}
