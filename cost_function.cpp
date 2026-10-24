/*
 L = -(y * ln(p) + (1 - y) * ln(1 - p))
*/


#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace std;

float binary_cross_entropy(const float& prediction, const float& target) {
    return -1 * (target * log(prediction) + (1 - target) * log(1 - prediction));
}
