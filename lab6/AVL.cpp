#include <iostream>
#include <clocale>
#include <vector>
#include "BinMinHeap.h"
#include <queue>
using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	 char hl = height(p->left);
	 char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if(bfactor(p) == 2)
	{
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) == -2)
	{
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if(!p) return new node(k);
	if(k<p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

void printTree(node *p)
{
	if(p != NULL)
	{
		cout << p->key << " ";
		printTree(p->left);
		printTree(p->right);
	}
}

void keep(node *root, vector<int> *nodes, int beg, int num)
{
	if(beg > num)
	{
		if(root == NULL) return;
		nodes->push_back(root->key);
		root->key = 0;
		keep(root->left, nodes, beg + 1, num);
		keep(root->right, nodes, beg + 1, num);
	}
	else
	{
		keep(root->left, nodes, beg + 1, num);
		keep(root->right, nodes, beg + 1, num);
	}
}

node *tree2(node *root, int beg, int num, node *root2)
{
	if(beg == num)
	{
		root2 = insert(root2, root->key);
		return root2;
	}
	else
	{
		root2 = tree2(root->left, beg + 1, num, root2);
		root2 = tree2(root->right, beg + 1, num, root2);
	}
}

node *cleantree(node *root, int beg, int levelToMove)
{
	if(beg > levelToMove)
	{
		if(root == NULL) return root;
		if(root->key == 0)
			root->left = NULL;
			root->right = NULL;
			return root;
	}
	else
	{
		cleantree(root->left, beg + 1,levelToMove);
		cleantree(root->right,beg + 1, levelToMove);
	}
}

int main()
{

	int array[] = {10, 4, 5, 30, 3, 300};
	int array2[] = {117, 42, 56, 29, 37, 50,48,2,15,1,12};
	
	BinMinHeap firstBinHeap(array, 6);
	BinMinHeap secondBinHeap(array2, 11);
	
	cout << "First binary heap: " << endl;
	firstBinHeap.Display();
	cout << endl;
	cout << "Second binary heap: " << endl;
	secondBinHeap.Display();
	
	cout << "Enter level to move from 1 heap to 2 heap:" << endl;
	int levelToMove;cin >> levelToMove;
	cout << endl;
	
	vector<int> nodesOnLevel = firstBinHeap.extractLevel(levelToMove);
	for(int iNode : nodesOnLevel)secondBinHeap.Insert(iNode);
	
		
	cout << "First binary heap after move:" << endl;
	firstBinHeap.Display();
	cout << endl;
	cout << "Second binary heap after move:" << endl;
	secondBinHeap.Display();
	cout << endl;



	// AVL TREES 



	node* root = NULL;
	node* root2 = NULL;
	for(int i = 0; i < 6; ++i)
		root = insert(root, array[i]);

	cout << "First AVL Tree:\n";
	printTree(root);
	cout << endl;

	int leveltoMove;
	cout << "Enter level to move from 1 heap to 2 heap: ";
	cin >> leveltoMove;

	vector<int> nodes;
	keep(root, &nodes, 1, leveltoMove); 
	for(int i = 0; i < nodes.size(); ++i)
		root2 = insert(root2, nodes.at(i));

	root = cleantree(root, 1, leveltoMove); // очищаем дерево с заданного уровня

	cout << "\nFirst AVL tree:\n";
	printTree(root);
	cout << endl;
	cout << "\nSecond AVL tree with moved nodes:\n";
	printTree(root2);

	system("pause.exe");
	return 0;
}