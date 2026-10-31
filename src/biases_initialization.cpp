#include <Eigen/Dense>
#include <fstream>

using namespace std;

int main() {
    Eigen::VectorXf b0 = Eigen::VectorXf::Zero(10);
    Eigen::VectorXf b1 = Eigen::VectorXf::Zero(10);
    Eigen::VectorXf b2 = Eigen::VectorXf::Zero(1);

    ofstream file("data/biases.txt");
    file << "#biases_layer_0" << "\n";
    file << b0 << "\n";

    file << "#biases_layer_1" << "\n";
    file << b1 << "\n";

    file << "#biases_layer_2" << "\n";
    file << b2 << "\n";
}
