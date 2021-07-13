#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Graph
{
private:

	int** matrix;
	int VertexCount;
	int EdgeCount;

	int* Dikstra(const int& startfrom, const bool& IsNeed);

	int GetRadiusIndex(const int& center);

	void GetChain(const int& radius, const int& startfrom);

	int GetGraphCenter();

public:

	Graph();

	void GetGraphInfo();

	~Graph();

};

Graph::Graph()
{
	int VertexCount;
	int EdgeCount;
	cout << "Количество вершин> "; cin >> VertexCount; cout << endl;
	cout << "Количество дуг> "; cin >> EdgeCount; cout << endl;
	cout << "Матрица инцидентности> ";
	this->matrix = new int* [VertexCount];
	for (int i = 0; i < VertexCount; i++)
	{
		this->matrix[i] = new int[EdgeCount];
	}
	for (int i = 0; i < VertexCount; i++)
	{
		for (int j = 0; j < EdgeCount; j++)
		{
			cin >> matrix[i][j];
		}
	}
	this->VertexCount = VertexCount;
	this->EdgeCount = EdgeCount;

	int amount = 0;
	int j = 0;
	int index1 = 0;
	int index2 = 0;
	int** NewMatrix = new int* [VertexCount];

	for (int i = 0; i < VertexCount; i++)
	{
		NewMatrix[i] = new int[VertexCount];
	}

	for (int i = 0; i < VertexCount; i++)
	{
		for (int j = 0; j < VertexCount; j++)
		{
			if (i == j)
				NewMatrix[i][j] = 0;
			else
				NewMatrix[i][j] = 10000;
		}
	}

	while (j != EdgeCount)
	{
		for (int i = 0; i < VertexCount; i++)
		{
			if (matrix[i][j] > 0)
			{
				index1 = i;
				amount = matrix[i][j];
			}
			if (matrix[i][j] < 0)
				index2 = i;
		}
		NewMatrix[index1][index2] = abs(amount);
		j++;
	}
	for (int i = 0; i < VertexCount; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	this->matrix = NewMatrix;
}

int* Graph::Dikstra(const int& startfrom, const bool& IsNeed)
{
	int big_num(9999);

	int* pos = new int[VertexCount];
	int* node = new int[VertexCount];
	int min(0), index_min(0);
	for (int i = 0; i < VertexCount; i++) {
		pos[i] = big_num;
		node[i] = 0;
	}
	pos[startfrom] = 0;
	for (int i = 0; i < VertexCount - 1; i++) {
		min = big_num;
		for (int j = 0; j < VertexCount; j++) {
			if (!node[j] && pos[j] < min) {
				min = pos[j];
				index_min = j;
			}
		}
		node[index_min] = true;
		for (int j = 0; j < VertexCount; j++) {
			if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num && pos[index_min] + matrix[index_min][j] < pos[j]) {
				pos[j] = pos[index_min] + matrix[index_min][j];
			}
		}
	}
	delete[] node;
	if (IsNeed)
	{
		switch (startfrom)
		{
		case 0:
			cout << endl << "Кратчайшие пути из вершины A" << endl;
			break;
		case 1:
			cout << endl << "Кратчайшие пути из вершины B" << endl;
			break;
		case 2:
			cout << endl << "Кратчайшие пути из вершины C" << endl;
			break;
		case 3:
			cout << endl << "Кратчайшие пути из вершины D" << endl;
			break;
		case 4:
			cout << endl << "Кратчайшие пути из вершины E" << endl;
			break;
		case 5:
			cout << endl << "Кратчайшие пути из вершины F" << endl;
			break;
		case 6:
			cout << endl << "Кратчайшие пути из вершины G" << endl;
			break;
		case 7:
			cout << endl << "Кратчайшие пути из вершины H" << endl;
			break;
		}
		for (int i = 0; i < VertexCount; i++)
		{
			if (pos[i] != 0 && pos[i] != 9999)
				cout << pos[i] << " ";
			if (pos[i] == 9999)
				cout << "Нет пути" << " ";
		}
		cout << endl;
	}

	return pos;
}

int Graph::GetRadiusIndex(const int& center)
{
	int radius = -1;
	int index = 0;
	int* distance = Dikstra(center, false);
	for (int i = 0; i < VertexCount; i++)
	{
		if (distance[i] != 9999 && distance[i] != 0)
		{
			if (distance[i] > radius)
			{
				index = i;
				radius = distance[i];
			}
		}
	}
	delete[] distance;
	return index;
}

int Graph::GetGraphCenter()
{
	int index = 0;
	int count = 0;
	int maxdistance = -1;
	int cent = 10000;
	int* center = new int[VertexCount];
	for (int i = 0; i < VertexCount; i++)
	{
		int* CurrentLine = Dikstra(count, true);
		for (int j = 0; j < VertexCount; j++)
		{
			if (CurrentLine[j] != 9999)
				maxdistance = max(maxdistance, CurrentLine[j]);
		}
		center[count] = maxdistance;
		maxdistance = -1;
		count++;
		delete[] CurrentLine;
	}
	for (int i = 0; i < VertexCount; i++)
	{
		if (center[i] != 0 && center[i] != -1)
		{
			if (center[i] < cent)
			{
				cent = center[i];
				index = i;
			}
		}
	}
	delete[] center;
	switch (index)
	{
	case 0:
		cout << endl << "Центр графа - вершина A" << endl;
		break;
	case 1:
		cout << endl << "Центр графа - вершина B" << endl;
		break;
	case 2:
		cout << endl << "Центр графа - вершина C" << endl;
		break;
	case 3:
		cout << endl << "Центр графа - вершина D" << endl;
		break;
	case 4:
		cout << endl << "Центр графа - вершина E" << endl;
		break;
	case 5:
		cout << endl << "Центр графа - вершина F" << endl;
		break;
	case 6:
		cout << endl << "Центр графа - вершина G" << endl;
		break;
	case 7:
		cout << endl << "Центр графа - вершина H" << endl;
		break;
	}
	return index;
}

void Graph::GetGraphInfo()
{
	int center = GetGraphCenter();
	int radius = -1;
	int* distance = Dikstra(center, false);
	for (int i = 0; i < VertexCount; i++)
	{
		if (distance[i] != 9999)
			radius = max(radius, distance[i]);
	}
	delete[] distance;
	cout << endl << "Внешний радиус графа равен: " << radius << endl;
	GetChain(GetRadiusIndex(center), center);
}

void Graph::GetChain(const int& radius, const int& startfrom)
{
	int big_num(9999);

	int* pos = new int[VertexCount];
	int* node = new int[VertexCount];
	int min(0), index_min(0);
	for (int i = 0; i < VertexCount; i++) {
		pos[i] = big_num;
		node[i] = 0;
	}
	cout << endl << "Цепь: ";
	pos[startfrom] = 0;
	for (int i = 0; i < VertexCount - 1; i++) {
		min = big_num;
		for (int j = 0; j < VertexCount; j++) {
			if (!node[j] && pos[j] < min) {
				min = pos[j];
				index_min = j;
			}
		}
		node[index_min] = true;
		if (index_min != radius)
		{
			switch (index_min)
			{
			case 0:
				cout << "A ";
				break;
			case 1:
				cout << "B ";
				break;
			case 2:
				cout << "C ";
				break;
			case 3:
				cout << "D ";
				break;
			case 4:
				cout << "E ";
				break;
			case 5:
				cout << "F ";
				break;
			case 6:
				cout << "G ";
				break;
			case 7:
				cout << "H ";
				break;
			}
		}
		for (int j = 0; j < VertexCount; j++) {
			if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num && pos[index_min] + matrix[index_min][j] < pos[j]) {
				pos[j] = pos[index_min] + matrix[index_min][j];
			}
		}
	}
	switch (radius)
	{
	case 0:
		cout << "A ";
		break;
	case 1:
		cout << "B ";
		break;
	case 2:
		cout << "C ";
		break;
	case 3:
		cout << "D ";
		break;
	case 4:
		cout << "E ";
		break;
	case 5:
		cout << "F ";
		break;
	case 6:
		cout << "G ";
		break;
	case 7:
		cout << "H ";
		break;
	}
	delete[] pos;
	delete[] node;
	cout << endl << endl;
}

Graph::~Graph()
{
	for (int i = 0; i < VertexCount; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int main()
{
	setlocale(LC_ALL, "ru");

	Graph graph;

	(&graph)->GetGraphInfo();
}