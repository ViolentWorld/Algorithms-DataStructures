#include <iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

class Tree
{
private:

	class Node
	{
	public:

		int Key; 
		int Size; 
		Node* pLeft; 
		Node* pRight; 
		Node* root; 
		Node(int k)
		{
			Key = k;
			pLeft = pRight = root = nullptr;
			Size = 1;
		}
	};

	int GetSize(Node* current) 
	{
		if (!current) return 0;
		return current->Size;
	}

	void FixSize(Node* current) 
	{
		current->Size = GetSize(current->pLeft) + GetSize(current->pRight) + 1;
	}

	Node* Find(Node* current, int k) 
	{
		if (!current) return nullptr;
		if (k == current->Key)
			return current;
		if (k < current->Key)
			return Find(current->pLeft, k);
		else
			return Find(current->pRight, k);
	}

	Node* InsertRoot(Node* current, int k) 
	{
		if (!current)
		{
			current = new Node(k);
			current->root = current;
			return current->root;
		}
		if (k < current->Key)
		{
			current->pLeft = InsertRoot(current->pLeft, k);
			return current;
		}
		else
		{
			current->pRight = InsertRoot(current->pRight, k);
			return current;
		}
	}

	Node* Insert(Node* current, int k) 
	{
		if (!current)
		{
			return  new Node(k);
		}
		if (rand() % (current->Size + 1) == 0)
			return InsertRoot(current, k);
		if (current->Key > k)
			current->pLeft = Insert(current->pLeft, k);
		else if (current->Key < k)
			current->pRight = Insert(current->pRight, k);
		FixSize(current);
		return current;
	}

	Node* Join(Node* current, Node* other) 
	{
		if (!current) return other;
		if (!other) return current;
		if (rand() % (current->Size + other->Size) < current->Size)
		{
			current->pRight = Join(current->pRight, other);
			FixSize(current);
			return current;
		}
		else
		{
			other->pLeft = Join(current, other->pLeft);
			FixSize(other);
			return other;
		}
	}

	Node* Remove(Node* current, int k) 
	{
		if (!current) return current;
		if (current->Key == k)
		{
			Node* temp = Join(current->pLeft, current->pRight);
			delete current;
			current = nullptr;
			return temp;
		}
		else if (k < current->Key)
			current->pLeft = Remove(current->pLeft, k);
		else
			current->pRight = Remove(current->pRight, k);
		return current;
	}

	void SimPrint(Node* current, int tabs) 
	{
		char n = 24;
		if (current)
		{
			tabs += 5;
			SimPrint(current->pLeft, tabs);
			for (long i = 0; i < tabs - 5; i++)
				cout << " ";
			cout << current->Key << endl;
			SimPrint(current->pRight, tabs);
			tabs -= 5;
			return;
		}
		return;
	}

	void BackPrint(Node* current, int tabs) 
	{
		if (current)
		{
			tabs += 5;
			BackPrint(current->pLeft, tabs);
			BackPrint(current->pRight, tabs);
			for (long i = 0; i < tabs; i++)
				cout << " ";
			cout << current->Key << endl;
			tabs -= 5;
			return;
		}
		return;
	}

	void FreeTree(Node* current) 
	{
		if (!current)
			return;
		FreeTree(current->pLeft);
		FreeTree(current->pRight);
		delete current;
		return;
	}

	Node* RemoveRepeatedNode(Node* current, Tree* other) 
	{
		Node* temp = current;
		if (current == nullptr)
			return temp;
		int k = current->Key;
		if (Find(other->current, k) != nullptr)
		{
			current = Remove(k);
			temp = current;
		}
		while (Find(other->current, current->Key) != nullptr)
		{
			current = Remove(current->Key);
			temp = current;
		}
		RemoveRepeatedNode(current->pLeft, other);
		RemoveRepeatedNode(current->pRight, other);
		return temp;
	}

	Node* current; 

public:

	Tree(int k) { current = new Node(k); }

	~Tree() { FreeTree(current); }

	Node* Find(int k) { return Find(current, k); }

	int GetSize() { return GetSize(current); }

	Node* Insert(int k) { current = Insert(current, k); return current; }

	Node* Remove(int k) { current = Remove(current, k);  return current; }

	void SimPrint() { return SimPrint(current, 0); }

	void BackPrint() { return BackPrint(current, 0); }

	Node* RemoveRepeatedNode(Tree* tre) { current = RemoveRepeatedNode(current, tre); return current; }
};



int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	Tree tree(28);
	for (int i = 0; i < 20; i++)
	{
		tree.Insert(rand() % 100);
	}

	Tree tre(-1);
	for (int i = 0; i < 20; i++)
	{
		tre.Insert(rand() % 100);
	}

	tree.SimPrint();
	cout << endl << endl;
	tree.RemoveRepeatedNode(&tre);
	tree.SimPrint();
}