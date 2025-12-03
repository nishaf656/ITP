#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

// storage for history
vector<array<int,4>> logBook;
// converts int code to char symbol
char toSymbol(int code) {
    return static_cast<char>(code);
}
// prints help message
void printHelp() {
    cout << "\nUsage:\n  <operator> <num1> <num2>\n\n"
         << "Description:\n  Perform basic arithmetic operations or run utility commands.\n\n"
         << "Operators: +  -  *  /\n\n"
         << "Commands:\n"
         << "  history  -> show all calculations\n"
         << "  help     -> show this help message\n"
         << "  quit     -> exit the program\n";
}
// checks if string is a valid int num
bool isNumberSafe(const string &s) {
    if (s.empty()) return false;
    int i = 0;
    if (s[0] == '+' || s[0] == '-') i++;
    if (i == s.size()) return false;
    for (; i < s.size(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main() {
    cout << "Simple Command-Line Calculator\nType 'help' for a list of commands.\n";
    string line;

    while (true) {
        cout << "\n> ";
        getline(cin, line);
        if (line.empty()) continue;
// process commands
        if (line == "help") {
            cout << "\nUsage:\n  <operator> <num1> <num2>\n"
                 << "\nDescription:\n  Perform basic arithmetic operations or run utility commands.\n"
                 << "\nOperators: +  -  *  /\n"
                 << "\nExample: + 5 3 -> 8\n"
                 << "\nCommands:\n"
                 << "  history -> show history of all previous operations\n"
                 << "  help    -> display this help message\n"
                 << "  quit    -> exit the program\n";
            continue;
        }
// show history
        if (line == "history") {
            if (logBook.empty()) {
                cout << "\nNo history yet.\n";
            } else {
                cout << "\n";
                for (auto &rec : logBook) {
                    cout << rec[0] << " " << toSymbol(rec[1]) << " " 
                         << rec[2] << " = " << rec[3] << "\n";
                }
            }
            continue;
        }
// exit program
        if (line == "quit") {
            cout << "Exiting Calculator.";
            break;
        }
// for arithmetic
        stringstream cut(line);
        string a, b;
        char sgn;
        cut >> sgn >> a >> b;
// validate input
        if (!cut || (sgn != '+' && sgn != '-' && sgn != '*' && sgn != '/')) {
            cout << "Error: Invalid input.";
            continue;
        }
// validate numbers
        if (!isNumberSafe(a) || !isNumberSafe(b)) {
            cout << "Error: Invalid number.";
            continue;
        }
// perform calc
        int x = stoi(a);
        int y = stoi(b);
        int val = 0;

        if (sgn == '/' && y == 0) {
            cout << "Error: Division by zero.";
            logBook.push_back({x, (int)sgn, y, 0});
            continue;
        }

        switch (sgn) {
            case '+': val = x + y; break;
            case '-': val = x - y; break;
            case '*': val = x * y; break;
            case '/': val = x / y; break;
        }
// output result & log
        cout << val;
        logBook.push_back({x, (int)sgn, y, val});
    }

    return 0;
}
