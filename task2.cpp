
#include <iostream>
#include <cmath>
using namespace std;

const int gridW = 80;
const int gridH = 20;
double x_min, x_max;

int main() {
    cout << "Enter x min and x max in radians: ";
    cin >> x_min >> x_max;

    char grid[gridH][gridW];
    for (int row = 0; row < gridH; row++) {
        for (int col = 0; col < gridW; col++) {
            grid[row][col] = ' ';
        }
    }

    int mid_point_y = gridH / 2;
    for (int col = 0; col < gridW; col++) {
        grid[mid_point_y][col] = '-';
    }

    int mid_point_x = gridW / 2;
    for (int row = 0; row < gridH; row++) {
        grid[row][mid_point_x] = '|';
    }
    for (int i = 0; i < gridW; i++) {
        double x = x_min + (x_max - x_min) * i / (gridW - 1);
        double y = sin(x);
        int grid_x = i;
        int grid_y = static_cast<int>((1.0 - y) / 2.0 * (gridH - 1));


        if (grid_y >= 0 && grid_y < gridH) {
            grid[grid_y][grid_x] = '*';
        }
    }

    for (int row = 0; row < gridH; row++) {
        for (int col = 0; col < gridW; col++) {
            cout << grid[row][col];
        }
        cout << endl;
    }

    return 0;
}

