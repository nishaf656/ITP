#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double w, b;
    cout << "Enter trained values of w and b: ";
    if (!(cin >> w >> b)) {
        cout << "Invalid input. Please enter numeric values.\n";
        return 1;
    }
    int correctCount = 0;

    cout << fixed << setprecision(2);
    cout << "\nTesting perceptron with 10 inputs:\n";

    for (int i = 0; i < 10; i++) {
        double x;
        cout << "Enter x" << i + 1 << ": ";
        if (!(cin >> x)) {
            cout << "Invalid input, stopping test.\n";
            break;
        }
        double y =w * x + b;
        double t =2 * x * x - 4;

        bool correct =fabs(y - t) <= 1.0;
        if (correct) correctCount++;
        cout << "x = " << setw(4) << x
             << ", prediction = " << setw(6) << y
             << ", target = " << setw(6) << t
             << " --> " << (correct ? "correct" : "incorrect")
             << endl;
    }

    double accuracy = (correctCount / 10.0) * 100.0;
    cout << "\nOverall accuracy = " << accuracy << "%" << endl;

    return 0;
}
