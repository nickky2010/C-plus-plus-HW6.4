//                                   Курс.Объектно - ориентированное программирование на C++.
//                                           Модуль 6. Динамические структуры данных.
//                                                   Домашнее задание № 4.
// Реализовать базу данных ГАИ по штрафным квитанциям с помощью бинарного дерева. 
// Ключом будет служить номер автомашины, значением узла – список правонарушений. 
// Если квитанция добавляется в первый раз, то в дереве появляется новый узел, а в списке - данные по правонарушению; 
// если нет, то данные заносятся в существующий список.
// Необходимо также реализовать следующие операции:
//    -Полная распечатка базы данных(по номерам машин и списку правонарушений, числящихся за ними).
//    -Распечатка данных по заданному номеру.

#include <windows.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include "Bin_tree.h"
using namespace std;
void check_inter(int &vyb, int min, int max);
void new_record(Tree& Data_Base_GAI, char* car_number);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int vyb = 0, v = 1;
	char c[2];                       // Забираем из потока символ Enter ("\n")
	char car_number[10];             // номер машины
	Tree Data_Base_GAI;
	Elem*f = NULL;
	do {
		system("cls");
		cout << "\t\tБаза данных ГАИ по штрафным квитанциям\n\n";
		if (Data_Base_GAI.GetRoot() != NULL)
		{
			cout << "1 - Добавить квитанцию о правонарушении" << endl;
			cout << "2 - Удалить машину из базы данных" << endl;
			cout << "3 - Распечатка данных по заданному номеру" << endl;
			cout << "4 - Полная распечатка базы данных" << endl;
			cout << "0 - Выход из программы\n";
			cout << "Ваш выбор: ";
			cin >> vyb;
			check_inter(vyb, 0, 4);
			switch (vyb)
			{
			case 1:
				system("cls");
				cin.getline(c, 2);
				cout << "Введите номер машины: \t\t";
				std::cin.getline(car_number, 10);
				new_record(Data_Base_GAI, car_number);
				system("pause");
				break;
			case 2:
				system("cls");
				cin.getline(c, 2);
				cout << "Введите номер машины: \t\t";
				std::cin.getline(car_number, 10);
				if ((f=Data_Base_GAI.Search(Data_Base_GAI.GetRoot(), car_number)) != 0) {
					Data_Base_GAI.Del(f);
					cout << "Данные о машине номер " << car_number << " удалены!\n";
				}
				else cout << "Данные о машине номер " << car_number << " отсутствуют в базе данных!\n";
				system("pause");
				break;
			case 3:
				system("cls");
				cin.getline(c, 2);
				cout << "Введите номер машины: \t\t";
				std::cin.getline(car_number, 10);
				Data_Base_GAI.Print_One(Data_Base_GAI.Search(Data_Base_GAI.GetRoot(), car_number), car_number);
				system("pause");
				break;
			case 4:
				system("cls");
				int j = 0;
				Data_Base_GAI.Print_All(Data_Base_GAI.GetRoot(), j);
				system("pause");
				break;
			}
		}
		else {
			cout << "В базе данных отсутствуют записи о правонарушениях\n";
			cout << "1 - Создать новую базу данных правонарушений\n";
			cout << "0 - Выход из программы\n";
			cout << "Ваш выбор: ";
			cin >> vyb;
			check_inter(vyb, 0, 1);
			switch (vyb)
			{
			case 1:
				system("cls");
				cin.getline(c, 2);                     //Забираем из потока символ Enter ("\n")
				cout << "Введите номер машины: \t\t";
				std::cin.getline(car_number, 10);
				new_record(Data_Base_GAI, car_number);
				while (v) {
					cout << "\n1 - Создать новую запись\n";
					cout << "0 - Вернутся в меню\n";
					cout << "Ваш выбор: ";
					cin >> v;
					check_inter(v, 0, 1);
					if (v) {
						system("cls");
						cin.getline(c, 2);                     //Забираем из потока символ Enter ("\n")
						cout << "Введите номер машины: \t\t";
						std::cin.getline(car_number, 10);
						new_record(Data_Base_GAI, car_number);
					}
				}
				break;
			}
		}
	} while (vyb != 0);
	return 0;
}

void new_record(Tree& Data_Base_GAI, char* car_number)
{
	int CountPenalty;      // количество нарушений
	Elem* Node;
	char c[2];
	cout << "Введите количество нарушений:\t";
	cin >> CountPenalty;
    char **tmpPenalty = new char*[CountPenalty];
	char **tmpDate_Penalty = new char*[CountPenalty];
	cin.getline(c, 2);
	for (int i = 0; i < CountPenalty; i++) {
		cout << "\nВведите описание " << i + 1 << " нарушения:\t";
		tmpPenalty[i] = new char[100];
		std::cin.getline(tmpPenalty[i], 100);
		cout << "Введите дату " << i + 1 << " нарушения:\t";
		tmpDate_Penalty[i] = new char[11];
		std::cin.getline(tmpDate_Penalty[i], 11);
	}
	if (Node=Data_Base_GAI.Search(Data_Base_GAI.GetRoot(), car_number)) {                   // если уже есть запись - дополняем
		bool create = false;
		Data_Base_GAI.Insert_penalty(Node, CountPenalty, tmpPenalty, tmpDate_Penalty, create);
	}
	else {
		Node = new Elem;                                                                    // если нет записи - создаем новую
		Data_Base_GAI.Insert(Node, car_number, CountPenalty, tmpPenalty, tmpDate_Penalty);
	}
	cout << "Новая запись внесена в базу данных!\n";
}

void check_inter(int &vyb, int min, int max)
{
	while (vyb < min || vyb>max) {
		if (vyb < min) cout << "\nНеверно! Вы ввели число менее " << min << " !\n";
		else if (vyb > max) cout << "\nНеверно! Вы ввели число более " << max << " !\n";
		cout << "Повторите ввод!\n";
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ваш выбор: ";
		cin >> vyb;
	}
}