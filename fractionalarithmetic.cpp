#include <iostream>
using namespace std;
int main () {
    int num1, den1, num2, den2;
    char op; 
    cout << "Enter numerator and denominator of first fraction: ";
    cin >> num1 >> den1;

    cout << "Enter numerator and denominator of second fraction: ";
    cin >> num2 >> den2;

    cout << "Choose operation (+, -, *, /): ";
    cin >> op;

    int num_ans, den_ans; 

    if (op == '+') { 
        // a/b + c/d = (ad + bc) / bd
        num_ans = num1* den2 + num2 * den1;
        den_ans = den1 * den2; 
    }
    else if (op == '-') {
        // a/b - c/d = (ad - bc) / bd
        num_ans = num1 * den2 - num2 * den1;
        den_ans = den1 * den2;
    }
    else if (op == '*') {
        num_ans = num1 * num2;
        den_ans = den1 * den2;
    }
    else if (op == '/') {
        // reciprocal -> a/b + c/d = (ad) / (bc)
        num_ans = num1 * den2;
        den_ans = num2 * den1;
    }

    // simplification 
    int a = num_ans, b = den_ans; // temporary var for gcd
    // get absolute value of a and b so gcd is always positive
    if (a < 0)
    a = -a;
    if (b < 0)
    b = -b;
    // using euclidean subtraction method to find gcd
    // keep subtracting the smaller number from the larger number until they are both equal
   while (a != b) {
    if (a > b) 
    a -= b;
    else 
    b -= a;
   }
   // now a == b == gcd 
   int gcd = a; // or b
   num_ans /= gcd; // numerator simplified
   den_ans /=gcd; // denomator simplified
   
   cout << "Result: " << num_ans << "/" << den_ans << endl;
   
    return 0;
}