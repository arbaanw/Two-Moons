
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <deque>

using namespace std;

int main() {
    constexpr double PI = 3.141592653589793;

    fstream training_dataset_file("data/training_dataset.csv", ios::out);
    fstream testing_dataset_file("data/testing_dataset.csv", ios::out);
    deque<string> data; 
    vector<string> testing_dataset;
    float t;
    int label;
    
    for (t = 0.0; t <= 180.0; t=t+0.0018) {
        label = 0;
        double rad = t * (PI / 180);
        float x1 = cos(rad);
        float y1 = sin(rad);

        string item = to_string(x1) + "," + to_string(y1) + "," + to_string(label) + "\n";
        data.push_back(item);
    }

    for (t = 0.0; t <= 180.0; t=t+0.0018) {
        label = 1;
        double rad = t * (PI / 180);
        float x2 = 1 - cos(rad);
        float y2 = -1 * sin(rad) + 0.5;

        string item = to_string(x2) + "," + to_string(y2) + "," + to_string(label) + "\n";
        data.push_back(item);
    }

    mt19937 gen(std::random_device{}());
    shuffle(data.begin(), data.end(), gen);

    for (int i = 0; i < 50000; i++) {
        testing_dataset.push_back(data[0]);
        data.pop_front();
    }

    for (const auto& item : data) {
        training_dataset_file << item;
    }

    for (const auto& item : testing_dataset) {
        testing_dataset_file << item;
    }

    return 0;
}
