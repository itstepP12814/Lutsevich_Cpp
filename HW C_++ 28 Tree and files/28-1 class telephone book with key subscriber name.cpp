/*Создать телефонный справочник для осуществления следующих операций :

+Добавление абонентов в базу.
+Удаление абонентов из базы.
+Модификация данных абонента.
+/-Поиск абонентов по телефонному номеру или фамилии.
+/-Распечатка в алфавитном порядке абонентов из заданного диапазона номеров или фамилий; например, для номеров диапазон может быть : 222222 - 333333, а для фамилий : Иванаускас - Иванов(то есть Иванова в диапазон не входит).
+Возможность сохранения найденной информации в файл.
+Сохранение базы в файл.
+Загрузка базы из файла.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

#define NS 14 //NUMBER_SUBSCRIBES
#define MAX_NAME 12

struct Elem {
	char Name[MAX_NAME];  // использую char и string  просто, чтобы прочувствовать разницу в их использовании 
	string Number;
	Elem *parent, *left, *right; // набор указателей для упорядочивания всего по ключу фамилия
};

class Book {
	Elem *root;
public:
	Book(){ root = NULL; }
	~Book(){ Del(); }
	void Add(char Name[],string Number);
	Elem* Min(Elem* Node); // служебная функция необходимая для работы Next
	Elem* Next(Elem* Node); //служебная функция необходимая для работы Del
	void Del(Elem* d = NULL); //удаление ветки для указанного узла, если 0 - всего дерева
	void Edit(Elem* Node, char Name[], string Number);
	void Print() const; // Печать всего справочника
	void Print(Elem* Node) const;
	Elem* SearchName(char Name[]);
	void PrintRange(char Name1[], char Name2[]);
	bool SaveNameDiapasoneToFile(char Name1[], char Name2[]);
	
	Elem* GetRoot(){ return root; } //служебная функция необходимая для работы других функций
	
	bool SaveBaseToFile();
	bool LoadBaseFromFile();
};

void Book::Add(char Name[], string Number){
	Elem *Ins = new Elem;
	strcpy(Ins->Name, Name);
	Ins->Number = Number;
	Elem *preIns = NULL; // узел к которому будем "пристыковывать" данные (пристыковочный узел)
	Elem *temp = root; // временный указатель для осуществления перебора
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
	else //if (strcmp(Ins->Name, preIns->Name) < 0)
		preIns->left = Ins;
}

Elem* Book::Min(Elem *Node){ // Поиск самого "левого" узла
	Elem *temp = Node;
	if (temp)   // Node!=0
		while (temp->left)
			temp = temp->left;
	return temp;
}

Elem* Book::Next(Elem *Node){
	Elem* Nxt = NULL; // узел, который мы ищем (который следующий) // NULL нужно задать до if для случая, когда Nxt вообще не будет (элемент будет и так крайний)
	if (Node){
		//1 Если есть правый потомок
		if (Node->right)
			Nxt = Min(Node->right);
		else {//2 Если правого потомка нет, то нужно вернуться хотя бы на узел выше (к родителю)
			Elem *preNxt = Node; //  временный указатель для осуществления перебора
			Nxt = preNxt->parent;// 2 Если мы вышли из левой ветки и родитель не NULL, то это и есть следующий узел
			while (Nxt != NULL&&preNxt == Nxt->right){ //3 Движемся дальше вверх (пока родитель не будет NULL или  пока мы выходим из правой ветки, ВАЖНО чтобы условия были именно в такой ПОСЛЕДОВАТЛЬНОСТИ ) 
				preNxt = Nxt;
				Nxt = Nxt->parent;
			}
		}
	}
	return Nxt;
}

void Book::Del(Elem *d){
	if (d) {  // удаление куста
		Elem *y = NULL, *Node = NULL; //УДАЛЯЕМЫЙ узел и узел после удаляемого

		// ОПРЕДЕЛИМ УДАЛЯЕМЫЙ УЗЕЛ (физически память которого будет delete)
		if (d->left == NULL || d->right == NULL){ // 1 потомок или 0 
			y = d;
		}
		else // 2 потомка - удалим следующий узел (у него обязательно не будет !!левого!! потомка)
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
			strcpy(d->Name, y->Name);
			d->Number = y->Number;
		}
		delete y;
	}
	else {
		while (root)
			Del(root);
	}
}

void  Book::Edit(Elem* Node, char Name[], string Number) {
	if (Node){
		strcpy(Node->Name, Name);
		Node->Number = Number;
	}
	else
		cout << "Error couldn't to Edit\n";
}

void Book::Print() const{
	Elem* temp = root;
	if (temp){
		Print(temp->left);
		printf("%-12s - %12s\n", temp->Name,temp->Number.data()); //Number.data() - функция возвращающая из string char*, который printf печатается
		Print(temp->right);
	}
	if (!root)
		cout << "Nothing to print\n";
}

void Book::Print(Elem* Node) const{
	Elem* temp = Node;
	if (temp){
		Print(temp->left);
		printf("%-12s - %12s\n", temp->Name,temp->Number.data());
		Print(temp->right);
	}
}

Elem* Book::SearchName(char Name[]){ // есть скоре всего неточности, нет времени глубоко разбирать детали
	Elem *Src = root;
	while (Src!=0 && strcmp(Src->Name, Name) != 0){ // Цикл прервется, если выйдем на NULL или совпадет ключ
		if (strcmp(Name, Src->Name)< 0) {
			if (Src->left&&strcmp(Name, Src->left->Name)>0){ // Условие, чтобы получаемое значение входило в диапазон поиска, т.е. было правее
				return Src;
			}
			Src = Src->left;
		}
		else { 
			if (!Src->right&&strcmp(Name, Src->Name)<0){ // Условие, чтобы не выйти правее самого правого элемента дерева
				return Src;
			}
			Src = Src->right;
		}
	}
}

/*Elem* Book::SearchNumber(string Number){ // Можно использовать, если дерево упорядочить по номерам
	Elem* Src = root;
	while (Src != 0 && Number.compare(Src->Number) != 0){
		if (Number.compare(Src->Number)>0)
			Src = Src->right;
		else if (Number.compare(Src->Number)<0)
			Src = Src->left;
	}
	if (!Src){
		cout << "Couldn't find such Number" << endl;
	}
	return Src;
}*/

void Book::PrintRange(char Name1[], char Name2[]){ // Не очень верная реализация границ диапазона, есть неучтенные нюансы
	Elem *temp = SearchName(Name1);
	while (temp&&strcmp(temp->Name, Name2)<=0){
		printf("%-12s - %12s\n", temp->Name, temp->Number.data());
		temp = Next(temp);
	}
}  

bool Book::SaveNameDiapasoneToFile(char Name1[], char Name2[]){
	FILE * resultfile;
	if (!(resultfile = fopen("d:\\Search_Result.txt", "w"))) {
		perror("could't save result");
		return false;
	}
	Elem *temp = SearchName(Name1);
	while (temp&&strcmp(temp->Name, Name2)<=0){
		fputs(temp->Name, resultfile);
		fputs(" ", resultfile);
		fputs(temp->Number.data(), resultfile);
		fputs("\n", resultfile);
		temp = Next(temp);
	}
	cout << "Search result was saved - d:\\Search_Result.txt\n";
	fclose(resultfile);
	return true;
}

bool Book::SaveBaseToFile(){ // сохраняем в файл последовательно, при этом удаляя каждый шаг корневой элемен. Этим  сохраняем исходный вид дерева, ИНАЧЕ потом при загрузке из этого файла получится вырожденное дерево
	FILE * basefile;
	if (!(basefile = fopen("d:\\Subscriber_book.txt", "w"))) {
		perror("could't save base");
		return false;
	}
	Elem *temp = GetRoot(); // временный указатель на текущий элемент
	while (temp){
		fputs(temp->Name, basefile);
		fputs(" ", basefile);
		fputs(temp->Number.data(), basefile);
		fputs("\n", basefile);
		Del(GetRoot());
		temp = GetRoot();
	}
	cout << "base was saved - d:\\Subscriber_book.txt\n";
	fclose(basefile);
	return true;
}

bool Book::LoadBaseFromFile(){
	FILE * basefile;
	if (!(basefile = fopen("d:\\Subscriber_book.txt", "r"))) {
		perror("could't open base");
		return false;
	}
	char buffer[MAX_NAME + 12];
	char* Name;
	string Number;
	fgets(buffer, MAX_NAME + 12, basefile);
	while (!feof(basefile)){
		Name = strtok(buffer, " ");
		Number = strtok('\0', "\n");
		Add(Name, Number);
		fgets(buffer, MAX_NAME + 12, basefile); // Очень важно, чтобы эта функция срабатывала в конце цикла, для того, чтобы вовремя сработало условие конца файла
	}
	cout << "base d:\\Subscriber_book.txt  was opened\n";
	fclose(basefile);
	return true;
}

void GenerateBase(Book &Bk) {
	char SArr[NS][2][10] {
			{"Mother", "454-23-41" },
			{ "Father", "253-14-12" },
			{ "Sister", "322-21-33" },
			{ "Brother", "543-76-44" },
			{ "Uncle", "644-21-22" },
			{ "Sasha", "233-11-42" },
			{ "Katya", "677-15-48" },
			{ "Masha", "541-22-17" },
			{ "Valera", "719-18-70" },
			{ "Ivan", "848-44-43" },
			{ "Artur", "789-87-15" },
			{ "Lesha", "477-52-36" },
			{ "Petya", "321-85-37" },
			{ "Pavel", "213-14-15" }
	};
	Elem MyS[NS];
	for (int i = 0; i < NS; ++i) { // Запись номеров в справочник
		strcpy(MyS[i].Name, SArr[i][0]);
		MyS[i].Number = SArr[i][1];
		Bk.Add(MyS[i].Name, MyS[i].Number);
	}
}

void main() {
	Book MySubsribes;
	GenerateBase(MySubsribes);
	MySubsribes.Print();
	cout << "----------------------------" << endl;
	MySubsribes.PrintRange("Pz", "Vz");
	MySubsribes.SaveNameDiapasoneToFile("Dada", "Masha");
}