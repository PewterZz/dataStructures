#include <iostream>
#include "List.h"
#include <string.h>
#include <vector>
using namespace std;

template <class T>
class Contacts{
	public:
		int count,choices;
		int size = 5;
		Contacts(){
			count = 0;
		};
		
		//dynamic storage using vector on struct class
		vector<ContactList> contacts{size};
		
		void addContact(){
			if(count >= (size-2)){
				//dynamic resizing
				contacts.resize(count+5);
			}
			cout << "\ncontact no." << count+1 << endl;
			cout << "Enter person's name: ";
			cin >> contacts[count].name;
			
			cout << "Enter person's age: ";
			cin >> contacts[count].age;
		
			cout << "Enter person's phone number: ";
			cin >> contacts[count].phone;
		
			for(int i = 0; i < count; i++){
				if(contacts[count].phone == contacts[i].phone){
					cout << "Contact already exists" << endl;
					return;
				};
			}
			
			cout << "Enter person's birthday (1st of January): ";
			cin >> contacts[count].birthday;
			count++;
			
			};
		
		
		void deleteContact(){
			int found = 0;
			int number, person;
			
			cout << "Enter the number of the person you would like to delete: ";
			cin >> person;
			
			for(int i = 0; i < count; i++){
				if(person == contacts[i].phone){
					found = i;
				}
			};
			if(found >= 0){
					for(int i = found; i < count; i++){
						contacts[i] = contacts[i + 1];
					};
				};
				
			cout << "\nContact Deleted" << endl;
			count--;
			
			//dynamic downsizing
			if((size-2) > count){
				contacts.resize(count+1);
			}
		}
		
		void searchContact(){
			int search;
			bool found = true;
			cout << "Enter search number: ";
			cin >> search;
			
			for(int i = 0; i < count + 1; i++){
				found = false;
				if(search == contacts[i].phone){
					cout << "\n!!!Found!!!";
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
			cout << endl << "Contact No." << i + 1 << endl;
			cout << "Name: " << contacts[i].name << endl;
			cout << "Age: " << contacts[i].age << endl;
			cout << "Phone: " << contacts[i].phone << endl;
			cout << "Birthday: " << contacts[i].birthday << endl;
		}

};

