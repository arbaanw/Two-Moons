/*
Crescent 1: x1(t) = cos(t), y1(t) = sin(t)
Crescent 2: x2(t) = 1 - cos(t), y2(t) = -sin(t) + 0.5
Domain: 0 <= t <= pi
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {
    constexpr double PI = 3.141592653589793;

    fstream csv_file("data_set.csv", ios::out);
    fstream text_file("data_set.txt", ios::out);
    vector<string> data; 
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

    for (const auto& item : data) {
        csv_file << item << " ";
        text_file << item << " ";
    }

    return 0;
}
