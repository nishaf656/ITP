#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of rows: ";
    cin >> n;

    // outer loop for rows
    for (int i = 1; i <= n; i++) {
        // print spaces to give pyramid shape
        for (int sp = 1; sp <= n - i; sp++) 
        cout << "  "; // two spaces to align (one space for each missing num)
        
        // print increasing numbers from 1 to i
        for (int j = 1; j <= i; j++) 
        cout << j << " ";

        // print decreasing numbers from i-1 to 1 (i-1 so it doesn't print the row number twice)
        for (int j = i - 1; j >= 1; j--)
        cout << j << " ";

        cout << endl; // move onto next row
    }

    return 0;
}