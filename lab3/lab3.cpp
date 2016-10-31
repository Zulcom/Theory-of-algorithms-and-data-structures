#include <iostream>
#include <conio.h>
#include <ctime>
#include <clocale>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


string find(string *array, int n, string myStr)
{
	if(myStr == array[0]) return array[1];
	if(array[n - 1] == myStr) return array[n - 2];

	for(int i = 0; i < n; ++i)
	{
		if(myStr == array[i])
		{
			return array[i - 1];
		}
	}
	return "no";
}

string findBin(string *array, int n, string myStr)
{
	if(myStr == array[0]) return array[1];
	if(array[n - 1] == myStr) return array[n - 2];

	string midStr;
	int mid, left = 0,
		right = n;
	while((right - left) > 1)
	{
		mid = (right + left) / 2;
		midStr = array[mid];
		if(midStr == myStr)
		{
			return array[mid - 1];
		}
		else if(midStr.length() == myStr.length())
		{
			for(int i = 0; 0 < myStr.length();)
			{
				if(midStr[i] == myStr[i]) ++i;
				else if(midStr[i] > myStr[i]) { right = mid; break; }
				else { left = mid; break; }
			}
		}
		else
		{
			if(midStr.length() > myStr.length()) right = mid;
			else left = mid;
		}
	}
	return "no";
}

string findInter(string *array, int n, string myStr)
{
	if(array[0] == myStr) return array[1];
	if(array[n - 1] == myStr) return array[n - 2];

	int index,
		l, r;
	string str = array[0];
	for(int i = 0; i < n; ++i)
	{
		if(array[i].length() == myStr.length())
		{
			l = i;
			break;
		}
	}
	for(int i = n - 1; i > 0; --i)
	{
		if(array[i].length() == myStr.length())
		{
			r = i;
			break;
		}
	}

	while(array[l] <= myStr && array[r] >= myStr)
	{
		index = l + ((myStr[0] - array[l][0])*(r - l)) / (array[r][0] - array[l][0]);
		if(array[index] == myStr) return array[index - 1];
		if(array[index]<myStr) l = index;
		else if(array[index]>myStr) r = index;
	}
	return "no";
}

int main()
{
	setlocale(LC_ALL, "russian");

	ifstream file("test.txt");
	if(!file.is_open())
	{
		cout << "Невозможно открыть файл" << endl;
		system("pause");
		return 0;
	}

	int n;
	file >> n;

	string *arrStr = new string[n];
	for(int i = 0; i < n; ++i)
	{
		file >> arrStr[i];
	}

	cout << "Данные из файла: " << endl;
	for(int i = 0; i < n; ++i)
	{
		cout << arrStr[i] << endl;
	}
	string myStr, findStrBin, findStrInter, findStr;
	cout << "Введите искомую строку: ";
	cin >> myStr;

	cout << "\nНаиболее близкий к искомому элемент " << endl;

	findStr = find(arrStr, n, myStr);
	if(findStr == "no")
		cout << "Данного элемента не существует." << endl << endl;
	cout << "Последовательный поиск: " << findStr << endl << endl;

	findStrBin = findBin(arrStr, n, myStr);
	if(findStrBin == "no")
		cout << "Данного элемента не существует." << endl << endl;
	cout << "Двоичный поиск: " << findStrBin << endl << endl;

	findStrInter = findInter(arrStr, n, myStr);
	if(findStrBin == "no")
		cout << "Данного элемента не существует." << endl << endl;
	cout << "Интерполирующий поиск: " << findStrInter << endl << endl;

	system("pause");
	return 0;
}