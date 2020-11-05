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
wstring rus_alphabet = L"абвгдежзийклмнопрстуфхцчшщьыэю€";
int most_encr[5] = { -1, -1, -1, -1, -1 };
int most_real[5] = {545, 417, 572, 403, 168};

wstring getting_full_text_in_one_string(wstring filename)
{
	wifstream input(filename);	// Open file
	input.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); // Set file codec to utf8
	wstringstream wss;			// Open stringstream
	wss << input.rdbuf();		// file to stringstream
	return wss.str();			// stringstream to string
}

wstring removing_endls(wstring text)
{
	int position = text.find(L"\n");
	while (position != string::npos)
	{
		text.replace(position, 1, L"");
		position = text.find(L"\n");
	}
	return(text);
}

int gcd(int a, int b)
{
	int q, r;
	while (b > 0)
	{
		q = a / b;
		r = a - q * b;
		a = b;
		b = r;
	}
	return a;
}

int find_inverse_element(int a, int mod)
{
	int inversed = -1;
	int q, r, r1 = a, r2 = mod, t, t1 = 0, t2 = 1;

	while (r2 > 0)
	{
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}

	if (r1 == 1)
		inversed = t1;

	if (inversed < 0)
		inversed = inversed + a;

	return inversed;
}

int modInverse(int a, int m)
{
	int m0 = m;
	int y = 0, x = 1;

	if (m == 1)
		return 0;

	while (a > 1)
	{
		// q is quotient 
		int q = a / m;
		int t = m;

		// m is remainder now, process same as 
		// Euclid's algo 
		m = a % m, a = t;
		t = y;

		// Update y and x 
		y = x - q * y;
		x = t;
	}

	// Make x positive 
	if (x < 0)
		x += m0;

	return x;
}


int find_letter_index(wchar_t letter)
{
	for (int i = 0; i < rus_alphabet.length(); i++)
	{
		if (letter == rus_alphabet[i])
		{
			return i;
		}
	}
	return 0;
}

void count_bigrams_and_frequencies_in_the_text(int **bigram_alphabet, wstring full_text, int step, string file_name)
{
	ofstream file(file_name + ".csv");
	int a = 0;
	int b = 0;
	double p;
	for (int i = 0; i < full_text.length() - step; i += step)
	{
		a = find_letter_index(full_text[i]);
		b = find_letter_index(full_text[i + 1]);
		bigram_alphabet[a][b]++;
	}
	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 31; j++)
		{
			p = (double)bigram_alphabet[i][j]; // full_text.length();
			file << fixed << setprecision(4) << p << ";";
		}
		file << "\n";
	}
	file << endl;
	file.close();
}

void find_five_most_popular(int **bigram_alphabet)
{
	for (int a = 0; a < 5; a++)
	{
		int max = bigram_alphabet[0][0];
		int index = 0;
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 31; j++)
			{
				if ((31 * i + j) == most_encr[0])
				{
					continue;
				}
				if ((31 * i + j) == most_encr[1])
				{
					continue;
				}
				if ((31 * i + j) == most_encr[2])
				{
					continue;
				}
				if ((31 * i + j) == most_encr[3])
				{
					continue;
				}
				if (max < bigram_alphabet[i][j])
				{
					max = bigram_alphabet[i][j];
					index = 31 * i + j;
				}
			}
		}
		if (most_encr[0] == -1) most_encr[0] = index;
		else if (most_encr[1] == -1) most_encr[1] = index;
		else if (most_encr[2] == -1) most_encr[2] = index;
		else if (most_encr[3] == -1) most_encr[3] = index;
		else most_encr[4] = index;
	}
	
}

wstring decryption(int a, int b, wstring text, int mod)
{
	wcout << a << L"   " << b << L"   " << text.substr(0, 10) << "   " << mod << endl;
	int x;
	int y;
	wstring decrypted;
	a = modInverse(a, mod);
	for (int i = 0; i < text.length(); i += 2)
	{
		y = find_letter_index(text[i]) * 31 + find_letter_index(text[i+1]);
		x = a * (y - b);
		while (x < 0) x += mod;
		if (x > mod) x = x % mod;
		decrypted += rus_alphabet[x / 31];
		decrypted += rus_alphabet[x % 31];
	}
	return(decrypted);
}

int solution_of_linear_equations(int a, int b, int mod)
{
	int d;
	int a1, b1, n1, x0; //зм≥нн≥ з формули, об*Їднала пункти 1) ≥ 2.2) в один, бо вони один одного перекривають 
	int inversed;
	d = gcd(a, mod);
	if ((d % b == 0))
	{
		return(-1);
	}
	cout << "gcd be like  " << d << endl;
	a1 = a / d;
	b1 = b / d;
	n1 = mod / d;
	inversed = find_inverse_element(n1, a1);
	cout << "inversed be like  " << inversed << endl;
	x0 = (b1 * inversed) % n1;
	cout << "x0 be like  " << x0 << endl;
	return(x0);
}

void data_for_solution_of_linear_equations(int mod, wstring text)
{
	int a, b, X, Y, x1, x2, z = 0;
	int y1 = most_encr[0];
	int y2 = most_encr[1];
	wstring real_text;
	for (int i = 0; i < 5; i++)
	{
		x1 = most_real[i];
		for (int j = 0; j < 5; j++)
		{
			x2 = most_real[j];
			Y = y1 - y2;
			if (Y < 0) Y += mod;
			X = x1 - x2;
			if (X < 0) X += mod;
			cout << "X: " << X << "  Y: " << Y << endl;
			a = solution_of_linear_equations(X, Y, mod);
			if (a < 0) continue;
			else b = (y1 - a * x1);
			while (b < 0) b += mod;
			real_text = decryption(a, b, text, mod);
			z++;
			cout << "(" << a << ", " << b << ")" << endl;
			wcout << text.substr(0, 50) << endl << endl;
			wcout << real_text.substr(0, 50) << endl << endl;
			real_text = L"";
		}
	}
	cout << "amount of keys  " << z << endl;
}

int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	wstring encrypted_text;
	encrypted_text = getting_full_text_in_one_string(L"D:\\16.txt");
	encrypted_text = removing_endls(encrypted_text);

	int **bigram_alphabet = new int*[31];
	for (int i = 0; i < 31; i++)
	{
		bigram_alphabet[i] = new int[31];
		for (int j = 0; j < 31; j++)
		{
			bigram_alphabet[i][j] = 0;
		}
	}
	count_bigrams_and_frequencies_in_the_text(bigram_alphabet, encrypted_text, 2, "bigram's_frequencies");
	find_five_most_popular(bigram_alphabet);
	for (int i = 0; i < 5; i++)
	{
		cout << most_encr[i] << "  ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << most_real[i] << "  ";
	}
	cout << endl;

	data_for_solution_of_linear_equations(31*31, encrypted_text);
	//wcout << decryption(370, 312, encrypted_text, 31*31) << endl;
	cout << "End Of Program" << endl;
	system("pause");
	return 0;
}