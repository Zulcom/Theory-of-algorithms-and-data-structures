//#include "BinMinHeap.h"
//#include <iostream>
//#include <vector>
//int main()
//{
//	int array[] = {10, 4, 5, 30, 3, 300};
//	int array2[] = {117, 42, 56, 29, 37, 50,48,2,15,1,12};
//
//	BinMinHeap firstBinHeap(array, 6);
//	BinMinHeap secondBinHeap(array2, 11);
//
//	cout << "First binary heap: " << endl;
//	firstBinHeap.Display();
//	cout << endl;
//	cout << "Second binary heap: " << endl;
//	secondBinHeap.Display();
//
//	cout << "Enter level to move from 1 heap to 2 heap:" << endl;
//	int levelToMove;cin >> levelToMove;
//	cout << endl;
//
//	vector<int> nodesOnLevel = firstBinHeap.extractLevel(levelToMove);
//	for(int iNode : nodesOnLevel)secondBinHeap.Insert(iNode);
//
//	
//	cout << "First binary heap after move:" << endl;
//	firstBinHeap.Display();
//	cout << endl;
//	cout << "Second binary heap after move:" << endl;
//	secondBinHeap.Display();
//	cout << endl;
//
//	system("pause.exe");
//	return 0;
//}
