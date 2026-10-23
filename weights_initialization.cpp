#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;

std::default_random_engine generator;

Eigen::MatrixXf he_initialization (int n_in, int n_out) {
    Eigen::MatrixXf W = Eigen::MatrixXf::Zero(n_out, n_in);
    std::normal_distribution<float> distribution(0.0f, sqrt(2.0f / n_in));

    for (int i = 0; i < W.rows(); i++) {
        for (int j = 0; j < W.cols(); j++) {
        W(i,j) = distribution(generator);
        } 
    }
    return W;
}


Eigen::MatrixXf Xavier_initialization (int n_in, int n_out) {
    Eigen::MatrixXf W = Eigen::MatrixXf::Zero(n_out, n_in);

    float x = sqrt(6.0f / (n_in + n_out));

    std::uniform_real_distribution<float> distribution(-x, x);

    for (int i = 0; i < W.rows(); i++) {
        for (int j = 0; j < W.cols(); j++) {
        W(i,j) = distribution(generator);
        } 
    }
    return W;
}

int main() {
    ofstream file("weights.txt");

    file << "#weights_layer_0" << "\n";
    file << he_initialization(2, 10)<< "\n";

    file << "#weights_layer_1" << "\n";
    file << he_initialization(10, 10)<< "\n";

    file << "#weights_layer_2" << "\n";
    file << Xavier_initialization(10, 1)<< "\n";

    return 0;
}
