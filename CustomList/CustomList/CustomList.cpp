#include <iostream>

using namespace std;

template<typename T>
class List
{
public:

	List();
	~List();
	void Add(T DATA, int pos);
	void Delete(int pos);
	void FindAndAdd(T DATA, T Value);
	int GetSize() { return Size; }
	T& operator[](const int index);
	void Print();

private:

	template<typename T>
	class Node
	{
	public:

		Node* pNext;
		T DATA;
		Node* pPrev;

		Node(T DATA = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->DATA = DATA;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

	};

	int Size;
	Node <T>* head;
};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
void List<T>::Add(T DATA, int pos)
{
	if (head == nullptr)
	{
		this->head = new Node<T>(DATA);
	}
	else
	{
		Node <T>* current = this->head;

		for (int i = 0; i < pos - 1; i++)
		{
			if (current->pNext == nullptr)
			{
				cout << "указанная позиция некорректна" << endl;
				return;
			}
			current = current->pNext;
		}
		Node<T>* temp = current->pPrev;

		if (pos == Size)
		{
			current->pNext = new Node<T>(DATA, nullptr, current);
		}
		else if (pos == 0)
		{
			current->pPrev = new Node<T>(DATA, current);
			this->head = current->pPrev;
		}
		else
		{
			current->pPrev = new Node<T>(DATA, current, temp);
			temp->pNext = current->pPrev;
		}
	}
	Size++;
	cout << "\nЭлемент добавлен...\n\n";
}

template<typename T>
void List<T>::Delete(int pos)
{
	if (this->head == nullptr)
	{
		cout << "\nСписок пуст\n\n";
		return;
	}
	Node<T>* current = this->head;
	for (int i = 0; i < pos; i++)
	{
		if (current->pNext == nullptr)
		{
			cout << "указанная позиция некорректна" << endl;
			return;
		}
		current = current->pNext;
	}
	if (pos == Size - 1)
	{
		current->pPrev->pNext = nullptr;
		delete current;
	}
	else if (pos == 0)
	{
		head = current->pNext;
		current->pNext->pPrev = nullptr;
		delete current;
	}
	else
	{
		current->pPrev->pNext = current->pNext;
		current->pNext->pPrev = current->pPrev;
		delete current;
	}
	Size--;
}

template<typename T>
void List<T>::FindAndAdd(T DATA, T Value)
{
	if (head == nullptr)
	{
		this->head = new Node<T>(DATA);
		cout << "Список был пуст, новый элемент добавлен";
		cout << endl;
	}
	else
	{
		Node<T>* current = head;
		while (current->DATA != Value)
		{
			if (current->pNext == nullptr)
			{
				cout << "Данного элемента нет в списке" << endl;
				return;
			}
			current = current->pNext;
		}
		if (current->pNext == nullptr)
		{
			current->pNext = new Node<T>(DATA, nullptr, current);
		}
		else
		{
			Node<T>* temp = current->pNext;
			current->pNext = new Node<T>(DATA, temp, current);
			temp->pPrev = current->pNext;
		}
		Size++;
	}


}

template<typename T>
void List<T>::Print()
{
	if (head == nullptr)
	{
		cout << "Список пуст";
		return;
	}

	Node<T>* current = this->head;
	for (int i = 0; i < Size; i++)
	{
		cout << current->DATA << " ";
		current = current->pNext;
	}
	cout << endl;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->DATA;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
List<T>::~List()
{
	Node<T>* current = head;
	while (Size != 1)
	{
		current = current->pNext;
		delete current->pPrev;
		Size--;
	}
	delete current;
	head = nullptr;
}

int main()
{
	setlocale(LC_ALL, "Rus");
}