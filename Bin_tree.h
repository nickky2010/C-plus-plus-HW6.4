#pragma once
struct Elem
{
	char car_number[10];   // номер машины
	int CountPenalty;      // количество нарушений
	char** Penalty;        // описание нарушения
	char** Date_Penalty;   // дата нарушения
	Elem* left;
	Elem* right;
	Elem* parent;
};

class Tree
{
	//корень
	Elem* root;
public:
	Tree();
	~Tree();
	//печать указанного узла 
	void Print_One(Elem * Node, char * car_number);
	//печать от указанного узла 
	void Print_All(Elem* Node, int &j);
	//поиск от указанного узла
	Elem* Search(Elem* Node, char* key);
	//min от указанного узла
	Elem* Min(Elem* Node);
	//max от указанного узла
	Elem* Max(Elem* Node);
	//следующий для указанного узла
	Elem* Next(Elem* Node);
	//предыдущий для указанного узла
	Elem* Previous(Elem* Node);
	//вставка узла
	void Insert(Elem * z, char * car_number, int CountPenalty, char **tmpPenalty, char **tmpDate_Penalty);
	//удаление ветки для указанного узла,
	//0 - удаление всего дерева
	void Del(Elem* z = 0);
	//получить корень
	Elem* GetRoot();
	// запись штрафов в узел
	void Insert_penalty(Elem * z, int CountPenalty, char ** tmpPenalty, char ** tmpDate_Penalty, bool create);
};