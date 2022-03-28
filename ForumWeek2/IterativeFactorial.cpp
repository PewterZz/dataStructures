#include <iostream>
using namespace std;


int main(){
	int input;
	int output = 1;
	cout << "Enter a value: ";
	cin >> input;
	if(input > 1){
		for(int i = input; i > 1; i-- ){
			output *= i;
		}
	}
	else{
		output = 1;
	}
	cout << "The factorial is: " << output << endl;
	
}
