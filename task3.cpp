#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


int main() {
    srand(time(0));

    int width, height, initialinf, days;
    double p_infect, p_worsen;

    cout << "Enter grid width and height: ";
    cin >> width >> height;
    cout << "Enter initial number of infected individuals: ";
    cin >> initialinf;
    cout << "Enter infection probability (0..1): ";
    cin >> p_infect;
    cout << "Enter worsening probability (0..1): ";
    cin >> p_worsen;
    cout << "Enter number of days: ";
    cin >> days;
    vector<vector<int>> grid(height, vector<int>(width, 0));

    for (int i = 0; i < initialinf; i++) {
        int r = rand() % height;
        int c = rand() % width;
        grid[r][c] = 1 + rand() % 3; 
    }

    cout << "\nInitial grid state:\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int cell = grid[i][j];
            if (cell == 0) cout << ".";
            else if (cell >= 1 && cell <= 9) cout << cell;
            else if (cell == 10) cout << "R";
            else if (cell == 11) cout << "X";
        }
        cout << '\n';
    }

    for (int day = 1; day <= days; day++) {
        vector<vector<int>> next = grid;
        int healthy = 0, infected = 0, recovered = 0, dead = 0;

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int state = grid[r][c];
                if (state == 0) {
                    bool neighborInfected = false;
                    for (int dr = -1; dr <= 1; dr++) {
                        for (int dc = -1; dc <= 1; dc++) {
                            if (dr == 0 && dc == 0) continue;
                            int nr = r + dr;
                            int nc = c + dc;
                            if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                                if (grid[nr][nc] >= 1 && grid[nr][nc] <= 9)
                                    neighborInfected = true;
                            }
                        }
                    }
                    if (neighborInfected && ((double)rand() / RAND_MAX) < p_infect) {
                        next[r][c] = 1;
                    }
                }

                else if (state >= 1 && state <= 9) {
                    double roll = (double)rand() / RAND_MAX;
                    if (roll < p_worsen / 3.0) {
                        next[r][c] = min(9, state + 1); 
                    } 
                    else if (roll < 0.5) {
                        next[r][c] = 10; 
                    } 
                    else if (roll > 0.9) {
                        next[r][c] = 11; 
                    }
                }

                int newState = next[r][c];
                if (newState == 0) healthy++;
                else if (newState >= 1 && newState <= 9) infected++;
                else if (newState == 10) recovered++;
                else if (newState == 11) dead++;
            }
        }

        grid = next;

        cout << "Day " << setw(2) << day
             << ": Healthy: " << healthy
             << ", Infected: " << infected
             << ", Recovered: " << recovered
             << ", Dead: " << dead << '\n';
    }

    cout << "\nFinal grid state:\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int cell = grid[i][j];
            if (cell == 0) cout << ".";
            else if (cell >= 1 && cell <= 9) cout << cell;
            else if (cell == 10) cout << "R";
            else if (cell == 11) cout << "X";
        }
        cout << '\n';
    }

    return 0;
}
