#include <iostream>
#include "List.h"
#include <string.h>
using namespace std;

class Contacts{
	public:
		int count,choices;
		Contacts(){
			count = 0;
		};
		
		ContactList contacts[500];
		void addContact(){
			cout << "\ncontact no." << count+1 << endl;
			cout << "Enter person's name: ";
			cin >> contacts[count].name;
			
			cout << "Enter person's age: ";
			cin >> contacts[count].age;
			
			cout << "Enter person's phone number: ";
			cin >> contacts[count].phone;
			
			cout << "Enter person's birthday (1st of January): ";
			cin >> contacts[count].birthday;
			count++;
			};
		
		void deleteContact(){
			int found = 0;
			string person,name;
			int number;
			
			cout << "Enter the name of the person you would like to delete: ";
			cin >> person;
			
			for(int i = 0; i < count; i++){
				if(person == contacts[i].name){
					found = i;
				}
			};
			if(found >= 0){
					for(int i = found; i < count; i++){
						contacts[i] = contacts[i + 1];
					};
				};
				
			cout << "done" << endl;
			count--;
		}
		
		void searchContact(){
			string search;
			bool found = true;
			cout << "Enter search name: ";
			cin >> search;
			
			for(int i = 0; i < count; i++){
				found = false;
				if(search == contacts[i].name){
					cout << "\n###Found";
					displayContact(i);
					found = true;
					break;
				};
			}
			if(found == false){
				cout << "Not found" << endl;;
			}
		}
		
	private:
		void displayContact(int i){
			cout << endl << "Contact #" << i + 1 << ":" << endl;
			cout << "Name: " << contacts[i].name << endl;
			cout << "Age: " << contacts[i].age << endl;
			cout << "Phone: " << contacts[i].phone << endl;
			cout << "Birthday: " << contacts[i].birthday << endl;
		}
};

