#pragma once
struct Elem
{
	char car_number[10];   // ����� ������
	int CountPenalty;      // ���������� ���������
	char** Penalty;        // �������� ���������
	char** Date_Penalty;   // ���� ���������
	Elem* left;
	Elem* right;
	Elem* parent;
};

class Tree
{
	//������
	Elem* root;
public:
	Tree();
	~Tree();
	//������ ���������� ���� 
	void Print_One(Elem * Node, char * car_number);
	//������ �� ���������� ���� 
	void Print_All(Elem* Node, int &j);
	//����� �� ���������� ����
	Elem* Search(Elem* Node, char* key);
	//min �� ���������� ����
	Elem* Min(Elem* Node);
	//max �� ���������� ����
	Elem* Max(Elem* Node);
	//��������� ��� ���������� ����
	Elem* Next(Elem* Node);
	//���������� ��� ���������� ����
	Elem* Previous(Elem* Node);
	//������� ����
	void Insert(Elem * z, char * car_number, int CountPenalty, char **tmpPenalty, char **tmpDate_Penalty);
	//�������� ����� ��� ���������� ����,
	//0 - �������� ����� ������
	void Del(Elem* z = 0);
	//�������� ������
	Elem* GetRoot();
	// ������ ������� � ����
	void Insert_penalty(Elem * z, int CountPenalty, char ** tmpPenalty, char ** tmpDate_Penalty, bool create);
};