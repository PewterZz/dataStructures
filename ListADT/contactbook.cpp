#include "contact.h"
#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;


int main(){
	Contacts * <int>MyContacts;
	string choice;
	int count;
	bool end = false;
	while(end == false){
		cout << "\n  ==Contact Book==\n1. Add a new contact\n2. Delete a contact\n3. Search a contact\n4. Exit\n\nWhat is your choice?: ";
		cin >> choice;
		
		if(choice == "1"){
			MyContacts.addContact();
			cout << "\nPress anything to continue...";
			while (true){
			if(kbhit()){
				system("cls");
				break;
			}
		}
		}
		else if(choice == "2"){
			MyContacts.deleteContact();
			cout << "\nPress anything to continue...";
			while (true){
			if(kbhit()){
				system("cls");
				break;
			}
		}
		}
		else if(choice == "3"){
			MyContacts.searchContact();
			cout << "\nPress anything to continue...";
			while (true){
			if(kbhit()){
				system("cls");
				break;
			}
		}
		}
		else if(choice == "4"){
			end = true;
			break;
		}
		else{
			system("cls");
			cout << "\nPlease give one of the choices\n";
		}
	}
};
