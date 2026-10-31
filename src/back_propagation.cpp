/* 
 *dL/da = -(y/a + (1-y)/(a-1))
 *
 * */

#include <iostream>
#include <Eigen/Dense>
#include <vector>

using namespace std;

Eigen::VectorXf ReLU_derivative(const Eigen::VectorXf& weighted_sum) {
    Eigen::VectorXf ReLU_derivative(weighted_sum.size());
    for (int i=0; i<weighted_sum.size(); i++) {
        if (weighted_sum(i) <= 0) {
            ReLU_derivative(i) = 0;
        }
        else 
            ReLU_derivative(i) = 1;
    }
    return ReLU_derivative;
}
        

vector<Eigen::MatrixXf> weight_gradient(
        const float target,
        const vector<Eigen::VectorXf>& a, 
        const vector<Eigen::MatrixXf>& W,
        const vector<Eigen::VectorXf>& z
        ) {
    Eigen::VectorXf a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
    Eigen::MatrixXf W0 = W[0], W1 = W[1], W2 = W[2];
    Eigen::VectorXf z0 = z[0], z1 = z[1], z2 = z[2];

    Eigen::MatrixXf Gw2 = (a3[0]-target) * a2.transpose();
    Eigen::MatrixXf Gw1 = ((W2.transpose() * (a3[0]-target)).cwiseProduct(ReLU_derivative(z1))) * a1.transpose();
    Eigen::MatrixXf Gw0 = ((W1.transpose()*((W2.transpose() * (a3[0]-target)).cwiseProduct(ReLU_derivative(z1)))).cwiseProduct(ReLU_derivative(z0))) * a0.transpose();

    return {Gw0, Gw1, Gw2};
}

vector<Eigen::VectorXf> bias_gradient(
        const float target,
        const vector<Eigen::VectorXf>& a, 
        const vector<Eigen::MatrixXf>& W,
        const vector<Eigen::VectorXf>& z
        ) {
    Eigen::VectorXf a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
    Eigen::MatrixXf W0 = W[0], W1 = W[1], W2 = W[2];
    Eigen::VectorXf z0 = z[0], z1 = z[1], z2 = z[2];

    Eigen::VectorXf Gb2(1);
    Gb2[0] = a3[0] - target;
    Eigen::VectorXf Gb1 = ((W2.transpose() * (a3[0]-target)).cwiseProduct(ReLU_derivative(z1)));
    Eigen::VectorXf Gb0 = ((W1.transpose()*((W2.transpose() * (a3[0]-target)).cwiseProduct(ReLU_derivative(z1)))).cwiseProduct(ReLU_derivative(z0)));

    return {Gb0, Gb1, Gb2};
}

vector<Eigen::MatrixXf> compute_new_weights(
        const float target,
        const float learning_rate,
        const vector<Eigen::VectorXf>& a, 
        const vector<Eigen::MatrixXf>& W,
        const vector<Eigen::VectorXf>& z
        ) {
    Eigen::MatrixXf W0 = W[0], W1 = W[1], W2 = W[2];
    vector<Eigen::MatrixXf> Gw = weight_gradient(target, a, W, z);

    Eigen::MatrixXf Wn0 = W0 - learning_rate*Gw[0];
    Eigen::MatrixXf Wn1 = W1 - learning_rate*Gw[1];
    Eigen::MatrixXf Wn2 = W2 - learning_rate*Gw[2];
    return {Wn0, Wn1, Wn2};
} 

vector<Eigen::VectorXf> compute_new_biases(
        const float target,
        const float learning_rate,
        const vector<Eigen::VectorXf>& a, 
        const vector<Eigen::MatrixXf>& W,
        const vector<Eigen::VectorXf>& z,
        const vector<Eigen::VectorXf>& b
        ) {
    Eigen::VectorXf b0 = b[0], b1 = b[1], b2 = b[2];
    vector<Eigen::VectorXf> Gb = bias_gradient(target, a, W, z);

    Eigen::VectorXf bn0 = b0 - learning_rate*Gb[0];
    Eigen::VectorXf bn1 = b1 - learning_rate*Gb[1];
    Eigen::VectorXf bn2 = b2 - learning_rate*Gb[2];
    return {bn0, bn1, bn2};
} 

