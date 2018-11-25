//                                   ����.�������� - ��������������� ���������������� �� C++.
//                                           ������ 6. ������������ ��������� ������.
//                                                   �������� ������� � 4.
// ����������� ���� ������ ��� �� �������� ���������� � ������� ��������� ������. 
// ������ ����� ������� ����� ����������, ��������� ���� � ������ ��������������. 
// ���� ��������� ����������� � ������ ���, �� � ������ ���������� ����� ����, � � ������ - ������ �� ��������������; 
// ���� ���, �� ������ ��������� � ������������ ������.
// ���������� ����� ����������� ��������� ��������:
//    -������ ���������� ���� ������(�� ������� ����� � ������ ��������������, ���������� �� ����).
//    -���������� ������ �� ��������� ������.

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
	char c[2];                       // �������� �� ������ ������ Enter ("\n")
	char car_number[10];             // ����� ������
	Tree Data_Base_GAI;
	Elem*f = NULL;
	do {
		system("cls");
		cout << "\t\t���� ������ ��� �� �������� ����������\n\n";
		if (Data_Base_GAI.GetRoot() != NULL)
		{
			cout << "1 - �������� ��������� � ��������������" << endl;
			cout << "2 - ������� ������ �� ���� ������" << endl;
			cout << "3 - ���������� ������ �� ��������� ������" << endl;
			cout << "4 - ������ ���������� ���� ������" << endl;
			cout << "0 - ����� �� ���������\n";
			cout << "��� �����: ";
			cin >> vyb;
			check_inter(vyb, 0, 4);
			switch (vyb)
			{
			case 1:
				system("cls");
				cin.getline(c, 2);
				cout << "������� ����� ������: \t\t";
				std::cin.getline(car_number, 10);
				new_record(Data_Base_GAI, car_number);
				system("pause");
				break;
			case 2:
				system("cls");
				cin.getline(c, 2);
				cout << "������� ����� ������: \t\t";
				std::cin.getline(car_number, 10);
				if ((f=Data_Base_GAI.Search(Data_Base_GAI.GetRoot(), car_number)) != 0) {
					Data_Base_GAI.Del(f);
					cout << "������ � ������ ����� " << car_number << " �������!\n";
				}
				else cout << "������ � ������ ����� " << car_number << " ����������� � ���� ������!\n";
				system("pause");
				break;
			case 3:
				system("cls");
				cin.getline(c, 2);
				cout << "������� ����� ������: \t\t";
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
			cout << "� ���� ������ ����������� ������ � ���������������\n";
			cout << "1 - ������� ����� ���� ������ ��������������\n";
			cout << "0 - ����� �� ���������\n";
			cout << "��� �����: ";
			cin >> vyb;
			check_inter(vyb, 0, 1);
			switch (vyb)
			{
			case 1:
				system("cls");
				cin.getline(c, 2);                     //�������� �� ������ ������ Enter ("\n")
				cout << "������� ����� ������: \t\t";
				std::cin.getline(car_number, 10);
				new_record(Data_Base_GAI, car_number);
				while (v) {
					cout << "\n1 - ������� ����� ������\n";
					cout << "0 - �������� � ����\n";
					cout << "��� �����: ";
					cin >> v;
					check_inter(v, 0, 1);
					if (v) {
						system("cls");
						cin.getline(c, 2);                     //�������� �� ������ ������ Enter ("\n")
						cout << "������� ����� ������: \t\t";
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
	int CountPenalty;      // ���������� ���������
	Elem* Node;
	char c[2];
	cout << "������� ���������� ���������:\t";
	cin >> CountPenalty;
    char **tmpPenalty = new char*[CountPenalty];
	char **tmpDate_Penalty = new char*[CountPenalty];
	cin.getline(c, 2);
	for (int i = 0; i < CountPenalty; i++) {
		cout << "\n������� �������� " << i + 1 << " ���������:\t";
		tmpPenalty[i] = new char[100];
		std::cin.getline(tmpPenalty[i], 100);
		cout << "������� ���� " << i + 1 << " ���������:\t";
		tmpDate_Penalty[i] = new char[11];
		std::cin.getline(tmpDate_Penalty[i], 11);
	}
	if (Node=Data_Base_GAI.Search(Data_Base_GAI.GetRoot(), car_number)) {                   // ���� ��� ���� ������ - ���������
		bool create = false;
		Data_Base_GAI.Insert_penalty(Node, CountPenalty, tmpPenalty, tmpDate_Penalty, create);
	}
	else {
		Node = new Elem;                                                                    // ���� ��� ������ - ������� �����
		Data_Base_GAI.Insert(Node, car_number, CountPenalty, tmpPenalty, tmpDate_Penalty);
	}
	cout << "����� ������ ������� � ���� ������!\n";
}

void check_inter(int &vyb, int min, int max)
{
	while (vyb < min || vyb>max) {
		if (vyb < min) cout << "\n�������! �� ����� ����� ����� " << min << " !\n";
		else if (vyb > max) cout << "\n�������! �� ����� ����� ����� " << max << " !\n";
		cout << "��������� ����!\n";
		cin.clear();
		while (cin.get() != '\n');
		cout << "��� �����: ";
		cin >> vyb;
	}
}