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
int alpha[630];
string CD[630];
string CL[630];

string& rtrim(string &str, string const &whitespace = " \r\n\t\v\f")
{
    str.erase(str.find_last_not_of(whitespace) + 1);
    return str;
}

string& ltrim(string &str, string const &whitespace = " \r\n\t\v\f")
{
    str.erase(0, str.find_first_not_of(whitespace));
    return str;
}

void translate(){
    string key;
    cout << "Translate what ?: ";
    cin >> key;
    auto start = steady_clock::now();
    for(int i = 0; i < 630; i++){
        int k = 0;
        CD[i] = rtrim(CD[i]);
        if(key == CD[i]){
            auto end = steady_clock::now();
            CL[i] = rtrim(CL[i]);
            CL[i] = ltrim(CL[i]);
            cout << "The result is: " << CL[i] << endl;
        	double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
        	cout << "Running time: " << elapsed_time;
        	break;
        }
    }
}

int main(){
    string alpha1,CD1, CL1, eof;

    int i = 0;

    ifstream coeff("kamus.txt");
    if(coeff.is_open()){
        while(i < 630){
            getline(coeff, alpha1, ' ');
            int number = stoi(alpha1);
            alpha[i] = number;
            getline(coeff, CD1, ':');
            CD[i] = CD1;
            getline(coeff, CL1, '\n');
            CL[i] = CL1;
            i = i+1;

        }
        coeff.close();
        cout << "Number of Entries:" << i << endl;

        translate();
    }
}
