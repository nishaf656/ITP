#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double n;
    cout << "Enter a positive number: ";
    cin >> n;
    // start at interval [a.b]. for n, we take a=0, b=n
    double a = 0, b = n;
    double tolerance = 0.01;
    double m; // midpoint

    while ((b - a) > tolerance) {
        m = (a + b) / 2;
    
    double f_m = m * m - n;

    if (f_m == 0) {
        break; // have already found the root so break out of loop
    }
    else if (f_m < 0) {
        // if f(m) is negative, root is bigger than m so bring a up to m
        a = m;
    }
    else {
        // if f(m) is positive, root is smaller than m so bring b down to m
        b = m; 
    }
}
cout << fixed << setprecision(2);
cout << "Square root of " << n << " is " << m << endl;

return 0;
}