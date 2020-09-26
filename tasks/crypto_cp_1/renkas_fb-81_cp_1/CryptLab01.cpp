#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <codecvt>
#include <locale>
#include <cmath>

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
		//delete extra spaces
		int position = norm_text.find(L"  ");
		while (position != string::npos)
		{
			norm_text.replace(position, 2, L" ");
			position = norm_text.find(L"  ");
		}
		
	}
	return(norm_text);
}

void count_letters_in_the_text(int *alphabet, wstring full_text)
{
	int j = 0;
	for (int i = 0; i < full_text.length(); i++)
	{
		if (full_text[i] == L'ґ')
			alphabet[26]++;
		else if (full_text[i] == L'є')
			alphabet[27]++;
		else if (full_text[i] == L'і')
			alphabet[29]++;
		else if (full_text[i] == L'ї')
			alphabet[32]++;
		else if (full_text[i] == L'ё')
			alphabet[32]++;
		else
		{
			j = full_text[i] - L'а';
			alphabet[j]++;
		}
	}
}

wstring removing_spaces_from_text(wstring full_text)
{
	wstring bufer = full_text;
	int position = bufer.find(L" ");
	while (position != string::npos)
	{
		bufer.replace(position, 1, L"");
		position = bufer.find(L" ");
	}
	return(bufer);
}

double counting_H1(int *alphabet, int length)
{
	double a = 0;
	double p;
	for (int i = 0; i < 33; i++)
	{
		p = (double)alphabet[i] / length;
		if (p != 0)
		{
			a += (p*log2(p));
		}
	}
	return(a * (-1));
}


int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int length_with_spaces;
	int length_without_spaces;
	wstring full_text;
	wstring full_text_without_spaces;
	int *alphabet = new int[33];
	for (int i = 0; i < 33; i++)
	{
		alphabet[i] = 0;
	}

	wstring first_file_name = L"D:\\Ukrainian.txt";
	wstring second_file_name = L"D:\\Дама с собачкой.txt";

	full_text = getting_full_text_in_one_string(first_file_name);
	full_text = normalization_of_string(full_text);
    full_text_without_spaces = removing_spaces_from_text(full_text);
	//АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩҐЄЬІЮЯЇ
	//абвгдежзийклмнопрстуфхцчшщґєьіюяї
	
	count_letters_in_the_text(alphabet, full_text_without_spaces);
	/*wcout << L"а  б  в  г  д  е  ж  з  и  й  к  л  м  н  о  п  р  с  т  у  ф  х  ц  ч  ш  щ  ґ  є  ь  і  ю  я  ї" << endl;
	for (int i = 0; i < 33; i++)
	{
		cout << alphabet[i] << "  ";
	}
	cout << endl;*/
	length_with_spaces = full_text.length();
	length_without_spaces = full_text_without_spaces.length();

	cout << "Using text with spaces: H1 = " << counting_H1(alphabet, length_with_spaces) << endl;
	cout << "Using text without spaces: H1 = " << counting_H1(alphabet, length_without_spaces) << endl;

	wcout << "End of program" << endl;
	return 0;
}
