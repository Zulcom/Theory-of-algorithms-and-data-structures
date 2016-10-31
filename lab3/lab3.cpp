#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string findLin(string *inputLines, int n, string search){
	if(inputLines[0] == search) return inputLines[1];
	if(inputLines[n - 1] == search) return inputLines[n - 2];
	for(int i = 0; i < n; ++i)
		if(search == inputLines[i])
			return inputLines[i - 1];
	return "-1";
}
string findBin(string *inputLines, int n, string search)
{
	if(inputLines[0] == search ) return inputLines[1];
	if(inputLines[n - 1] == search) return inputLines[n - 2];
	string midStr;
	int mid, left = 0,
		right = n;
	while(right - left > 1){
		mid = (right + left) / 2;
		midStr = inputLines[mid];
		if(midStr == search) return inputLines[mid - 1];
		if(midStr.length() == search.length())
			for(int i = 0; 0 < search.length();)
				if(midStr[i] == search[i]) ++i;
				else{
					if(midStr[i] > search[i]) right = mid;
					else left = mid;
					break;
				}
		else
			if(midStr.length() > search.length()) right = mid;
			else left = mid;
	}
	return "-1";
}
string(*searches[2])(string*, int, string) = {findLin,findBin};
int main()
{
	ifstream input("test.txt");
	if(!input.is_open())
	{
		cout << "Error handled on file open" << endl;
		system("pause");
		return 0;
	}
	int n;
	input >> n;
	string *inputLines = new string[n];
	for(int i = 0; i < n; ++i) input >> inputLines[i];
	cout << "Lines in file: " << endl;
	for(int i = 0; i < n; ++i) cout << inputLines[i] << endl;
	string search, result;
	cout << "Input what are you serching for: ";
	cin >> search;
	cout << "Inport number of search alorithm:\n1.Linear Search\n2.Binary Search\n";
	int choise;
	cin >> choise;
	while(choise >2 || choise<1)
	{
		cout << "Incorrect number of alogithm, please try again" << endl;
		cout << "Inport number of search alorithm:\n1.Linear Search\nBinary Search\n";
		cin >> choise;
	}
	
	result = searches[choise-1](inputLines, n, search);
	if(result == "-1") cout << "Line not found in file" << endl;
	else cout << "\nClosest line: "<< result << endl;
	system("pause");
	return 0;
}