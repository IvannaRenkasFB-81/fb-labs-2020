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


int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);


	int length_with_trash;
	wstring full_text;
	wstring text;
	wstring first_file_name = L"/Ukrainian.txt";
	wstring second_file_name = L"D:\\Дама с собачкой.txt";

	full_text = getting_full_text_in_one_string(second_file_name);
	wcout << full_text << endl;

	length_with_trash = full_text.length();

	wcout << length_with_trash << endl;
	wcout << "End of program" << endl;
	return 0;
}
