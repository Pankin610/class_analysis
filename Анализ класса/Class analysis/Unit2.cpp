//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <cmath>

using namespace std;

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if (getStudentId(to_string(Edit1->Text)) == -1) {
		ShowMessage("Неправильный формат ввода");
		return;
	}
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
