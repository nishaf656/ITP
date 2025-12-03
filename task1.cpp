#include <iostream>
#include <string>
#include <cctype>

// helper func to compare two chars case insensitively
bool comesbefore(char a, char b) {
    char ca = std::tolower(a);
    char cb = std::tolower(b);
    return ca < cb;
}
// 
std::string sort_string(const std::string& str, int n = -1) {
    std::string result = str;
    // determine limit
    int limit = n;
    if (limit < 0 || limit > (int)result.size()) {
        limit = result.size();
    }

    // selection sort
    for (int i = 0; i < limit - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < limit; j++) {
            if (comesbefore(result[j], result[minIndex])) {
                minIndex = j;
            }
        }
        std::swap(result[i], result[minIndex]);
    }

    return result;
    // returns sorted copy
}

void sort_string_inplace(std::string& str, int n = -1) {
    // determine limit
    int limit = n;
    if (limit < 0 || limit > (int)str.size()) {
        limit = str.size();
    }

    for (int i = 0; i < limit - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < limit; j++) {
            if (comesbefore(str[j], str[minIndex])) {
                minIndex = j;
            }
        }
        std::swap(str[i], str[minIndex]);
    }
}
// sorts string in place


int main() {
    std::string userInput;
    int countToSort;

    std::cout << "Enter a string: ";
    std::getline(std::cin, userInput);

    std::cout << "Enter number of characters to sort (negative for all): ";
    std::cin >> countToSort;

    std::string sortedCopy = sort_string(userInput, countToSort);

    std::cout << "Sorted string (new):     " << sortedCopy << "\n";

    sort_string_inplace(userInput, countToSort);
    std::cout << "Sorted string (in place): " << userInput << "\n";

    return 0;
}
