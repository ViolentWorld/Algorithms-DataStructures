#include <iostream>

class MyStack
{
private:

	class MyVector
	{
	private:

		int* items;
		int length;

	public:

		unsigned long long int cnt;

		MyVector()
		{
			length = 0;
			items = new int[length];
			cnt = 0;
		}

		int Size()
		{
			cnt++;
			return length;
		}

		void Push(int item)
		{
			int* newVector = new int[length + 1]; cnt += 5;
			for (int i = 0; i < length; i++)
			{
				newVector[i] = items[i]; cnt += 5;
			}
			cnt++;
			newVector[length] = item; cnt++;
			length++; cnt++;
			delete[] items; cnt++;
			items = newVector; cnt++;
		}

		int Pop()
		{
			int* newVector = new int[length - 1]; cnt += 5;
			for (int i = 0; i < length - 1; i++)
			{
				newVector[i] = items[i]; cnt += 5;
			}
			cnt++;
			int item = items[length - 1]; cnt += 2;
			length--; cnt += 2;
			delete[] items; cnt++;
			items = newVector; cnt += 2;
			return item;
		}

		void PrintVector()
		{
			for (int i = 0; i < length; i++)
			{
				std::cout << items[i] << " "; cnt += 5;
			}
			cnt++;
			std::cout << std::endl; cnt++;
		}

		int& operator[] (const int index)
		{
			cnt += 2;
			return items[index];
		}
	};

	MyVector items;
	int count;

public:

	MyStack()
	{
		count = 0;
	}

	bool Empty()
	{
		if (count == 0)
		{
			return true;
		}
		return false;
	}

	int Size()
	{
		return count;
	}

	void Push(int item)
	{
		items.Push(item);
		count++;
	}

	int Pop()
	{
		count--;
		return items.Pop();
	}

	int Peek()
	{
		return items[items.Size() - 1];
	}

	void Print()
	{
		items.PrintVector();
	}

	long long int GetCnt()
	{
		return items.cnt;
	}

	void SetCnt(int k)
	{
		items.cnt += k;
	}

	void NullCnt()
	{
		items.cnt = 0;
	}

	int& operator[] (const int index)
	{
		return items[index];
	}
};