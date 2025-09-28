#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "Enter an amount in figures: ";
    cin >> n;

    string inwords = "";
    bool isnegative = false;

    // deal with negative numbers
    if (n < 0) {
        isnegative = true;
        n = -n;
    }

    // deal with zero
    if (n==0) {
        inwords = "zero";
    } else {
        // add negative if it was a negative number
        if (isnegative) {
            inwords += "negative ";
        }
        // break number down into thousands and hundereds/tens/units
        int thousandspart = n / 1000;
        int hundredstensunitspart = n % 1000;

        // deal with thousands part (eg for 4521 = 4)
        if (thousandspart > 0) {
            // handle numbers upto 999 for thousands part
            int h = thousandspart / 100; // hundereds place in the thousands part
            int tandu = thousandspart % 100; // tens and units place in the thousands part

            if (h > 0) {
                // convert hundreds place digit into words
                switch (h) {
                    case 1: inwords += "one"; break;
                    case 2: inwords += "two"; break;
                    case 3: inwords += "three"; break;
                    case 4: inwords += "four"; break;
                    case 5: inwords += "five"; break;
                    case 6: inwords += "six"; break;
                    case 7: inwords += "seven"; break;
                    case 8: inwords += "eight"; break;
                    case 9: inwords += "nine"; break;
                }
                inwords += " hundred";
                // add a space if there is a tens / units place
                if (tandu > 0) {
                    inwords += " ";
                }

            }
            // convert tens and units place digits in the thousands part
            if (tandu > 0) {
                if (tandu >=1 && tandu <=19) {
                    // for 1-19
                    switch (tandu) {
                        case 1: inwords += "one"; break;
                        case 2: inwords += "two"; break;
                        case 3: inwords += "three"; break;
                        case 4: inwords += "four"; break;
                        case 5: inwords += "five"; break;
                        case 6: inwords += "six"; break;
                        case 7: inwords += "seven"; break;
                        case 8: inwords += "eight"; break;
                        case 9: inwords += "nine"; break;
                        case 10: inwords += "ten"; break;
                        case 11: inwords += "eleven"; break;
                        case 12: inwords += "twelve"; break;
                        case 13: inwords += "thirteen"; break;
                        case 14: inwords += "fourteen"; break;
                        case 15: inwords += "fifteen"; break;
                        case 16: inwords += "sixteen"; break;
                        case 17: inwords += "seventeen"; break;
                        case 18: inwords += "eighteen"; break;
                        case 19: inwords += "nineteen"; break;
                    }
                } else {
                    // dealing with 20-99
                    int tens = tandu / 10;
                    int units = tandu % 10;

                    switch (tens) {
                        case 2: inwords += "twenty"; break;
                        case 3: inwords += "thirty"; break;
                        case 4: inwords += "forty"; break;
                        case 5: inwords += "fifty"; break;
                        case 6: inwords += "sixty"; break;
                        case 7: inwords += "seventy"; break;
                        case 8: inwords += "eighty"; break;
                        case 9: inwords += "ninety"; break;
                    }
                    if (units > 0) {
                        if (tens > 0) {
                            // add space if there was a tens word
                        inwords += " ";
                        }
                        switch (units) {
                            case 1: inwords += "one"; break;
                            case 2: inwords += "two"; break;
                            case 3: inwords += "three"; break;
                            case 4: inwords += "four"; break;
                            case 5: inwords += "five"; break;
                            case 6: inwords += "six"; break;
                            case 7: inwords += "seven"; break;
                            case 8: inwords += "eight"; break;
                            case 9: inwords += "nine"; break;
                        }
                    }
                }
            }

       
       inwords += " thousand"; // end of the thousands part
       // add a space if there is a hundereds/tens/units part next
       if (hundredstensunitspart > 0) {
        inwords += " ";
       }
    }

    // deal with the hundreds tens units part (eg in 4521 = 521)
    if (hundredstensunitspart > 0) {
       int h = hundredstensunitspart / 100;
       int tandu = hundredstensunitspart % 100;

       if (h > 0) {
        // convert hundreds 
        switch (h) {
            case 1: inwords += "one"; break;
            case 2: inwords += "two"; break;
            case 3: inwords += "three"; break;
            case 4: inwords += "four"; break;
            case 5: inwords += "five"; break;
            case 6: inwords += "six"; break;
            case 7: inwords += "seven"; break;
            case 8: inwords += "eight"; break;
            case 9: inwords += "nine"; break;
        }
        inwords += " hundred";
        // add a space if there is a tens and units part next
        if (tandu > 0) {
            inwords += " ";
        }
       }
       // convert tens and units
       if (tandu > 0) {
        if (tandu >=1 && tandu <=19) {
            // for 1-19
            switch (tandu) {
                case 1: inwords += "one"; break;
                case 2: inwords += "two"; break;
                case 3: inwords += "three"; break;
                case 4: inwords += "four"; break;
                case 5: inwords += "five"; break;
                case 6: inwords += "six"; break;
                case 7: inwords += "seven"; break;
                case 8: inwords += "eight"; break;
                case 9: inwords += "nine"; break;
                case 10: inwords += "ten"; break;
                case 11: inwords += "eleven"; break;
                case 12: inwords += "twelve"; break;
                case 13: inwords += "thirteen"; break;
                case 14: inwords += "fourteen"; break;
                case 15: inwords += "fifteen"; break;
                case 16: inwords += "sixteen"; break;
                case 17: inwords += "seventeen"; break;
                case 18: inwords += "eighteen"; break;
                case 19: inwords += "nineteen"; break;
            }
        } else {
        // dealing with 20-99
        int tens = tandu / 10;
        int units = tandu % 10;

        switch (tens) {
            case 2: inwords += "twenty"; break;
            case 3: inwords += "thirty"; break;
            case 4: inwords += "forty"; break;
            case 5: inwords += "fifty"; break;
            case 6: inwords += "sixty"; break;
            case 7: inwords += "seventy"; break;
            case 8: inwords += "eighty"; break;
            case 9: inwords += "ninety"; break;
        }
        if (units > 0) {
            if (tens > 0) {
                // add space if there was a tens word
            inwords += " ";
            }
            switch (units) {
                case 1: inwords += "one"; break;
                case 2: inwords += "two"; break;
                case 3: inwords += "three"; break;
                case 4: inwords += "four"; break;
                case 5: inwords += "five"; break;
                case 6: inwords += "six"; break;
                case 7: inwords += "seven"; break;
                case 8: inwords += "eight"; break;
                case 9: inwords += "nine"; break;
            }
       }
    }
}
}
}
cout << "In words: " << inwords << endl;

    return 0;
}