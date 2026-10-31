#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<Eigen::VectorXf> read_biases() {
    ifstream biases_file("data/biases.txt");
    if (!biases_file) throw runtime_error("Cannot open biases.txt");

    vector<float> values[3];
    string line;
    int layer = -1;

    while (getline(biases_file, line)) {
        if (line.find("#biases_layer_") == 0) {
            layer = line.back() - '0';
            continue;
        }

        if (layer < 0 || layer > 2) continue;

        istringstream ss(line);
        float x;
        while (ss >> x) {
            values[layer].push_back(x);
        }
    }

    if (values[0].size() != 10 ||
        values[1].size() != 10 ||
        values[2].size() != 1) {
        throw runtime_error("Unexpected number of biases");
    }

    Eigen::VectorXf b0 = Eigen::Map<Eigen::VectorXf>(values[0].data(), 10);
    Eigen::VectorXf b1 = Eigen::Map<Eigen::VectorXf>(values[1].data(), 10);
    Eigen::VectorXf b2 = Eigen::Map<Eigen::VectorXf>(values[2].data(), 1);

    vector<Eigen::VectorXf> biases = {b0, b1, b2};
    return biases;
}
