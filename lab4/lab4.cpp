#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node
{
	friend class HashTableChaining;
	Node* next;
	int data;
public:
	Node() {}
	Node(int d, Node* n)
	{
		data = d;
		next = n;
	}
	~Node() {}
};

class HashTableChaining
{
public:
	int size;
	vector<Node*>* Nodes;

	HashTableChaining(int tableSize)
	{
		size = tableSize;
		Nodes = new vector<Node*>(size);
	}
	~HashTableChaining() {}

	void push(int data);
	void remove(int data);
	bool isContains(int data);
	int getSize()const;
	int getKey(int data)const;
	void display() const;

};
int HashTableChaining::getKey(int data)const { return abs(data % getSize()); }
int HashTableChaining::getSize() const{ return size; }
void HashTableChaining::push(int data)
{
	int key = getKey(data); // определяем ключ, в который будет добавленны данные
	if(Nodes->at(key) == NULL) // если у этого ключа нет записей ..
	{
		Nodes->at(key) = new Node(data, NULL); // .. всунуть туда запись с новыми данынми.
		return;
	}
	for(Node* iNode = Nodes->at(key);iNode != NULL;iNode = iNode->next)
	{
		if(iNode->next == NULL) // если текущая запись последняя (т.е. не имеет ссылку на сл.запись)...
		{
			iNode->next = new Node(data, NULL); // ...добавляем к ней ещё одну запись.
			break;
		}
	}
}

void HashTableChaining::remove(int data)
{
	int index = getKey(data);
	for(Node* pos = Nodes->at(index); pos; pos = pos->next)
	{
		if(pos->data == data)
		{
			for(Node* prev = Nodes->at(index); prev; prev = prev->next)
			{
				if(prev->data == pos->data)
				{
					Nodes->at(index) = pos->next;
					return;
				}
				if(prev->next == pos)
				{
					prev->next = pos->next;
					delete pos;
					return;
				}
			}
		}
	}
}

bool HashTableChaining::isContains(int data)
{
	for(Node* iNode = Nodes->at(getKey(data)); iNode != NULL; iNode = iNode->next)
	{
		if(iNode->data == data)
			return true;
	}
	return false;
}

void HashTableChaining::display() const
{
	for(int i = 0; i < Nodes->size(); i++) //пробегаем по всем ключам
	{
		cout << "[" << i << "]" << " => "; // выводим текуший ключ
		
		Node* iNode = Nodes->at(i); // т.к в на одном ключе могут быть несколько записей, выводим их все.
		while(iNode != NULL) // пока существует запись
		{
			cout << iNode->data << " "; // вывести из неё данные
			iNode = iNode->next; // перейти к следущей
		}
		cout << endl;
	}
}

class HashTableOpenAdressing : public HashTableChaining
{
public:
	int size;
	int* table;

	HashTableOpenAdressing(int sizeTable): HashTableChaining(sizeTable)
	{
		size = sizeTable + 2;
		table = new int[size + 2];
		for(int i = 0; i < size; ++i)
			table[i] = 0;
	}
	~HashTableOpenAdressing() {}

	void push(int data);
	void remove(int data);
	int findIndex(int data);
	void display() const;

};

void HashTableOpenAdressing::push(int data)
{
	int index = getKey(data) - 1;
	if(table[index] == 0) // если по этому индексу место свободно
		table[index] = data; // записать данные прямо в него
	else
		for(int i = index + 1;i <= size;i++)
		{
			if(i == size) i = 0; // если мы добежали до конца массива, начинаем бежать снова
			if(i == index) break; // если во время пробежки мы достигли начальной точки, то всё, мест нет.
			if(table[i] == 0) // если есть место после этого индекса - записать в это свободное место
			{
				table[i] = data;
				return;
			}
		}
}

void HashTableOpenAdressing::remove(int data)
{
	int index = getKey(data) - 1;
	bool flag = false;
	while(index < size)
	{
		if(table[index] == data)
		{
			table[index] = -1;
			flag = true;
			break;
		}
		index++;
	}

	if(flag)
		return;

	int i = 0;
	while(i < index)
	{
		if(table[i] == data)
		{
			table[i] = -1;
			break;
		}
		index++;
	}
}

int HashTableOpenAdressing::findIndex(int data)
{
	int index = getKey(data) - 1;
	for(int i = index;i <= size;i++)
	{
		if(i == size) i = 0; // если мы добежали до конца массива, начинаем бежать снова
		if(i == index-1) break; // если во время пробежки мы достигли начальной точки, то всё, мест нет.
		if(table[i] == data)
			return i;
	}
	return 0;
}

void HashTableOpenAdressing::display()const
{
	for(int i = 0; i < size; i++)
	{
		cout << "[" << i+1 << "]" << " => ";
		cout << table[i] << endl;
	}
}

int main()
{
	//HashTableChaining hash(10);
	HashTableOpenAdressing hash(10);
	ifstream inputFile("test.txt");

	int nRow, temp;
	inputFile >> nRow;
	cout << "Make hash table from test.txt: " <<endl;
	for(int i = 0; i <nRow; i++){
		inputFile >> temp;
		hash.push(temp);
	}
	hash.display();

	int searchData, pushData, removeData;
	cout << "\nWhat are you searching for: ";
	cin >> searchData;
	if(typeid(hash) == typeid(HashTableChaining))
	{
		if(hash.isContains(searchData))
			cout << "[" << hash.getKey(searchData) << "]" << " => " << searchData << endl;
		else cout << "Hash table doesn't contains that data." << endl;
	}
	else
	{
		int finded = hash.findIndex(searchData);
		if(finded)
			cout << "[" << finded+1 << "]" << " => " << searchData << endl;
		else cout << "Hash table doesn't contains that data." << endl;
	}
	cout << "\nWhat data would you like to add?: ";
	cin >> pushData;
	hash.push(pushData);
	cout << "Data key: [" << hash.getKey(pushData) << "]" <<endl;
	cout << "Updated Hash table:" << endl;
	hash.display();

	cout << "\nWhat data would you like to remove?: ";
	cin >> removeData;
	hash.remove(removeData);
	cout << "\nUpdated Hash table: \n";
	hash.display();

	system("pause");
	return 0;
}