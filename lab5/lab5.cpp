#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

void sortStupid(int *arr, int n)
{
	for(int i = 0; i < n - 1; ++i)
		if(arr[i]>arr[i + 1]){
			swap(arr[i], arr[i + 1]);
			i = -1;
		}
}



void sortQuick(int *arr, int low, int high)
{
	int i = low;
	int j = high;
	int x = arr[(low + high) / 2];
	do
	{
		while(arr[i] < x) ++i;
		while(arr[j] > x) --j;
		if(i <= j){
			swap(arr[i], arr[j]);
			i++; j--;
		}
	} while(i < j);
	if(low < j) sortQuick(arr, low, j);
	if(i < high) sortQuick(arr, i, high);
}



void merger(int* buf, int l, int r, int m)
{
	if(l >= r || m < l || m > r) return;
	if(r == l + 1 && buf[l] > buf[r]){
		swap(buf[l], buf[r]);
		return;
	}
	int* tmp = new int[r - l + 1];
	for(int i = l, j = 0; i <= r; i++, j++)
		tmp[j] = buf[i];
	for(int i = l, j = 0, k = m - l + 1; i <= r; i++)
	{
		if(j > m - l)      buf[i] = tmp[k++];
		else if(k > r - l) buf[i] = tmp[j++];
		else               buf[i] = (tmp[j] < tmp[k]) ? tmp[j++] : tmp[k++];
	}
}



void sortMerge(int* buf, int l, int r)
{
	if(l >= r) return;
	int m = (l + r) / 2;
	sortMerge(buf, l, m);
	sortMerge(buf, m + 1, r);
	merger(buf, l, r, m);
}



int main()
{
	int n=50;
	//cout << "Enter numbers amunt: ";cin >> n;
	//cout << "Generated number array: " << endl;
	int* arr = new int[n];
	srand(time(0)); // initialize random generator
	for(int i = 0; i < n; ++i){
		arr[i] = rand() % 20 - 10;
		//cout << arr[i] << " ";
	}
	int choice = 3;
	/*while(choice <1 || choice >3){
		cout << "\nChoice sort alogithm:\n1.Stupid sort\n2.Merge sort\n3.Quick sort\n";
		cin >> choice;
	}*/
	system("pause.exe");
	switch (choice){
		case 1: 
		sortStupid(arr, n);
		break;

		case 2:
		sortMerge(arr, 0, n - 1);
		break;

		case 3:
		sortQuick(arr, 0, n - 1);
		break;
	}
	system("pause.exe");
	return 0;
	cout << "Sorted array: \n";
	for(int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}