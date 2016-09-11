#include <iostream> // ����-�����
#include <climits> // ������������ ����
#include <algorithm> // ���������

/*
	�������: 11.� ��������� ������������������ ����� ����� ��� ����������� ��������.
	���������� �������� ���� ��������, ������ �������� � ������ ���������� ���������� � ������ �������� �� ������.
*/
/**
	������ ������� ��������� ����� �� a �� ���������� � �������, ����������� ����������� �����������
*/
bool noneq(int a, int min0, int min1, int min2) {	return !(a != min0 && a != min1 && a != min2);}
/**
	����� ���� ����������� ��������� ��� ������������� �������.
*/
void withoutArray(int N) {
	int min0 = INT_MAX, min1 = INT_MAX, min2 = INT_MAX;
	int currentNumber;
	for (int i = 1; i < N + 1; i++){
		std::cout << "Enter number " << i << ": ";std::cin >> currentNumber;
		if (noneq(currentNumber, min0, min1, min2)) continue;
		if (currentNumber < min0) min0 = currentNumber;
		else if (currentNumber < min1) min1 = currentNumber;
		else if (currentNumber < min2) min2 = currentNumber;	
	}
	std::cout << std::endl << "Three minimum numbers (in increase order):" << std::endl;
	std::cout << min0 << " " << min1 << " " << min2 << std::endl;
}
/**
	���������� ������� ��� �������, ������������ ���  ��� ���������� ������
*/
int* fillArray(int N) {
	int* resultArray = new int[N];
	for (int i = 0; i < N; i++){
		std::cout << "Enter number " << i + 1 << ": ";std::cin >> resultArray[i];
	}
	return resultArray;
}
/**
	���������� �������, ��������� ����������� algorithm. � ������������ �������, ��� ���������� �������� ���������� � Intrrosrt
	������� � ������������ ����� ����������, ��� ������ ��������� ������� ���� ������� O(nlogn)
*/
void introsort(int* array, int N) {
	int counter = 0;
	std::sort(array, array + N);
	std::cout << std::endl << "Three minimum numbers (in increase order):" << std::endl;
	//��������� � ������������������ ����� ���������� ���������� ����������� ��������, � ������� ���������� �������� �� �� �����.
	for(int i = 0; i < N && counter<3; i++){
		bool equals = false;
		for(int j = i+1; j < N; j++){
			if(array[i] == array[j]) equals = true;
		}
		if(!equals){
			std::cout << array[i] << " ";
			counter++;
		}
	}
	std::cout << std::endl;
}
/**
	������������ ���������� ���������
*/
void bubblesort(int* array, int N) {
	int counter = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N - 1; j++)
			if (array[j] > array[j + 1]){
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
	std::cout << std::endl << "Three minimum numbers (in increase order):" << std::endl;
	//��������� � ������������������ ����� ���������� ���������� ����������� ��������, � ������� ���������� �������� �� �� �����.
	for(int i = 0; i < N && counter<3; i++){
		bool equals = false;
		for(int j = i + 1; j < N; j++){
			if(array[i] == array[j]) equals = true;
		}
		if(!equals){
			std::cout << array[i] << " ";
			counter++;
		}
	}
	std::cout << std::endl;
}

int main() {
	int N = 0, menuSelector;
	while(true){
		std::cout << "Select function:" << std::endl;
		std::cout << "1. o(n)" << std::endl << "2. O(n logn)" << std::endl << "3.O(n*n)" << std::endl << "4. exit" << std::endl;
		std::cin >> menuSelector;
		if(menuSelector != 4){ std::cout << "Input sequence length: ";std::cin >> N; }
		switch(menuSelector){
			case 1:{
				withoutArray(N);
				break;
			}
			case 2:{
				int* array = fillArray(N);
				introsort(array, N);
				delete[] array;
				break;
			}
			case 3:{
				int* array = fillArray(N);
				bubblesort(array, N);
				delete[] array;
				break;
			}
			case 4:{
				system("pause.exe");
				return 0;
			}
			default: ;
		}
	}
}