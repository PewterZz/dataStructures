//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Delete.h"
#include "cstring"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------