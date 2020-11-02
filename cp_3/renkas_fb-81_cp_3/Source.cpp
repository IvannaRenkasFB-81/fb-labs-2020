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
wstring rus_alphabet = L"אבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";

wstring getting_full_text_in_one_string(wstring filename)
{
	wifstream input(filename);	// Open file
	input.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); // Set file codec to utf8
	wstringstream wss;			// Open stringstream
	wss << input.rdbuf();		// file to stringstream
	return wss.str();			// stringstream to string
}

int find_inverse_element(int a, int mod)
{

	int b = mod;
	int c = 0;
	int d = 1;
	int e = 0;
	int f = 0;
	if (mod == 1)
		return 0;
	while (a > 1)
	{
		e = a / mod;
		f = mod;
		mod = a % mod;
		a = f;
		f = c;
		c = d - e * c;
		d = f;
	}

	if (d < 0)
		d += b;
	return d;
}

int find_letter_index(wchar_t letter)
{
	if (letter == L'¸')
		return(32);
	else if (letter == L' ')
		return(33);
	else
	{
		return(letter - L'א');
	}
}

void count_bigrams_and_frequencies_in_the_text(int **bigram_alphabet, wstring full_text, int step, string file_name)
{
	ofstream file(file_name + ".csv");
	int a = 0;
	int b = 0;
	double p;
	wchar_t first = L'א';
	for (int i = 0; i < full_text.length() - step; i += step)
	{
		a = find_letter_index(full_text[i]);
		b = find_letter_index(full_text[i + 1]);
		bigram_alphabet[a][b]++;
	}
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			p = (double)bigram_alphabet[i][j] / full_text.length();
			file << fixed << setprecision(4) << p << ";";
		}
		file << "\n";
		if (first == L'ÿ')
		{
			first = L'¸';
		}
		else if (first == L'¸')
		{
			first = L'_';
		}
		else first++;
	}
	file << endl;
	file.close();
}

int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	wstring encrypted_text;
	encrypted_text = getting_full_text_in_one_string(L"D:\\16.txt");

	int **bigram_alphabet = new int*[31];
	for (int i = 0; i < 30; i++)
	{
		bigram_alphabet[i] = new int[31];
		for (int j = 0; j < 30; j++)
		{
			bigram_alphabet[i][j] = 0;
		}
	}
	count_bigrams_and_frequencies_in_the_text(bigram_alphabet, encrypted_text, 2, "bigram's_frequencies");

	cout << "End Of Program" << endl;
	system("pause");
	return 0;
}