/*
Crescent 1: x1(t) = cos(t), y1(t) = sin(t)
Crescent 2: x2(t) = 1 - cos(t), y2(t) = -sin(t) + 0.5
Domain: 0 <= t <= pi
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
    constexpr double PI = 3.141592653589793;

    fstream file("data.txt", ios::out);
    int t;
    int label;
    
    for (t = 0; t <= 180; t++) {
        label = 0;
        double rad = t * (PI / 180);
        float x1 = cos(rad);
        float y1 = sin(rad);

        std::cout << x1 << "," << y1 << "," << label << "\n";
    }

    for (t = 0; t <= 180; t++) {
        label = 1;
        double rad = t * (PI / 180);
        float x2 = 1 - cos(rad);
        float y2 = -1 * sin(rad) + 0.5;

        std::cout << x2 << "," << y2 << "," << label << "\n";
    }
    return 0;
}
