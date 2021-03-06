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
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TDictionary *Dictionary;
//---------------------------------------------------------------------------
using std::getline;
using std::string;
using std::endl;
using namespace std::chrono;

const int T_S = 10411;
string alpha[1100], bairon[1100], charlie[1100];
int index;
int size = 1040;

string& rtrim(string &str, string const &whitespace = " \r\n\t\v\f\"")
{
	str.erase(str.find_last_not_of(whitespace) + 1);
	return str;
}

string& ltrim(string &str, string const &whitespace = " \r\n\t\v\f\"")
{
	str.erase(0, str.find_first_not_of(whitespace));
	return str;
}

string ToNarrow( const wchar_t *s, char dfault = '?',
					  const std::locale& loc = std::locale() )
{
  std::ostringstream stm;

  while( *s != L'\0' ) {
	stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
  }
  return stm.str();
}

template <class T>
void swapper(T &x, T &y)
  {
	  T temp;
	  temp = x;
	  x = y;
      y = temp;
  }

template <class T>
void selectionSort(T array[], int size)
  {
      int lowestPosition;
	  T lowestValue;

	  for (int i = 0; i < size - 1; i++)
	  {
          lowestValue = array[i];
		  lowestPosition = i;
          for (int j = i + 1; j < size; j++)
		  {
              if (array[j] < lowestValue)
              {
                  lowestPosition = j;
                  lowestValue = array[j];
              }
		  }
          swapper(array[i], array[lowestPosition]);
      }
  }


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

int hashfunc(string key){
	int hash = 0;
	for(int i=0;i < key.size(); i++){
		hash += static_cast<int>(key[i]);
	}
	hash = hash % T_S;
	return hash;
}


class HashTableEntry {
   public:
	  string word;
	  string type;
	  string definition;

	  HashTableEntry(string k, string type, string v) {
		 this->word = k;
		 this->type = type;
		 this->definition = v;
      }
};


class HashMapTable {
   private:
	  HashTableEntry **t;
   public:
	  HashMapTable() {
		 t = new HashTableEntry *[T_S];
		 for (int i = 0; i < T_S; i++) t[i] = NULL;
	  }

	  void Insert(string k, string j, string v) {
		 auto start = steady_clock::now();
		 int h = hashfunc(k);
		 while (t[h] != NULL && t[h]->definition != k) {
			h = (h + 1) % T_S;
		 }
		 if (t[h] != NULL)
			delete t[h];
		 t[h] = new HashTableEntry(k, j, v);
         auto end = steady_clock::now();
		 double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
		 elapsed_time /= 1000000;
		 string time = std::to_string(elapsed_time);
		 Dictionary->Edit2->Text = (time + " ms").c_str();
	  }

	  int SearchKey(string k) {
		 auto start = steady_clock::now();
		 int h = hashfunc(k);
		 string temp;
		 int j;
		 while (t[h] != NULL && t[h]->word != k) {
			j += 1;
			h = (h + 1) % T_S;
		 }
		 Dictionary->Edit3->Text = j;
		 j = 0;
		if (t[h] != NULL){
			auto end = steady_clock::now();
			double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
			elapsed_time /= 1000000;
			string time = std::to_string(elapsed_time);
			Dictionary->Edit2->Text = (time + " ms").c_str();
			return h;
		 }

		 return 0;
	  }

	  void display(int h){
		if(t[h] != NULL && t[h]->word != ""){
			Dictionary->ListBox1->Items->Add((t[h]->word + ", " + t[h]->type + " : " + t[h]->definition).c_str());
		}
	  }

	  string update(string k, string def) {
		 auto start = steady_clock::now();
		 int h = hashfunc(k);
		 string temp;
		 while (t[h] != NULL && t[h]->word != k) {
			h = (h + 1) % T_S;
		 }
		 if(def == "def"){
		 if (t[h] != NULL){
			return t[h]->definition;
		 }
		 }
		 else{
			 t[h]->definition = def;
			 auto end = steady_clock::now();
			 double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
			 elapsed_time /= 1000000;
			 string time = std::to_string(elapsed_time);
			 Dictionary->Edit2->Text = (time + " ms").c_str();
		 }

		 return "nvm";
	  }

	  void ShowAll(){
		int i = 0;
		int word;
		Dictionary->ListBox1->Items->Clear();
		while(i < size){
				word = SearchKey(alpha[i]);
				display(word);
				i += 1;
			}

	  }

	  void deleteElement(string k){
		auto start = steady_clock::now();
		int h = SearchKey(k);
		Dictionary->Edit3->Text = t[h]->word.c_str();
		if (t[h] != NULL && t[h]->word == k){
			delete t[h];
			auto end = steady_clock::now();
			double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
			elapsed_time /= 1000000;
			string time = std::to_string(elapsed_time);
			Dictionary->Edit2->Text = (time + " ms").c_str();
		}
		t[h] = new HashTableEntry("B","O","B");
	  }

};

HashMapTable hash;

ifstream coeff("C:\\Users\\ACER\\Documents\\Hash Table\\Project\\dictionary - Sheet1.csv");

__fastcall TDictionary::TDictionary(TComponent* Owner)
	: TForm(Owner)
{
	int i = 0;
	string alpha1,CD,CL,CY,temp;


	if(coeff.is_open()){
		while(i < size){
			getline(coeff, alpha1, ',');
			alpha[i] = rtrim(ltrim(alpha1));
			getline(coeff, CL, ',');
			bairon[i] = rtrim(ltrim(CL));
			getline(coeff, CD, '\n');
			charlie[i]= rtrim(ltrim(CD));
			hash.Insert(alpha1,CL, CD);
			Dictionary->ListBox1->Items->Add((alpha1 + ", " + CL + " : " + CD).c_str());


			i = i+1;

		}
		coeff.close();
		Dictionary->Edit2->Text = "0.00 ms";
	}

	else{
		Dictionary->ListBox1->Items->Add("Dictionary File not found.");
	};

}
//---------------------------------------------------------------------------






void __fastcall TDictionary::SearchClick(TObject *Sender)
{
	String taskText= Edit1->Text;
	AnsiString text = taskText;
	int res;
	if(!taskText.IsEmpty()){
		ListBox1->Items->Clear();
		res = hash.SearchKey(text.c_str());
		if(res == 0){
			ShowMessage("Not Found \t\t\t");
		}
		else{
			hash.display(res);
		}
	}
	else{
		auto start = steady_clock::now();
		hash.ShowAll();
        auto end = steady_clock::now();
		double elapsed_time = double(duration_cast<nanoseconds> (end-start).count());
		elapsed_time /= 1000000;
		string time = std::to_string(elapsed_time);
		Dictionary->Edit2->Text = (time + " ms").c_str();
		}

	Edit1->Text = "";
	}

void __fastcall TForm2::InsertionClick(TObject *Sender)
{
	String wordText = Edit2->Text;
	string word = ToNarrow(wordText.c_str());
	alpha[size] = rtrim(ltrim(word));
	String typeText = Edit1->Text;
	string type = ToNarrow(typeText.c_str());
	bairon[size] = rtrim(ltrim(type));
	String defText = Edit3->Text;
	string def = ToNarrow(defText.c_str());
	charlie[size] = rtrim(ltrim(def));
	size += 1;
	hash.Insert(word,type, def);
	Dictionary->ListBox1->Items->Add((wordText + ", " + typeText + " : " + defText).c_str());
	Close();
}

void __fastcall TForm3::UpdateShowClick(TObject *Sender)
{
	String wordText = Edit2->Text;
	string word = ToNarrow(wordText.c_str());
	string res = hash.update(word, "def");
	if(res == "nvm"){
		ShowMessage("Not Found \t\t\t");
	}else{
		Edit1->Text = res.c_str();
	}


}

void __fastcall TForm3::UpdateYesClick(TObject *Sender){
	String wordText = Edit2->Text;
	string word = ToNarrow(wordText.c_str());
	String defText = Edit3->Text;
	string newdef = ToNarrow(defText.c_str());
	string res = hash.update(word, newdef);
	int i = 0;
	while(i < size){
		if(word == alpha[i]){
			charlie[i] = newdef;
			Dictionary->ListBox1->Items->Clear();
			hash.ShowAll();
		}
		i += 1;
	}
	Close();
}

//---------------------------------------------------------------------------

void __fastcall TDictionary::InsertClick(TObject *Sender)
{
	TForm2 *Form2;
	Form2 = new TForm2(this);
	Form2->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TDictionary::UpdateClick(TObject *Sender)
{
	TForm3 *Form3;
	Form3 = new TForm3(this);
	Form3->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TDictionary::ListBox1ItemClick(TCustomListBox * const Sender, TListBoxItem * const Item)
{
	TForm1 *Form1;
	Form1 = new TForm1(this);
	Form1->ShowModal();
}

void __fastcall TForm1::YesClick(TObject *Sender)
{
	int i = 0;
	index = Dictionary->ListBox1->Selected->Index;
	String one = Dictionary->ListBox1->Selected->Text;
	string j = split(ToNarrow(one.c_str()), ',');
	while(i < size){
		if(alpha[i] == j){
			index = i;
		}
		i += 1;
	}
	Dictionary->ListBox1->Items->Delete(index);
	hash.deleteElement(rtrim(ltrim(j)));
	while(index < size){
		alpha[index] = alpha[index+1];
		bairon[index] = bairon[index+1];
		charlie[index] = charlie[index+1];
		index += 1;
	}
	size -= 1;
	Close();
}
//---------------------------------------------------------------------------



void __fastcall TDictionary::SortClick(TObject *Sender)
{
	int i = 0;
	auto sortstart = steady_clock::now();
	selectionSort(alpha, size);
	auto sortend = steady_clock::now();
	double elapsed_time = double(duration_cast<nanoseconds> (sortend-sortstart).count());
	elapsed_time /= 1000000;
	string time = std::to_string(elapsed_time);
	Dictionary->ListBox1->Items->Clear();
	int h;
	while(i < size){
		h = hash.SearchKey(alpha[i]);
		if(h != 0){
			hash.display(h);
		}
		i += 1;
	}
	Dictionary->Edit2->Text = (time + " ms").c_str();
}
//---------------------------------------------------------------------------



