#include <iostream>
#include <clocale>
#include <conio.h>
#include <ctime>
#include <queue>

using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	int height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

int height(node* p)
{
	return p ? p->height : 0;
}

int mustBalanced(node* p)
{
	return height(p->right) - height(p->left);
}

void fixHeight(node* p)
{
	int heightLeft = height(p->left);
	int heightRight = height(p->right);
	p->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

node* rotateRight(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

node* rotateLeft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixHeight(p);
	if(mustBalanced(p) == 2)
	{
		if(mustBalanced(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if(mustBalanced(p) == -2)
	{
		if(mustBalanced(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
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

void printTree(node *p, int n)
{
	if(p->right) printTree(p->right, n + 1);

	for(int i = 0; i < n; i++)
		cout << " ";
	cout << p->key << endl;

	if(p->left) printTree(p->left, n + 1);
}

void keep(node *root, queue<int> *nodes, queue<int> *nodeslvl, int beg, int num)
{
	if(beg == num && root != NULL)
	{
		nodeslvl->push(root->key);
	}
	if(beg > num)
	{
		if(root == NULL) return;
		nodes->push(root->key);
		keep(root->left, nodes, nodeslvl, beg + 1, num);
		keep(root->right, nodes, nodeslvl, beg + 1, num);
	}
	else
	{
		if(root == NULL) return;
		keep(root->left, nodes, nodeslvl, beg + 1, num);
		keep(root->right, nodes, nodeslvl, beg + 1, num);
	}
}

node *cleantree(node *root, int beg, int num)
{
	if(beg == num - 1 && root != NULL)
	{
		root->left = NULL;
		root->right = NULL;
		return root;
	} 
	if(root != NULL)
	{
		root->left = cleantree(root->left, beg + 1, num);
		root->right = cleantree(root->right, beg + 1, num);
	}
	return root;
}

int main()
{
	setlocale(LC_ALL, "rus");

	int n;
	cout << "Введите количество узлов дерева: ";
	cin >> n;

	node *root = NULL;
	//int k;
	cout << "Введите значения ключей:\n";
	for(int i = 0; i < n; ++i)
	{
	//	cin >> k;
		root = insert(root, rand()%10);
	}

	cout << "Построенное дерево:\n";
	printTree(root, 0);
	cout << endl;

	int num;
	cout << "Введите номер уровня: ";
	cin >> num;

	queue<int> nodes, nodeslvl;
	keep(root, &nodes, &nodeslvl, 1, num);

	node* root2 = NULL;
	int size = nodeslvl.size();
	for(int i = 0; i < size; ++i)
	{
		root2 = insert(root2, nodeslvl.front());
		nodeslvl.pop();
	}

	root = cleantree(root, 1, num); // очищаем дерево с заданного уровня

	size = nodes.size();
	for(int i = 0; i < size; ++i) // перезаписываем первоначальное дерево
	{
		root = insert(root, nodes.front());
		nodes.pop();
	}

	cout << "\nОбновлённое первое дерево:\n";
	printTree(root, 0);

	cout << "\n\nВторое дерево с элементами с заданного уровня первого дерева:\n";
	printTree(root2, 0);

	system("pause.exe");
	return 0;
}