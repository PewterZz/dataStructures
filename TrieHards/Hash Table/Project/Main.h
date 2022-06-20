//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Menus.hpp>
#include <FMX.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDictionary : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TListBox *ListBox1;
	TButton *Button1;
	TLabel *Label2;
	TImage *Image2;
	TButton *Button2;
	TButton *Button4;
	TButton *Button5;
	TLabel *Label3;
	TEdit *Edit2;
	TLabel *Label4;
	TEdit *Edit3;
	TLabel *Label5;
	void __fastcall SearchClick(TObject *Sender);
	void __fastcall InsertClick(TObject *Sender);
	void __fastcall UpdateClick(TObject *Sender);
	void __fastcall ListBox1ItemClick(TCustomListBox * const Sender, TListBoxItem * const Item);
	void __fastcall SortClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TDictionary(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDictionary *Dictionary;
//---------------------------------------------------------------------------
#endif
