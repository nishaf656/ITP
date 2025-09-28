#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;

    int sum = 0; // sum of proper divisors

    // check all numbers from 1 to n/2
    for (int i = 1; i <= n/2; i++) {
        if (n % i == 0) { // if i divides evenly
            sum += i; // add i to sum
        }
    }

    // check for perfect number i.e if sum of divisors equals the number 
    if (sum == n) 
    cout << n << " is a perfect number." << endl;
    else 
    cout << n << " is not a perfect number." << endl;

    return 0;
}