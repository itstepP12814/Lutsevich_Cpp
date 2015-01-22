//Использование бинарного дерева для хранения результатов игр команд английского чемпионата по футболу.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

struct Elem {
	int OwnerPoints; // очки хозяина
	int OppPoints;  // очки противника
	char Match[10];   //Счет матча
	char Name[20];    // Имя команды
	char Opponent[20];  //Имя соперника
	Elem *left, *right, *parent;
};

class Tree {
	Elem *root;     // корень
public:
	Tree() { root = NULL; }
	~Tree(){Del();}
	void Print(Elem *Node);// Печать от указанного узла
	Elem* Search(Elem *Node, char *key); // Поиск от указанного узла
	Elem* Min(Elem *Node); // найти минимальный элемент от указанного узла
	Elem* Max(Elem *Node); // найти максимальный элемент от указанного узла
	Elem* Next(Elem *Node); // найти следующий элемент для указанного узла
	Elem* Previous(Elem *Node); // найти предыдущий элемент для указанного узла
	void Insert(Elem *Ins);  // Вставка узла
	void Del(Elem *Node = 0); //удаление ветки для указанного узла, если 0 - всего дерева
	Elem* GetRoot(){ return root; } // Получить корень
};

// Рекурсивный обход дерева
void Tree::Print(Elem *Node){
	if (Node){
		Print(Node->left);
		cout << Node->Name<<Node->Match<<Node->Opponent << endl;
		Print(Node->right);
	}
}

Elem* Search(Elem *Node, char *key){
	Elem *Src = Node;
	while (Src != NULL && strcmp(key, Src->Name)!=0){
		if (strcmp(key, Src->Name) > 0)
			Src = Src->right;
		else
			Src = Src->left;
	}
	return Src;
}

Elem* Tree::Min(Elem *Node){ // Поиск самого "левого" узла
	Elem *temp = Node;
	if (temp)   // Node!=0
		while (temp->left)
			temp = temp->left;
	return temp;
}

Elem* Tree::Max(Elem *Node){ // Поиск самого "правого" узла
	Elem *temp = Node;
	if (temp)   // Node!=0
		while (temp->right)
			temp = temp->right;
	return temp;
}

Elem* Tree::Next(Elem *Node){
	Elem* Nxt = NULL; // узел, который мы ищем (который следующий) // NULL нужно задать до if для случая, когда Nxt вообще не будет (элемент будет и так крайний)
	if (Node){
		//1 Если есть правый потомок
		if (Node->right)
			Nxt = Min(Node->right);
		else {//2 Если правого потомка нет, то нужно вернуться хотя бы на узел выше (к родителю)
			Elem *preNxt = Node; //  временный указатель для осуществления перебора
			Nxt = preNxt->parent;// 2 Если мы вышли из левой ветки и родитель не NULL, то это и есть следующий узел
			while (Nxt != NUL&&preNxt == Nxt->right){  //3 Движемся дальше вверх (пока родитель не будет NULL или  пока мы выходим из правой ветки, ВАЖНО чтобы условия были именно в такой ПОСЛЕДОВАТЛЬНОСТИ ) 
				preNxt = Nxt;
				Nxt = Nxt->parent;
			}
		}
	}
	return Nxt;
}

Elem* Tree::Previous(Elem* Node){
	Elem *Prv = NULL;
	if (Node) {
		if (Node->left) // 1 Если есть левый потомок, то предыд элемент - это максимальный элемент из левой ветки
			Prv = Max(Node->left);
		else { 
			Elem *prePrv = Node;
			Prv = prePrv->parent; // 2 Если мы вернулись из правой ветки и родитель не NULL
			while (Prv != NULL&&prePrv == Prv->left){
				prePrv = Prv; Prv = Prv->parent;   // поднимаемся вверх
			}
		}
	}
	return Prv;
}

void Tree::Insert(Elem *Ins){
	Elem* preIns = NULL; // узел к которому будем "пристыковывать" данные (пристыковочный узел)
	Elem* temp = root; // временный указатель для осуществления перебора
	// 1 Поиск узла для "пристыковки"
	while (temp) { // temp!=NULL  
		preIns = temp;
		if (strcmp(Ins->Name, temp->Name) >= 0)
			temp = temp->right;
		else
			temp = temp->left;
	}
	//2 Устанавливаем указатели у вставляемого узла
	Ins->parent = preIns; // родитель вставляемого узла
	Ins->left = Ins->right = NULL;  // у вставляемого узла нет потомков
	//3 Устанавливаем указатели у "пристыковочного" узла в дереве
	if (preIns == NULL) // если добавляем элемент первый раз
		root = Ins;
	else if (strcmp(Ins->Name, preIns->Name) >= 0)
		preIns->right = Ins;
	else
		preIns->left = Ins;
}

void Tree::Del(Elem *d){
	if (d) {  // удаление куста
		Elem *y = NULL, *Node = NULL; //УДАЛЯЕМЫЙ узел и узел после удаляемого

		// ОПРЕДЕЛИМ УДАЛЯЕМЫЙ УЗЕЛ (физически память которого будет delete)
		if (d->left == NULL || d->right == NULL){ // 1 потомок или 0 
			y = d;
		} else // 2 потомка - удалим следующий узел (у него обязательно не будет !!левого!! потомка)
			y = Next(d);

		// ОПРЕДЕЛИМ УКАЗАТЕЛИ связанные с узлом Node
		if (y->left) // здесь учтено,что для случая с двумя потомками левого потомка точно не будет, т.е.этот if точно не сработает
			Node = y->left;
		else if (y->right) 
			Node = y->right;
		if (Node) 
			Node->parent = y->parent;
		
		// ПЕРЕОПРЕДЕЛИМ УКАЗАТЕЛИ  C УЧЕТОМ УДАЛЕННОГО y
		if (y->parent == NULL)
			root = Node;
		else if (y == y->parent->left)
			y->parent->left = Node;
		else // if (y == y->parent->right)
			y->parent->right = Node;

		if (y != d){
			strcpy(d->Match, y->Match);
			strcpy(d->Name, y->Name);
			strcpy(d->Opponent, y->Opponent);
			d->OppPoints = y->OppPoints;
			d->OwnerPoints = y->OwnerPoints;
		}
		delete y;
		// вариант кода с четко расписанными тремя ситуациями, из которого получен код выше
		/*Elem *Node = NULL; // временный указатель на элемент после удаляемого
		Elem *y = NULL; // временный указатель на удаляемый элемент
		if (d->left != NULL  && d->right != NULL){
			y = Next(d);

			if (y->right)
			    Node = y->right;

			if (Node)
			    Node->parent = y->parent;

			if (y->parent == NULL)
			    root = NULL;
			else if (y == y->parent->left)
			    y->parent->left = Node;
			else if (y == y->parent->right)
			    y->parent->right = Node;

			strcpy(d->Name, y->Name);
			strcpy(d->Opponent, y->Opponent);
			strcpy(d->Match, y->Match);
			d->OppPoints = y->OppPoints;
			d->OwnerPoints = y->OwnerPoints;
		} else	if (d->left == NULL && d->right == NULL){
			y = d;

			if (y->parent == NULL)
			    root = Node;
			else if (y == y->parent->left)
			    y->parent->left = NULL;
			else if (y == y->parent->right)
			    y->parent->right = NULL;
		} else if (d->left == NULL || d->right == NULL){
			y = d;

			if (y->left)
			    Node = y->left;
			else if (y->right)
			    Node = y->right;

			if (Node)
			    Node->parent = y->parent;

			if (y->parent == NULL)
			    root = Node;
			else if (y == y->parent->left)
			     y->parent->left = Node;
			else if (y == y->parent->right)
			     y->parent->right = Node;
		}
		delete y;*/
	}
	else {
		while (root)
			Del(root);
	}
}

Tree tournament;  // Турнирная таблица

void Game(char Commands[][20], int N) {
	int i, j, p1, p2;  // Счет
	Elem * temp;
	for (int k = 0; k < 2; k++) // Каждая команда играет с каждой по 2 раза - дома и в гостях
		for (i = 0; i < N - 1; i++)	
			for (j = i + 1; j < N; j++)	{
				temp = new Elem;
				if (k == 0)	{ // 1 игра
					strcpy(temp->Name, Commands[i]);
					strcpy(temp->Opponent, Commands[j]);
				}
				else { // 2 игра
					strcpy(temp->Name, Commands[j]);
					strcpy(temp->Opponent, Commands[i]);
				}
				p1 = rand() % 6;
				p2 = rand() % 6;
				if (p1 > p2) {
					temp->OwnerPoints = 3;
					temp->OppPoints = 0;
				}
				else if (p1 == p2) 	{
					temp->OwnerPoints = 1;
					temp->OppPoints = 1;
				}
				else {
					temp->OwnerPoints = 0;
					temp->OppPoints = 3;
				}
				sprintf(temp->Match, " %d : %d ", p1, p2); // Запись счета
				tournament.Insert(temp);  // Добавление записи
			}
}

void main() {
	srand((unsigned)time(NULL));

	const int N = 4;
	char Commands[ ][20] =
	{
		"Liverpool",
		"Manchester United",
		"Arsenal",
		"Lids United",
	};
	// Игра
	Game(Commands, N);
	tournament.Print(tournament.GetRoot());
	for (int i = 0; i < 12; ++i){ // проверка удаления
		tournament.Del(tournament.GetRoot());
		getchar();
		system("cls");
		tournament.Print(tournament.GetRoot());
	}
}

