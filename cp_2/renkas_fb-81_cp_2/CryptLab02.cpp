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
		int index = full_text[i] - L'À';
		//using whitelist
		if (full_text[i] == L'¨' || full_text[i] == L'¸')
			norm_text += L'¸';
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
	}
	//delete extra spaces
	int position = norm_text.find(L"  ");
	while (position != string::npos)
	{
		norm_text.replace(position, 2, L" ");
		position = norm_text.find(L"  ");
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


int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	wstring full_text;
	wstring full_text_without_spaces;

	wstring file_name = L"D:\\text.txt";
	cout << "Reading text...  ";
	full_text = getting_full_text_in_one_string(file_name);
	cout << "done" << endl << "Normalization of the text in process...   ";
	full_text = normalization_of_string(full_text);
	cout << "done" << endl << "Removing all spaces....";
	full_text = removing_spaces_from_text(full_text);
	cout << "done" << endl;

	//àáâãäåæçèéêëìíîïðñòóôõö÷øù´ºü³þÿ¿
	int *alphabet = new int[34];
	for (int i = 0; i < 34; i++)
	{
		alphabet[i] = 0;
	}

	int **bigram_alphabet = new int*[34];
	for (int i = 0; i < 34; i++)
	{
		bigram_alphabet[i] = new int[34];
		for (int j = 0; j < 34; j++)
		{
			bigram_alphabet[i][j] = 0;
		}
	}

	system("pause");
	return 0;
}
