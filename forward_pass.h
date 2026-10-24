#pragma once

#include <Eigen/Dense>


Eigen::VectorXf sigmoid(const Eigen::VectorXf& z);


Eigen::VectorXf ReLU(const Eigen::VectorXf& z);


Eigen::VectorXf weighted_sum(const Eigen::MatrixXf& W, const Eigen::VectorXf& a, const Eigen::VectorXf b);
