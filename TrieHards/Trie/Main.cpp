//---------------------------------------------------------------------------

#include <fmx.h>
#include <iostream>
#include <locale>
#include <string>
#include <iomanip>
#include <sstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstring>
#include <chrono>
#pragma hdrstop

#include "Main.h"
#include "TrieHardsPCH1.h"
#include "Insert.h"
#include "Update.h"
#include "Delete.h"
#define CHAR_SIZE 123
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TDictionary *Dictionary;
//---------------------------------------------------------------------------
using std::getline;
using std::string;
using std::endl;
using namespace std::chrono;

int index;
int size = 1040;

//used to trim \r\n\t\v\f\" (mostly white space and ") from the right side of a string
string& rtrim(string &str, string const &whitespace = " \r\n\t\v\f\"")
{
	str.erase(str.find_last_not_of(whitespace) + 1);
	return str;
}

//used to trim \r\n\t\v\f\" (mostly white space and ") from the left side of a string
string& ltrim(string &str, string const &whitespace = " \r\n\t\v\f\"")
{
	str.erase(0, str.find_first_not_of(whitespace));
	return str;
}

//this function is used to turn a wchar to a string.
//the reason this is done is because the ide mostly supports unicode strings to input into listboxes and such
//unicode strings dont go well with normal data structures and methods.
//thus a string that is taken from a box such as edit which comes out as a unicode string will be
//converted into wchar using c_str() and then toNarrow() will be used subsequently and a string
// will be returned.
string ToNarrow( const wchar_t *s, char dfault = '?',
					  const std::locale& loc = std::locale() )
{
  std::ostringstream stm;

  while( *s != L'\0' ) {
	stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
  }
  return stm.str();
}

//when selecting from the listbox the selected text needs to be split apart to get only the word in the front.
template <class T>
string split(string str, T del){
	  string temp = "";

	  for(int i=0; i<(int)str.size(); i++){
		 if(str[i] != del){
			temp += str[i];
		}
		  else{
			return temp;
			  temp = "";
		}
	}

	  return temp;
}

//The trie data structure implementation
class Trie
{
public:
	//public variables
	bool isLeaf;
	string word;
	string def;
	string type;
	Trie* character[CHAR_SIZE];

	// Constructor
    Trie()
    {
        this->isLeaf = false;

		for (int i = 31; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }

	void insert(string w, string t, string d);
	bool preorderSort(Trie* node);
	bool deletion(Trie*&, string);
	void traversal();
	string update(string, string);
	void prefixSearch(Trie* node, string key);
	bool search(string);
	bool haveChildren(Trie const*);
};

// Iterative function to insert a key into a Trie
void Trie::insert(string key, string type, string def)
{
    // start from the root node
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
		if (curr->character[key[i]] == nullptr) {
			curr->character[key[i]] = new Trie();
		}

		// go to the next node
		curr = curr->character[key[i]];
    }

    // mark the current node as a leaf
	curr->isLeaf = true;
	curr->word = key;
	curr->type = type;
	curr->def = def;
}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie otherwise false
bool Trie::search(string key)
{
	Trie* curr = this;
	string word;
	for (int i = 0; i < key.length(); i++)
	{
		// go to the next node
		curr = curr->character[key[i]];
		// if the string is invalid (reached end of a path in the Trie)
		if (curr == nullptr) {
			return false;
		}
	}

	// return true if the current node is a leaf and the
	// end of the string is reached
	if(curr->isLeaf){
		Dictionary->ListBox1->Items->Add((key + ", " + curr->type + ": " + curr->def).c_str());
	}
	return curr->isLeaf;
}



// Returns true if a given node has any children
bool Trie::haveChildren(Trie const* curr)
{
	for (int i = 31; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return true;    // child found
        }
    }

    return false;
}

// Recursive function to delete a key in the Trie
//done in post-order tree traversal-> right, left, root.
bool Trie::deletion(Trie*& curr, string key)
{
    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }

    if (key.length())
	{
		// recursion for the node to the next character in the key
		// and if it returns true, delete the current node only if not leaf

		if (curr != nullptr && curr->character[key[0]] != nullptr &&
			deletion(curr->character[key[0]], key.substr(1)) && curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
				curr = nullptr;
                return true;
            }
            else {
                return false;
            }
		}
    }

    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
		// if the current node is a leaf node and doesnt have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;

            // delete the non-leaf parent nodes
            return true;
        }

        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            return false;
		}
    }

    return false;
}

//preorder sort -> root, left, right.
bool Trie::preorderSort(Trie* node)
{
    if (node == NULL)
        return false;

	for (int i = 31; i < CHAR_SIZE; i++) {
		if (node->character[i] != NULL) {

			// if leaf node then print key
			if (node->character[i]->isLeaf != false)
				Dictionary->ListBox1->Items->Add((node->character[i]->word + ", " + node->character[i]->type + ": " + node->character[i]->def).c_str());

			//recursive call to dive down into until a leaf is found.
			preorderSort(node->character[i]);
		}
	}
	return true;
}

//choice is used to seperate two different actions in update. showing and updating definition.
string Trie::update(string key, string choice)
{
	Trie* curr = this;
	string word;
	for (int i = 0; i < key.length(); i++)
	{
		// go to the next node
		curr = curr->character[key[i]];
		// if the string is invalid (reached end of a path in the Trie)
		if (curr == nullptr) {
			//nvm is returned and will be declined by the conditional in the code.
			return "nvm";
		}
	}

	// return true if the current node is a leaf and the
	// end of the string is reached
	if(choice == "1"){
		if(curr->isLeaf){
		return (curr->def);
	}
	}

	if(curr->isLeaf){
		curr->def = choice;
	}
	return "nvm";
}

//preorder traversal->root, left, right.
void Trie::traversal(){
	//adds word to drop down list once leaf is found.
	if(this->isLeaf){
		Dictionary->ComboEdit1->Items->Add(this->word.c_str());
		return;
	}

	int v = 31;
	while(v < CHAR_SIZE){
		if(this->character[v] != nullptr){
			//recursively call traversal to traverse from root then right and left.
			this->character[v]->traversal();
		}
		v += 1;
	}
}

//function used to find node to start after key is inputted.
void Trie::prefixSearch(Trie* node, string key){
	int i = 0;
	char k;
	//doesnt go through if text box is empty
	if(key != "") {
		while(i < key.length()){
			k = key[i];
			if(node->character[k] != nullptr){
				node = node->character[k];
			}
			else{
				return;
			}
			i += 1;
		}
		node->traversal();
	}
}

//input full location of dictionary file to use here
ifstream coeff("C:\\Users\\ACER\\Documents\\Hash Table\\Project\\dictionary - Sheet1.csv");
Trie* head = new Trie();

__fastcall TDictionary::TDictionary(TComponent* Owner)
	: TForm(Owner)
{
	int i = 0;
	string alpha1,CD,CL,CY,temp;


	if(coeff.is_open()){
		while(i < size){
			//seperating word, type and definition.
			getline(coeff, alpha1, ',');
			getline(coeff, CL, ',');
			getline(coeff, CD, '\n');
            //inserting word, type and definition trimmed of all whitespace into trie.
			head->insert(rtrim(ltrim(alpha1)), rtrim(ltrim(CL)), rtrim(ltrim(CD)));

			i = i+1;

		}
		coeff.close();
		head->preorderSort(head);
		Dictionary->Edit2->Text = "0.00 ms";
	}

	else{
		Dictionary->ListBox1->Items->Add("Dictionary File not found.");
	};

}
//---------------------------------------------------------------------------






void __fastcall TDictionary::SearchClick(TObject *Sender)
{
	String taskText= ComboEdit1->Text;
	AnsiString text = taskText;
	bool res;
	if(!taskText.IsEmpty()){
		ListBox1->Items->Clear();
		auto sortstart = steady_clock::now();
		res = head->search(text.c_str());
		auto sortend = steady_clock::now();
		double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
		elapsed_time /= 1000000;
		string time = std::to_string(elapsed_time);
		Dictionary->Edit2->Text = (time + " ms").c_str();
		if(res == False){
			ShowMessage("Not Found \t\t\t");
		}
	}
	else{
		ListBox1->Items->Clear();
        auto sortstart = steady_clock::now();
        head->preorderSort(head);
		auto sortend = steady_clock::now();
		double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
		elapsed_time /= 1000000;
		string time = std::to_string(elapsed_time);
		Dictionary->Edit2->Text = (time + " ms").c_str();
		}

	ComboEdit1->Text = "";
	}

//when clicking yes on the insert window
void __fastcall TForm2::InsertionClick(TObject *Sender)
{
	String wordText = Edit2->Text;
	string word = ToNarrow(wordText.c_str());
	String typeText = Edit1->Text;
	string type = ToNarrow(typeText.c_str());
	String defText = Edit3->Text;
	string def = ToNarrow(defText.c_str());
	size += 1;
	auto sortstart = steady_clock::now();
	head->insert(word,type, def);
	auto sortend = steady_clock::now();
	double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
	elapsed_time /= 1000000;
	string time = std::to_string(elapsed_time);
	Dictionary->Edit2->Text = (time + " ms").c_str();
	Dictionary->ListBox1->Items->Add((wordText + ", " + typeText + " : " + defText).c_str());
	Close();
}

//shows the word that is going to be updated
void __fastcall TForm3::UpdateShowClick(TObject *Sender)
{
	String wordText = Edit2->Text;
	string word = ToNarrow(wordText.c_str());
	string res = head->update(word, "1");
	if(res == "nvm"){
		ShowMessage("Not Found \t\t\t");
	}else{
		Edit1->Text = res.c_str();
	}


}

//updates the word that has been found
void __fastcall TForm3::UpdateYesClick(TObject *Sender){
	String wordText = Edit2->Text;
	string word = ToNarrow(wordText.c_str());
	String defText = Edit3->Text;
	string newdef = ToNarrow(defText.c_str());
	auto sortstart = steady_clock::now();
	string res = head->update(word, newdef);
	auto sortend = steady_clock::now();
	double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
	elapsed_time /= 1000000;
	string time = std::to_string(elapsed_time);
	Dictionary->Edit2->Text = (time + " ms").c_str();
	Dictionary->ListBox1->Items->Clear();
	head->preorderSort(head);
	Close();
}

////---------------------------------------------------------------------------

//shows the insert window
void __fastcall TDictionary::InsertClick(TObject *Sender)
{
	TForm2 *Form2;
	Form2 = new TForm2(this);
	Form2->ShowModal();
}
////---------------------------------------------------------------------------


//shows the update window
void __fastcall TDictionary::UpdateClick(TObject *Sender)
{
	TForm3 *Form3;
	Form3 = new TForm3(this);
	Form3->ShowModal();
}
////---------------------------------------------------------------------------

//when clicking on an item in the listbox a window is shown to make sure.
void __fastcall TDictionary::ListBox1ItemClick(TCustomListBox * const Sender, TListBoxItem * const Item)
{
	TForm1 *Form1;
	Form1 = new TForm1(this);
	Form1->ShowModal();
}

//deleting a word
void __fastcall TForm1::YesClick(TObject *Sender)
{
	int i = 0;
	index = Dictionary->ListBox1->Selected->Index;
	String one = Dictionary->ListBox1->Selected->Text;
	string j = split(ToNarrow(one.c_str()), ',');
	Dictionary->ListBox1->Items->Delete(index);
	auto sortstart = steady_clock::now();
	head->deletion(head, j);
	auto sortend = steady_clock::now();
	double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
	elapsed_time /= 1000000;
	string time = std::to_string(elapsed_time);
	Dictionary->Edit2->Text = (time + " ms").c_str();
	size -= 1;
	Close();
}
////---------------------------------------------------------------------------


 //uses preorder sort to display all of the words in the trie alphabetically.
void __fastcall TDictionary::SortClick(TObject *Sender)
{
	int i = 0;
	Dictionary->ListBox1->Clear();
	auto sortstart = steady_clock::now();
	head->preorderSort(head);
	auto sortend = steady_clock::now();
	double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
	elapsed_time /= 1000000;
	string time = std::to_string(elapsed_time);
	Dictionary->Edit2->Text = (time + " ms").c_str();
}
//---------------------------------------------------------------------------

//this function runs whenever someone is typing in the combobox and once called drops down
// a list containing all possible words than can be done.
void __fastcall TDictionary::ComboEdit1Typing(TObject *Sender)
{
	String query = ComboEdit1->Text;
	string word = ToNarrow(query.c_str());
	ComboEdit1->Items->Clear();
	auto sortstart = steady_clock::now();
	head->prefixSearch(head, word);
	auto sortend = steady_clock::now();
	double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
	elapsed_time /= 1000000;
	string time = std::to_string(elapsed_time);
	Dictionary->Edit2->Text = (time + " ms").c_str();
	ComboEdit1->DropDown();
}
//---------------------------------------------------------------------------

