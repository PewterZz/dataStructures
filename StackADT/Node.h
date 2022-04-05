#ifndef STACK
#define STACK

#include <iostream>
using namespace std;

struct Node{
	int data;
	Node *next;
};


Node *head;

void push(){
	int data;
	cout << "Enter value: ";
	cin >> data;

	Node* new_node = new Node();
	
	new_node -> data = data;
	new_node -> next = head;
	head = new_node;
}

void pop(){
	Node* pop;
	if (head == NULL){
		return;
	}
	pop = head;
	head = head -> next;
	delete pop;
}

void peek(){
	if(head != NULL){
		cout << head -> data << endl;  
	}
	else{
		return;
	}
}

void peekall(Node* ptr){
	Node* All;
	All = ptr;
	while(All != NULL){
		cout << All -> data << " -> ";
		if(All->next == NULL){
			cout << "NULL";
		};
		All = All -> next;
	}
	cout << endl;
}

void ReversePrintRecursive(Node* ptr){
	if(ptr == NULL){
		return;
	}
	else{
		ReversePrintRecursive(ptr -> next);	
		cout << ptr -> data << " -> ";
	}
	if(ptr == head){
		cout << "NULL";
	}
}


void ReverseLinkedList(Node** ptr){
	Node* Body = *ptr;
	Node *next2 = NULL, *previous = NULL;
	while(Body != NULL){
		next2 = Body->next;
		Body -> next = previous;
		previous = Body;
		Body = next2; 
	}
	*ptr = previous;
	
}

void ReversePrintIterative(Node* ptr){
	ReverseLinkedList(&ptr);
	peekall(ptr);
	ReverseLinkedList(&ptr);
	
}


#endif
