#include <iostream>
using namespace std;

int recursionFactorial(int i){
	if(i == 1){
		return 1;
	}
	else{
		return i * recursionFactorial(i-1);
	}
}

int main(){
	int input,output;
	cout << "Enter a value: ";
	cin >> input;
	output = recursionFactorial(input);
	cout << "The factorial is: " << output << endl;
	
}
