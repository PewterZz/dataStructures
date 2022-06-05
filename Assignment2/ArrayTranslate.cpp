#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct word {
    string key;
    string definition;
};

string& rtrim(string& str, string const& whitespace = " \r\n\t\v\f")
{
    str.erase(str.find_last_not_of(whitespace) + 1);
    return str;
}

string& ltrim(string& str, string const& whitespace = " \r\n\t\v\f")
{
    str.erase(0, str.find_first_not_of(whitespace));
    return str;
}

word list[629];

void translate() {
    string key;
    cout << "Translate what ?: ";
    getline(cin, key);
    auto start = steady_clock::now();
    for (int i = 0; i < 630; i++) {
        int k = 0;
        if (key == list[i].key) {
            auto end = steady_clock::now();
            cout << "The result is: " << list[i].definition << endl;
            double elapsed_time = double(duration_cast<nanoseconds> (end - start).count());
            cout << "Running time: " << elapsed_time;
            break;
        }
    }
}

int main() {
    string alpha1, CD1, CL1, eof;

    int i = 0;

    ifstream coeff("kamus.txt");
    if (coeff.is_open()) {
        while (i < 629) {
            getline(coeff, alpha1, ' ');
            int number = stoi(alpha1);
            getline(coeff, CD1, ':');
            getline(coeff, CL1, '\n');
            list[i].key = rtrim(ltrim(CD1));
            list[i].definition = rtrim(ltrim(CL1));
            i = i + 1;

        }
        coeff.close();
        cout << "Number of Entries:" << i << endl;

        translate();
    }
}
