/* 
 *dL/da = -(y/a + (1-y)/(a-1))
 *
 * */

#include <iostream>
#include <Eigen/Dense>

Eigen::MatrixXf weight_gradient(const Eigen::VectorXf& prediction, const Eigen::VectorXf& target, const Eigen::VectorXf& a) {
    return (prediction-target) * a.transpose();
}


