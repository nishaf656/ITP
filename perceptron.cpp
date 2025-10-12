#include <iostream>
#include <iomanip>   
using namespace std;

int main() {
    double w = 0.0; 
    double b = 0.0;
    double learningRate = 0.01;
    double x = 3.0;
    double target = 2 * x * x - 4; 
    int steps = 1000;

    cout << fixed << setprecision(2);

    for (int i = 0; i < steps; i++) {
        double y = w * x + b;
        double error = target - y;

        w = w + learningRate * error * x;
        b = b + learningRate * error;
        if (i % 100 == 0) {
            cout << "Step " << setw(4) << i 
                 << ": prediction = " << setw(6) << y
                 << ", error = " << setw(6) << error << endl;
        }
    }
    double finalPrediction = w * x + b;
    cout << "\nFinal prediction at x=3: " << finalPrediction << endl;
    cout << "Target value: " << target << endl;
    cout << "Final w = " << w << ", b = " << b << endl;

    return 0;
}


