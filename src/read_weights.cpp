#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<Eigen::MatrixXf> read_weights() {
    ifstream weights_file("weights.txt");
    if (!weights_file) throw runtime_error("Cannot open weights.txt");

    vector<float> values[3];
    string line;
    int layer = -1;

    while (getline(weights_file, line)) {
        if (line.find("#weights_layer_") == 0) {
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

    if (values[0].size() != 20 ||
        values[1].size() != 100 ||
        values[2].size() != 10) {
        throw runtime_error("Unexpected number of weights");
    }

    using RowMajorMatrix = Eigen::Matrix<float, Eigen::Dynamic,
                                         Eigen::Dynamic, Eigen::RowMajor>;

    Eigen::Map<RowMajorMatrix> W0(values[0].data(), 10, 2);
    Eigen::Map<RowMajorMatrix> W1(values[1].data(), 10, 10);
    Eigen::Map<RowMajorMatrix> W2(values[2].data(), 1, 10);

    vector<Eigen::MatrixXf> weights= {W0, W1, W2};
    return weights;
}
