#include "contact.h"
#include <iostream>
#include <string.h>
using namespace std;


int main(){
	Contacts MyContacts;
	int choice, count;
	bool end = false;
	while(end == false){
		cout << "\n==Contact Book==\n1.Add a new contact\n2. Delete a contact\n3. Search a contact\n4. Exit\n\nWhat is your choice?: ";
		cin >> choice;
		
		if(choice == 1){
			MyContacts.addContact();
		}
		else if(choice == 2){
			MyContacts.deleteContact();
		}
		else if(choice == 3){
			MyContacts.searchContact();
		}
		else{
			end = true;
			break;
		}
	}
};
