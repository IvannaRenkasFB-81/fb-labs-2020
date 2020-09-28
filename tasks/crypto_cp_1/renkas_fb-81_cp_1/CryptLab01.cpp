#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <codecvt>
#include <locale>
#include <cmath>
#include <iomanip>

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

int find_letter_index(wchar_t letter)
{
	if (letter == L'ґ')
		return(26);
	else if (letter == L'є')
		return(27);
	else if (letter == L'і')
		return(29);
	else if (letter == L'ї')
		return(32);
	else if (letter == L'ё')
		return(32);
	else if (letter == L' ')
		return(33);
	else
	{
		return(letter - L'а');
	}
}

void count_letters_in_the_text(int *alphabet, wstring full_text)
{
	int j = 0;
	for (int i = 0; i < full_text.length(); i++)
	{
		j = find_letter_index(full_text[i]);
		alphabet[j]++;
	}
}

double counting_H1(int *alphabet, int length)
{
	double a = 0;
	double p;
	cout << "Probability of each letter" << endl;
	wcout << L"а\tб\tв\tг\tд\tе\tж\tз\tи\tй\tк" << endl;
	for (int i = 0; i < 33; i++)
	{
		p = (double)alphabet[i] / length;
		cout << fixed << setprecision(4) << p << "\t";
		if (i == 10)
		{
			wcout << endl << L"л\tм\tн\tо\tп\tр\tс\tт\tу\tф\tх" << endl;
		}
		if (i == 21)
		{
			wcout << endl << L"ц\tч\tш\tщ\tґ\tє\tь\tі\tю\tя\tї" << endl;
		}
		if (p != 0)
		{
			a += (p*log2(p));
		}
	}
	cout << endl;
	return(a * (-1));
} 

void count_bigrams_in_the_text(int **bigram_alphabet, wstring full_text, int step)
{
	int a = 0;
	int b = 0;
	for (int i = 0; i < full_text.length() - step; i+=step)
	{
		a = find_letter_index(full_text[i]);
		b = find_letter_index(full_text[i+1]);
		bigram_alphabet[a][b]++;
	}
}

double counting_H2(int **bigram_alphabet, int length, int spaces)
{
	double a = 0;
	double p;
	/*cout << "Probability of each letter" << endl;
	wcout << L"а\tб\tв\tг\tд\tе\tж\tз\tи\tй\tк" << endl;*/
	for (int i = 0; i < 33 + spaces; i++)
	{
		for (int j = 0; j < 33 + spaces; j++)
		{
			p = (double)bigram_alphabet[i][j] / length;
			//cout << fixed << setprecision(4) << p << "\t";
			/*if (i == 10)
			{
				wcout << endl << L"л\tм\tн\tо\tп\tр\tс\tт\tу\tф\tх" << endl;
			}
			if (i == 21)
			{
				wcout << endl << L"ц\tч\tш\tщ\tґ\tє\tь\tі\tю\tя\tї" << endl;
			}*/
			if (p != 0)
			{
				a += (p*log2(p));
			}
		}
	}
	cout << endl;
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

	wstring first_file_name = L"D:\\Ukrainian.txt";
	wstring second_file_name = L"D:\\Дама с собачкой.txt";

	full_text = getting_full_text_in_one_string(second_file_name);
	full_text = normalization_of_string(full_text);
    full_text_without_spaces = removing_spaces_from_text(full_text);
	length_with_spaces = full_text.length();
	length_without_spaces = full_text_without_spaces.length();
	//АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩҐЄЬІЮЯЇ
	//абвгдежзийклмнопрстуфхцчшщґєьіюяї
	int *alphabet = new int[33];
	for (int i = 0; i < 33; i++)
	{
		alphabet[i] = 0;
	}
	count_letters_in_the_text(alphabet, full_text_without_spaces);
	
	cout << "Using text with spaces: H1 = " << counting_H1(alphabet, length_with_spaces) << endl;
	cout << "Using text without spaces: H1 = " << counting_H1(alphabet, length_without_spaces) << endl;

	int **bigram_alphabet = new int*[34];
	for (int i = 0; i < 34; i++)
	{
		bigram_alphabet[i] = new int[34];
		for (int j = 0; j < 34; j++)
		{
			bigram_alphabet[i][j] = 0;
		}
	}
	count_bigrams_in_the_text(bigram_alphabet, full_text_without_spaces, 1);
	cout << "Using text with spaces and intersections: H2 = " << counting_H2(bigram_alphabet, length_with_spaces - 1, 1);
	cout << "Using text with intersections and without spaces: H2 = " << counting_H2(bigram_alphabet, length_without_spaces - 1, 0);

	count_bigrams_in_the_text(bigram_alphabet, full_text_without_spaces, 2);
	cout << "Using text with spaces and without intersections: H2 = " << counting_H2(bigram_alphabet, length_with_spaces - 1, 1);
	cout << "Using text without intersections and spaces: H2 = " << counting_H2(bigram_alphabet, length_without_spaces - 1, 0) << endl;
	wcout << "End of program" << endl;
	return 0;
}
