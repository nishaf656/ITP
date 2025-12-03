#include <iostream>
#include <string>
#include <vector>
#include <cctype>

bool isValidTaskFile(const std::string& name) {
    // check starts with "task" and ends with ".cpp"
    if (name.size() < 6) return false; 
    if (name.substr(0, 4) != "task") return false;

    // extract number between task and .cpp
    int dotPos = name.find(".cpp");
    if (dotPos == std::string::npos) return false;

    std::string numPart = name.substr(4, dotPos - 4);

    // number part must not be empty
    if (numPart.empty()) return false;

    // number must be fully digits
    for (char ch : numPart) {
        if (!isdigit(ch)) return false;
    }

    // ❗ FIX ADDED: reject leading zeros (task01.cpp invalid)
    if (numPart.size() > 1 && numPart[0] == '0') return false;

    // ensure no illegal characters
    for (char ch : name) {
        if (!(isdigit(ch) || isalpha(ch) || ch == '_' || ch == '.'))
            return false;
    }
    return true;
}

bool isValidZipName(const std::string& name, int labNumber, int erp) {
    std::string expected = "lab" + std::to_string(labNumber) +
                           "_" + std::to_string(erp) + ".zip";
    return name == expected;
}

bool valid_submission(int labNumber, int erp,
                      const std::vector<std::string>& files,
                      bool verbose = false) {

    if (files.empty()) return false;  // no zip file at all

    bool allGood = true;
    const std::string& zipName = files[0];

    if (verbose) {
        std::cout << "Validating submission: " << zipName << "\n";
    }

    bool zipOk = isValidZipName(zipName, labNumber, erp);

    if (verbose) {
        std::cout << " - " << zipName << "   "
                  << (zipOk ? "pass" : "fail") << "\n";
    }

    if (!zipOk) allGood = false;

    int passed = zipOk ? 1 : 0;
    int total = files.size();

    for (int i = 1; i < (int)files.size(); i++) {
        bool ok = isValidTaskFile(files[i]);

        if (!ok) allGood = false;

        if (verbose) {
            std::cout << " - " << files[i] << "   "
                      << (ok ? "pass" : "fail") << "\n";
        }

        if (ok) passed++;
    }

    if (verbose) {
        std::cout << "Summary for " << zipName << ": "
                  << passed << "/" << total << " passed\n\n";
    }

    return allGood;
}

int main() {
    std::vector<std::string> case1 = {
        "lab8_12345.zip", "task1.cpp", "task2.cpp", "task3.cpp"
    };

    std::vector<std::string> badZip = {
        "lab08_12345.zip", "task1.cpp", "task2.cpp"
    };

    std::vector<std::string> badTask = {
        "lab8_12345.zip", "task01.cpp", "task2.cpp"
    };

    std::vector<std::string> badChars = {
        "lab8_12345.zip", "task1!.cpp", "task2.cpp"
    };

    // verbose
    std::cout << "Verbose Mode:\n";
    valid_submission(8, 12345, case1, true);
    valid_submission(8, 12345, badZip, true);
    valid_submission(8, 12345, badTask, true);
    valid_submission(8, 12345, badChars, true);

    // non-verbose
    
    std::cout << "Non-Verbose Mode:\n";
    std::cout << " - Valid Submission       "
              << (valid_submission(8, 12345, case1) ? "pass" : "fail") << "\n";
    std::cout << " - Invalid Zip Name       "
              << (valid_submission(8, 12345, badZip) ? "pass" : "fail") << "\n";
    std::cout << " - Invalid Task Name      "
              << (valid_submission(8, 12345, badTask) ? "pass" : "fail") << "\n";
    std::cout << " - Special Character in Task Name      "
              << (valid_submission(8, 12345, badChars) ? "pass" : "fail") << "\n";

    return 0;
}
