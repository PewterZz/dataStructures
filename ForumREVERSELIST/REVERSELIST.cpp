#include <iostream>
using namespace std;

struct Node
{
	int data;
	
	Node* next;
};

void ReversePrint(Node* ptr){
	if(ptr == NULL){
		return;
	}
	
	else{
		ReversePrint(ptr->next);
		cout << ptr->data << endl;
	}
	
}

int main(){
	Node* Node1 = new Node;
	Node* Node2 = new Node;
	Node* Node3 = new Node;
	Node* Node4 = new Node;
	Node* Node5 = new Node;
	
	Node1->data = 6;
	Node2->data = 4;
	Node3->data = 2;
	Node4->data = 7;
	Node5->data = 8;
	
	Node1->next = Node2;
	Node2->next = Node3;
	Node3->next = Node4;
	Node4->next = Node5;
	Node5->next = NULL;
	
	ReversePrint(Node1);
}
