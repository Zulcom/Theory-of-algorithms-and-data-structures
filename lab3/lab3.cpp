/*
Реализовать двоичный поиск наиболее близкого к заданному элементу среди отсортированных символьных строк, хранящихся в файле.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
	ifstream input("./tests/scba1.txt"); // открываем файл на чтение
	int N;
	input >> N; // считаываем количество строк
	vector<string> inpvec(N); // создаем контейнер под эти строки
	for(int i = 0; i < N; i++){ // считываем их
		string temp;
		getline(input, temp);
		inpvec[i]=temp;
	}
	input.close(); // не забываем закрыть поток чтения, он нам больше ни к чему.
	int upBound=N;
	int botBound= 0;
	int averageIndex = 0;
	string searchValue;
	cout << "Enter value what you searching for: " << endl;
	getline(cin, searchValue);
	while(botBound < upBound)
	{
		averageIndex = ((upBound - botBound) / 2); //чеееее блядь?
		searchValue.compare(inpvec[averageIndex]) <= 0 ? upBound = averageIndex : botBound = averageIndex + 1;
	}
	cout << inpvec[averageIndex];

}
