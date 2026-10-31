#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

int main() {
    ifstream csv_input("training_dataset.csv");

    deque<string> lines;
    string line;

    while (getline(csv_input, line)) {
        lines.push_back(line);
    }

    csv_input.close();

    cout << lines.size() << "\n";

    ofstream csv_training_file("training_dataset.csv");
    ofstream txt_training_file("training_dataset.txt");
    ofstream csv_testing_file("testing_dataset.csv");
    ofstream txt_testing_file("testing_dataset.txt");

    vector<string> testing_dataset;

    for (int i = 0; i < 50000; i++) {
        testing_dataset.push_back(lines[0]);
        lines.pop_front();
    }

    cout << lines.size() << "\n";

    for (const auto& item : lines) {
        csv_training_file << item << '\n';
        txt_training_file << item << '\n';
    }

    for (const auto& item : testing_dataset) {
        csv_testing_file << item << '\n';
        txt_testing_file << item << '\n';
    }

}
