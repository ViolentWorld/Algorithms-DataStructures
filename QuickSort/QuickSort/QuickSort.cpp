#include <iostream>
#include "Struct.h"
#include <ctime>
#include <cstdlib>
#include "Windows.h"

using namespace std;

void inverse(MyStack& stack)
{
	MyStack temporary;
	stack.SetCnt(1);
	while (!stack.Empty())
	{
		stack.SetCnt(2);
		temporary.Push(stack.Pop());

	}
	stack = temporary;
	stack.SetCnt(1);
}

void move_stack(MyStack& first, MyStack& stack)
{
	stack.SetCnt(1);
	inverse(first);
	stack.SetCnt(1);
	while (!first.Empty())
	{
		stack.SetCnt(1);
		stack.Push(first.Pop());
		stack.SetCnt(1);
	}
}

void quick_sort(MyStack& stack)
{
	stack.SetCnt(1);
	if (stack.Empty())
	{
		stack.SetCnt(1);
		return;
	}

	MyStack lhs;
	MyStack equal;
	MyStack rhs;

	const auto pivot = stack.Peek(); stack.SetCnt(1);

	stack.SetCnt(1);
	while (!stack.Empty()) {
		const auto value = stack.Peek(); stack.SetCnt(1);

		stack.SetCnt(1);
		if (value < pivot)
		{
			stack.SetCnt(1);
			lhs.Push(value);
		}
		else if (pivot < value)
		{
			stack.SetCnt(2);
			rhs.Push(value);
		}
		else {
			stack.SetCnt(1);
			equal.Push(value);
		}

		stack.Pop();
	}
	stack.SetCnt(1);
	quick_sort(lhs);
	stack.SetCnt(1);
	quick_sort(rhs);

	stack.SetCnt(1);
	move_stack(lhs, stack);
	stack.SetCnt(1);
	move_stack(equal, stack);
	stack.SetCnt(1);
	move_stack(rhs, stack);
}

void Sort(int N)
{
	MyStack stack;
	double t_s, t_f = 0;

	for (int i = 0; i < N; i++)
	{
		stack.Push(rand() % 100);
	}

	stack.NullCnt();

	t_s = GetTickCount();

	quick_sort(stack);

	t_f = GetTickCount();

	cout << "Отсортированно элементов: " << N << " Количество операций: " << stack.GetCnt() << " Время сортировки: " << (t_f - t_s) / 1000.0 << "s." << endl;
}


int main()
{
	int a;
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	Sort(4500);
	Sort(9000);
	Sort(13500);
	Sort(18000);
	Sort(22500);
	Sort(27000);
	Sort(31500);
	Sort(36000);
	Sort(40500);
	Sort(45000);
	std::cin >> a;
	return 0;
}