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


wstring normalization_of_string(wstring full_text) 
{
	wstring norm_text;
	for (int i = 0; i < full_text.length(); i++) 
	{
		int index = full_text[i] - L'А'; 
		//using whitelist
		if (full_text[i] == L'Ґ' || full_text[i] == L'ґ')
			norm_text += L'ґ';
		else if (full_text[i] == L'Є' || full_text[i] == L'є')
			norm_text += L'є';
		else if (full_text[i] == L'І' || full_text[i] == L'і')
			norm_text += L'і';
		else if (full_text[i] == L'Ї' || full_text[i] == L'ї')
			norm_text += L'ї';
		else if (full_text[i] == L'Ё' || full_text[i] == L'ё')
			norm_text += L'ё';
		else if (full_text[i] == L' ' || full_text[i] == L'\n')
			norm_text += L' ';
		else if (index < 64 && index >= 0)
		{
			if (index < 32)
			{
				full_text[i] += 32;
			}
			norm_text += full_text[i];
		}
		//delete spaces
		int position = norm_text.find(L"  ");
		while (position != string::npos)
		{
			norm_text.replace(position, 2, L" ");
			position = norm_text.find(L"  ");
		}
		
	}
	return(norm_text);
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
	int *alphabet = new int[33];
	wstring first_file_name = L"D:\\Ukrainian.txt";
	wstring second_file_name = L"D:\\Дама с собачкой.txt";

	full_text = getting_full_text_in_one_string(first_file_name);
	full_text = normalization_of_string(full_text);

	//АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩҐЄЬІЮЯЇ
	//абвгдежзийклмнопрстуфхцчшщґєьіюяї

	wcout << full_text << endl;
	
	length_with_trash = full_text.length();

	wcout << length_with_trash << endl;
	wcout << "End of program" << endl;
	return 0;
}
