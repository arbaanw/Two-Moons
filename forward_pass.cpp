#include <iostream>
#include <Eigen/Dense>

using namespace std;

Eigen::VectorXf sigmoid(const Eigen::VectorXf& z) {
    return (1.0f / (1.0f + (-z.array()).exp())).matrix();
}

Eigen::VectorXf ReLU(const Eigen::VectorXf& z) {
    return z.array().max(0.0f).matrix();
}

Eigen::VectorXf weighted_sum(const Eigen::MatrixXf& W, const Eigen::VectorXf& a, const Eigen::VectorXf b) {
    return W * a + b;
}
