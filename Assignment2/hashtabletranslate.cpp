#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
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

const int T_S = 3000;

int hashfunc(string key){
	int hash = 0;
	for(int i=0;i < key.size(); i++){
		hash += static_cast<int>(key[i]);
	}
	hash = hash % T_S;
	return hash;
}

class HashTableEntry {
   public:
      string definition;
      string v;
      
      HashTableEntry(string k, string v) {
         this->definition = k;
         this->v = v;
      }
};
class HashMapTable {
   private:
      HashTableEntry **t;
   public:
      HashMapTable() {
         t = new HashTableEntry * [T_S];
         for (int i = 0; i < T_S; i++) t[i] = NULL;
      }
      void Insert(string k, string v) {
         int h = hashfunc(k);
         cout << h << "\n";
         while (t[h] != NULL && t[h]->v != k) {
            h = (h + 1) % T_S;
         }
         if (t[h] != NULL)
            delete t[h];
         t[h] = new HashTableEntry(v, k);
      }
      
      string SearchKey(string k) {	
         int h = hashfunc(k);
         while (t[h] != NULL && t[h]->v != k) {
            h = (h + 1) % T_S;
         }
         if (t[h] == NULL)
            throw "ERROR NOT FOUND";
         else
            return t[h]->definition;
      }
};
	
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


int main(){
	int i = 0;
	string alpha1,CD,CL,CY;
	
	HashMapTable hash;
	ifstream coeff("kamus.txt");
	if(coeff.is_open()){	
		while(i < 629){
			getline(coeff, alpha1, ' ');
			int number = stoi(alpha1);
			getline(coeff, CD, ':');
			getline(coeff, CL, '\n');
		 	hash.Insert(ltrim(rtrim(CD)), ltrim(rtrim(CL)));
            cout << CD << " " << CL << endl;
			
 			i = i+1;
			
		}
		coeff.close();
		cout << "Number of Entries:" << i << endl;
		
		cout << "what to search: ";
			getline(cin, CY , '\n');
			auto start = steady_clock::now();
            string res = hash.SearchKey(CY);
			auto end = steady_clock::now();
			cout << res << endl;
			double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
			cout << "Running time: " << elapsed_time;
		
	}
}
