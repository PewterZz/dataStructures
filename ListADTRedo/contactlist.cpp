#include <iostream>
#include "contactclass.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main(){
	int choice;
	bool Except = true;
	ContactStock* contact;
	ContactList<ContactStock>* Contacts;
	Contacts = new ContactList<ContactStock>();
	do{
		system("cls");
		cout << "Welcome to Picadilly Laptop" << endl;
		cout << "===========================" << endl;
		cout << "1. Add Item" << endl;
		cout << "2. Sell Item" << endl;
		cout << "3. Display Item" << endl;
		cout << "4. Search Item" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter an option: ";
		cin >> choice;
		switch(choice){
			case 1:{
				string brand,model;
				int stock;
				cout << "Enter brand: ";
                cin >> brand;
                cout << "Enter model: ";
                cin >> model;
                while(true){
                	cout << "Enter stock(1-100): ";
                	cin >> stock;
                	if(0 > stock || stock <= 100){
                		break;
            		}
            }
                contact = new ContactStock(brand, model, stock);
                Contacts->add(*contact);
                break;
            }
            
            case 2:{
            	while(true){
            	string model,enter, answer;
            	cout << "input laptop model to sell: ";
            	cin >> model;
            	for(int i = 0; i < Contacts->length(); i++) {
            		if(Contacts->position(i).getmodel() == model){
				        cout << "\nBrand: " << Contacts->position(i).getbrand() << endl;
				        cout << "Model: " << Contacts->position(i).getmodel() << endl;
				        cout << "Stock: " << Contacts->position(i).getstock() << endl;
				        cout << endl;
				        cout << "Are you sure this is the one (y/n)?: ";
						cin  >> answer;
						if(answer == "y"){
							string temp = Contacts->position(i).getmodel();
							Contacts->sell(Contacts->position(i).getstock(), i, Contacts->position(i).getbrand(), Contacts->position(i).getmodel());
							if(temp == Contacts->position(i).getmodel()){
								cout << "Remaining stock: " << Contacts->position(i).getstock() << endl;
							}
							else{
								cout << "No more remaining in stock" << endl;
							}
			    		}
			    		else{
			    			break;
						}
					}
			    }
				cout << "Enter y to continue... ";
				cin >> enter;
				if(enter == "y"){
					break;
				}
				else{
					break;
				}
			break;
			}
				break;
			}

			case 3:{
				while(true){
					string enter;
				for(int i = 0; i < Contacts->length(); i++) {
			        cout << "\nBrand: " << Contacts->position(i).getbrand() << endl;
			        cout << "Model: " << Contacts->position(i).getmodel() << endl;
			        cout << "Stock: " << Contacts->position(i).getstock() << endl;
			        cout << endl;
			    }
			    cout << "Enter y to continue... ";
			    cin >> enter;
			    if(enter == "y"){
			    	break;
				}
				else{
					break;
				}
			}
			    break;
            }
            
            case 4:{
            	while(true){
            	string model,enter;
            	cout << "input laptop model: ";
            	cin >> model;
            	for(int i = 0; i < Contacts->length(); i++) {
            		if(Contacts->position(i).getmodel() == model){
				        cout << "\nBrand: " << Contacts->position(i).getbrand() << endl;
				        cout << "Model: " << Contacts->position(i).getmodel() << endl;
				        cout << "Stock: " << Contacts->position(i).getstock() << endl;
				        cout << endl;
			    }
			    }
				cout << "Enter y to continue... ";
				cin >> enter;
				if(enter == "y"){
					break;
				}
				else{
					break;
				}
			}
			break;
			}
			
			case 5:{
				Except = false;
				break;
			}

		}
	
	}while(Except);
	
}
