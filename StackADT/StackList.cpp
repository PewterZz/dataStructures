#include <iostream>
#include "Node.h"
using namespace std;

int main(){
	push();
	push();
	push();
	push();
	
	cout << endl;
	cout << "Original values: ";
	peekall(head);
	
	cout << endl;
	cout << "Recursively Reversed: ";
	ReversePrintRecursive(head);
	
	cout << endl;
	cout << "Iteratively Reversed: ";
	ReversePrintIterative(head);
	cout << endl;
	
	cout << endl;
	cout << "The element at the top is: ";
	peek();
	
	pop();
	pop();
	
	cout << endl;
	cout << "Values after popping twice: ";
	peekall(head);
	
}
