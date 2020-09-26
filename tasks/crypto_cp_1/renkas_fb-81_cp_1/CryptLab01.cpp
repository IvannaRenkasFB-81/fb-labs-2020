#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <codecvt>
#include <locale>

using namespace std;

wstring getting_full_text_in_one_string(wstring filename)
{
	wifstream input(filename);	// Open file
	input.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); // Set file codec to utf8
	wstringstream wss;			// Open stringstream
	wss << input.rdbuf();		// file to stringstream
	return wss.str();			// stringstream to string
}

void count_letters_in_the_text(int alphabet[33], wstring full_text)
{
	int j = 0;
	for (int i = 0; i < full_text.length(); i++)
	{
		j = full_text[i] - L'a';
		alphabet[j]++;
	}
}


int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);


	int length_with_trash;
	wstring full_text;
	wstring text;
	int *alphabet = new int [33];
	wstring first_file_name = L"/Ukrainian.txt";
	wstring second_file_name = L"D:\\Дама с собачкой.txt";

	full_text = getting_full_text_in_one_string(second_file_name);
	
	for (int i = 0; i < full_text.length(); i++)
	{
		//АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩҐЄЬІЮЯЇ
		//абвгдежзийклмнопрстуфхцчшщґєьіюяї

		int index = 0;
		if (full_text[i] == L'Ґ' || full_text[i] == L'ґ')
			alphabet[26]++;
		else if (full_text[i] == L'Є' || full_text[i] == L'є')
			alphabet[27]++;
		else if (full_text[i] == L'І' || full_text[i] == L'і')
			alphabet[29]++;
		else if (full_text[i] == L'Ї' || full_text[i] == L'ї')
			alphabet[32]++;
		else if (full_text[i] == L'Ё' || full_text[i] == L'ё')
			alphabet[32]++;
		else
		{
			index = full_text[i] - L'А';
			if (index >= 32)
				index -= 32;
			alphabet[index]++;
		}
	}
	wcout << "TEXT:" << endl;
	wcout << full_text << endl << endl;
	wcout << L"А Б В Г Д Е Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ґ Є Ь І Ю Я Ї" << endl;
	for (int i = 0; i < 33; i++)
	{
		cout << alphabet[i] << " ";
	}

	count_letters_in_the_text(alphabet, full_text);

	length_with_trash = full_text.length();

	wcout << length_with_trash << endl;
	wcout << "End of program" << endl;
	return 0;
}
