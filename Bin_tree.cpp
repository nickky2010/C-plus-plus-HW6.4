#include <windows.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Bin_tree.h"
using namespace std;

Tree::Tree()
{
	root = NULL;
}
Tree::~Tree()
{
	Del();
}
void Tree::Print_One(Elem* Node, char * car_number)
{
	if (Node != 0)
	{
		cout << "\n==================================================\n";
		cout << "Машина регистрационный номер: " << Node->car_number << setw(21 - strlen(Node->car_number)) << "|\n";
		cout << "==================================================\n";
		for (int i = 0; i < Node->CountPenalty; i++)
		{
			cout << "Нарушение: " << Node->Penalty[i] << setw(28 - strlen(Node->Penalty[i])) << "Дата: " << Node->Date_Penalty[i] << "|\n";
			if (i + 1 == Node->CountPenalty) cout << "==================================================\n\n";
		}
	}
	else if (Node == 0) cout << "Запись о правонарушениях по номеру " << car_number << " отсутствует\n\n";
}

//Рекурсивный обход дерева 
void Tree::Print_All(Elem* Node, int &j)
{
	if (Node != 0) {
		Print_All(Node->left, j);
		int otst = 0;
		++j;
		for (int tmp = j; tmp > 0;) { tmp /= 10; otst++; }
		cout << "====================================================\n";
		cout << j << ". Машина регистрационный номер: " << Node->car_number << setw(21 - strlen(Node->car_number) - otst) << "|\n";
		cout << "====================================================\n";
		for (int i = 0; i < Node->CountPenalty; i++)
		{
			cout << "Нарушение: " << Node->Penalty[i] << setw(30-strlen(Node->Penalty[i])) << "Дата: " << Node->Date_Penalty[i] << "\n";
			if (i + 1 == Node->CountPenalty) cout << endl;
		}
		Print_All(Node->right, j);
	}
}

Elem* Tree::Search(Elem* Node, char* k)
{
	//Пока есть узлы и ключи не совпадают
	while (Node != 0 && strcmp(k, Node->car_number) != 0)
	{
		if (strcmp(k, Node->car_number)<0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	return Node;
}

Elem* Tree::Min(Elem* Node)
{
	//Поиск самого "левого" узла
	if (Node != 0)
		while (Node->left != 0)
			Node = Node->left;
	return Node;
}

Elem* Tree::Max(Elem* Node)
{
	//Поиск самого "правого" узла
	if (Node != 0)
		while (Node->right != 0)
			Node = Node->right;
	return Node;
}

Elem* Tree::Next(Elem* Node)
{
	Elem* y = 0;
	if (Node != 0)
	{
		//если есть правый потомок
		if (Node->right != 0)
			return Min(Node->right);
		//родитель узла
		y = Node->parent;
		//если Node не корень и Node справа
		while (y != 0 && Node == y->right)
		{
			//Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem* Tree::Previous(Elem* Node)
{
	Elem* y = 0;
	if (Node != 0)
	{
		//если есть левый потомок
		if (Node->left != 0)
			return Max(Node->left);
		//родитель узла
		y = Node->parent;
		//если Node не корень и Node слева
		while (y != 0 && Node == y->left)
		{
			//Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem* Tree::GetRoot()
{
	return root;
}

void Tree::Insert_penalty(Elem* z, int CountPenalty, char **tmpPenalty, char **tmpDate_Penalty, bool create)
{
	
	char **tPenalty, **tDate_Penalty;
	if (create) {
		z->Penalty = new char*[CountPenalty];
		z->Date_Penalty = new char*[CountPenalty];
		for (int i = 0; i < CountPenalty; i++) {
			z->Penalty[i] = new char[strlen(tmpPenalty[i]) + 1];
			strcpy_s(z->Penalty[i], strlen(tmpPenalty[i]) + 1, tmpPenalty[i]);
			z->Date_Penalty[i] = new char[strlen(tmpDate_Penalty[i]) + 1];
			strcpy_s(z->Date_Penalty[i], strlen(tmpDate_Penalty[i]) + 1, tmpDate_Penalty[i]);
		}
	}
	else 
	{
		tPenalty = new char*[z->CountPenalty+CountPenalty];
		tDate_Penalty = new char*[z->CountPenalty + CountPenalty];
		for (int j = 0; j < z->CountPenalty; j++) {
			tPenalty[j] = new char[strlen(z->Penalty[j]) + 1];
			strcpy_s(tPenalty[j], strlen(z->Penalty[j]) + 1, z->Penalty[j]);
			tDate_Penalty[j] = new char[strlen(z->Date_Penalty[j]) + 1];
			strcpy_s(tDate_Penalty[j], strlen(z->Date_Penalty[j]) + 1, z->Date_Penalty[j]);
		}
		for (int j = 0; j < z->CountPenalty; j++) {
			delete z->Penalty[j];
			delete z->Date_Penalty[j];
		}
		delete z->Penalty;
		delete z->Date_Penalty;
		z->Penalty = tPenalty;
		z->Date_Penalty = tDate_Penalty;
		for (int i = z->CountPenalty, j = 0; i < z->CountPenalty + CountPenalty; i++, j++) {
			z->Penalty[i] = new char[strlen(tmpPenalty[j]) + 1];
			strcpy_s(z->Penalty[i], strlen(tmpPenalty[j]) + 1, tmpPenalty[j]);
			z->Date_Penalty[i] = new char[strlen(tmpDate_Penalty[j]) + 1];
			strcpy_s(z->Date_Penalty[i], strlen(tmpDate_Penalty[j]) + 1, tmpDate_Penalty[j]);
		}
		z->CountPenalty += CountPenalty;
	}
}

void Tree::Insert(Elem* z, char* car_number, int CountPenalty, char **tmpPenalty, char **tmpDate_Penalty)
{
	z->left = NULL;
	z->right = NULL;    
	Elem* y = NULL;
	Elem* Node = root;
	bool create = true;
	strcpy_s(z->car_number, strlen(car_number)+1, car_number);
	z->CountPenalty = CountPenalty;
	if (z->CountPenalty > 0) {
		Insert_penalty(z, z->CountPenalty, tmpPenalty, tmpDate_Penalty, create);
	}
	//поиск места
	while (Node != 0)
	{
		//будущий родитель
		y = Node;
		if (strcmp(z->car_number, Node->car_number)<0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	//заполняем родителя
	z->parent = y;
	if (y == 0) //элемент первый (единственный)
		root = z;
	//чей ключ больше?
	else
		if (strcmp(z->car_number, y->car_number)<0)
			y->left = z;
		else
			y->right = z;
}

void Tree::Del(Elem* z)
{
	//удаление куста
	if (z != 0)
	{
		Elem* Node;
		Elem* y;
		//не 2 ребенка
		if (z->left == 0 || z->right == 0)
			y = z;
		else
			y = Next(z);
		if (y->left != 0)
			Node = y->left;
		else
			Node = y->right;
		if (Node != 0)
			Node->parent = y->parent;
		//Удаляется корневой узел?
		if (y->parent == 0)
			root = Node;
		else
			if (y == y->parent->left)
				//слева от родителя?
				y->parent->left = Node;
			else
				//справа от родителя?
				y->parent->right = Node;
		if (y != z)
		{
			//Копирование данных узла
			strcpy_s(z->car_number, strlen(y->car_number)+1, y->car_number);
			if (z->CountPenalty>0)
				for (int i = 0; i < z->CountPenalty; i++) {
					delete z->Penalty[i];
					delete z->Date_Penalty[i];
				}
			z->CountPenalty = y->CountPenalty;
			z->Penalty = y->Penalty;
			z->Date_Penalty = y->Date_Penalty;
			if (z->CountPenalty > 0) {
				z->Penalty = new char*[z->CountPenalty];
				z->Date_Penalty = new char*[z->CountPenalty];
				for (int i = 0; i < z->CountPenalty; i++) {
					z->Penalty[i] = new char [strlen(y->Penalty[i])+1];
					z->Date_Penalty[i] = new char[strlen(y->Date_Penalty[i]) + 1];
					strcpy_s(z->Penalty[i], strlen(y->Penalty[i])+1, y->Penalty[i]);
					strcpy_s(z->Date_Penalty[i], strlen(y->Date_Penalty[i])+1, y->Date_Penalty[i]);
				}
			}
		}
		delete y->Penalty;
		delete y->Date_Penalty;
		delete y;
	}
	else //удаление всего дерева
		while (root != 0)
			Del(root);
}
