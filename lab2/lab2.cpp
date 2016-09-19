/*
	Задание: разработать для решения поставленной задачи алгоритм; 
	реализовать полученный алгоритм с использованием линейных структур данных заданных типов.
	Одна из заданных  структур должна быть реализована самостоятельно, без использования готовых библиотек;
	вторая структура может быть как реализована самостоятельно, так и взята из STL. 
	11. Отсортировать числовую последовательность. - Массив / двусвязный список
*/
#include <iostream>
#include <list>
#include <iterator>
using namespace std;


void sort(int * array,int N) {
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(array[i]<array[j]){
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
}
int main() {
	int N;
	cout << "Enter length of sequence:";
	cin >> N;
	int * array = new int[N];
	list<int> myList;
	for(int i = 0; i < N; i++){
		cin >> array[i];
		myList.push_back(array[i]);
	}
	sort(array,N);
	myList.sort();
	for(int i = 0; i < N; i++){
		cout << array[i] << " ";
	}
	cout << endl;
	copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	system("pause.exe");
	return 0;
}
