#pragma once

#include <Eigen/Dense>
Eigen::MatrixXf weight_gradient(const Eigen::VectorXf& prediction, const Eigen::VectorXf& target, const Eigen::VectorXf& a);
