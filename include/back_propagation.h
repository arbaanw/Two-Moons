#pragma once

#include <Eigen/Dense>
#include <vector>

using namespace std;

Eigen::VectorXf ReLU_derivative(const Eigen::VectorXf& weighted_sum);

vector<Eigen::MatrixXf> weight_gradient(
        const float target,
        const vector<Eigen::VectorXf>& a, 
        const vector<Eigen::MatrixXf>& W,
        const vector<Eigen::VectorXf>& z
        );

vector<Eigen::MatrixXf> compute_new_weights(
        const float target,
        const float learning_rate,
        const vector<Eigen::VectorXf>& a, 
        const vector<Eigen::MatrixXf>& W,
        const vector<Eigen::VectorXf>& z
        );
