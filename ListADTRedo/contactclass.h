#include <iostream>
#include <array>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::array;

class ContactStock
{
    public:
    	ContactStock();
        ContactStock(string brand, string model, int stock);
        string getbrand();
        string getmodel();
        int getstock();
        void setstock(int new_amount);

    private:
        string _brand;
        string _model;
        int _stock;
};

ContactStock::ContactStock(){
}; 
ContactStock::ContactStock(string brand, string model, int stock)
{
    this->_brand = brand;
    this->_model = model;
    this->_stock = stock;
}

string ContactStock::getbrand()
{
    return this->_brand;
}

string ContactStock::getmodel()
{
    return this->_model;
}

int ContactStock::getstock()
{
    return this->_stock;
}

void ContactStock::setstock(int new_amount){
	this->_stock = new_amount;
}

template <class T>
class ContactList
{   
    public:
        ContactList(int size = 100);
        int length();
        int maxSize() const;
        T position(int index);
        void add(T &object);
        void sell(int stock, int index);
        void remove(int index);

    private:
        int _length;
        int _maxSize;
        T* _list;
};

template <class T>
ContactList<T>::ContactList(int size)
{
    if(100 < size < 0)
    {
        cout << "Creating an array of size 100 Instead." << endl;
        this->_maxSize = 100;
    }
    else
    {
    	cout << "Creating an array of size " << size << endl; 
        this->_maxSize = size;
    }

    this->_length = 0;
    this->_list = new T[this->_maxSize];
}

template <class T>
int ContactList<T>::length()
{
    return this->_length;
}

template <class T>
void ContactList<T>::add(T &object)
{
    if(this->length() >= this->_maxSize)
    {
        cout << "List is full." << endl;
    }
    else
    {
        this->_list[this->length()] = object;
        this->_length++;
    }
}

template <class T>
T ContactList<T>::position(int index)
{
    return this->_list[index];
}


template <class T>
void ContactList<T>::remove(int index)
{
    if(index < 0 || index >= this->length())
    {
        cout << "Invalid range" << endl;
    }
    else
    {
        for(int i = index; i < this->length(); i++)
        {
            this->_list[i] = this->_list[i + 1];
        }
        this->_length--;
    }
}


template <class T>
void ContactList<T>::sell(int stock, int index){
	int amount, integer;
	while(true){
	cout << "How much laptops are going to be sold? (" << stock << ") left: ";
	cin >> amount;
	if(0 >= amount || amount > stock){
		cout << "Amount is invalid, not enough in stock or unrecognized value." << endl;
	}
	else{
		if(amount - stock == 0){
			this->remove(index);
			break;
		}
		else{
			integer = stock - amount;
			this->position(index).setstock(integer);
			break;
		}
	}
}
	
}
