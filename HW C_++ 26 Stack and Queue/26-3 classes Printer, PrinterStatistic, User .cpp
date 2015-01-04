/*Разработать приложение, имитирующее очередь печати принтера.Должны быть клиенты, посылающие запросы на принтер, 
у каждого из которых есть свой приоритет.Каждый новый клиент попадает в очередь в зависимости от своего приоритета.
Необходимо сохранять статистику печати(пользователь, время) в отдельной очереди.Предусмотреть вывод статистики на экран.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;

struct Atributes{ // Структура для хранения различных атрибутов
	char* User; // Имя пользователя
	char* Doc; // Имя документа
	int Pri; // Приоритет
	tm timePrintIn; // ячейка для хранения времени прихода документа на печать
};

struct Atributes2{ // усовершенствованные Atributes c полем timePrintOut
	Atributes Atributes1;
	tm timePrintOut; // ячейка для хранения времени распечатывания документа
};

class PrinterStatistics { // класс для хранения статистики печати принтера
	Atributes2* Stat;
	int MaxStatLength;
	int StatLength;
	bool IsEmpty(){ return StatLength == 0; }
	bool IsFull(){ return StatLength == MaxStatLength; }
public:
	PrinterStatistics(int m = 5) { Stat = new Atributes2[m*sizeof(Atributes2)]; MaxStatLength = m; StatLength = 0; }
	~PrinterStatistics() { delete[] Stat; }
	void Add(Atributes,tm);
	void Show();
};

void PrinterStatistics::Add(Atributes Atrib, tm timePrintOUT){
	if (IsFull()){ // расширяем память для хранения статистики, если она переполнена
		// можно было бы сделать все гораздо красивей и толковее с помощью realloc, но хотелось проверить как это делается с new
		MaxStatLength += 5;
		Atributes2* tempStat = new Atributes2[MaxStatLength*sizeof(Atributes2)];
		for (int i = 0; i < StatLength; ++i){
			tempStat[i] = Stat[i];
		}
		delete[] Stat;
		Stat = new Atributes2[MaxStatLength*sizeof(Atributes2)];
		for (int i = 0; i < StatLength; ++i){
			Stat[i] = tempStat[i];
		}
	} 
	Stat[StatLength].Atributes1 = Atrib;
	Stat[StatLength++].timePrintOut = timePrintOUT;
}

void PrinterStatistics::Show(){
	if (IsEmpty()){
		cout << "Didn't was print else" << endl;
	} else {
		for (int i = 0; i < StatLength; ++i) {
			cout << "User " << Stat[i].Atributes1.User << "  ";
			cout << "Doc " << Stat[i].Atributes1.Doc << "  ";
			cout << "timePIN  " << Stat[i].Atributes1.timePrintIn.tm_hour << ":" << Stat[i].Atributes1.timePrintIn.tm_min << ":" << Stat[i].Atributes1.timePrintIn.tm_sec << "  ";
			cout << "Pri " << Stat[i].Atributes1.Pri << "  ";
			cout << "timePOUT  " << Stat[i].timePrintOut.tm_hour << ":" << Stat[i].timePrintOut.tm_min << ":" << Stat[i].timePrintOut.tm_sec << "  " << endl;
		}
	}
}

class Printer {// очередь с приоритетным исключением
	Atributes* Atr;
	int MaxQueueLength;
	int QueueLength;
	bool IsEmpty(){ return QueueLength == 0; }
	bool IsFull(){ return QueueLength == MaxQueueLength; }
	PrinterStatistics PrSt;
public:
	Printer(int m = 5){ 	Atr = new Atributes[m]; MaxQueueLength = m; QueueLength = 0; }
	~Printer(){ delete[] Atr; }
	void Add(Atributes);
	char* Print();
	void ShowBuffer();
	void ShowStatistics();
	void Reset(){ QueueLength = 0; }
	
};

void Printer::Add(Atributes Atrib){   //char* U,char* D, int p
	if (IsEmpty()) {
		Atr[QueueLength++] = Atrib;
	} else {
		if (IsFull()) { // выделяем дополнительную память, если очередь уже заполнена
			Atributes* tempAtr = new Atributes[MaxQueueLength*sizeof(Atributes)];
			for (int i = 0; i < QueueLength; ++i) {
				tempAtr[i] = Atr[i];
			}
			delete[] Atr;
			MaxQueueLength += 5;
			Atr = new Atributes[MaxQueueLength*sizeof(Atributes)];
			for (int i = 0; i < QueueLength; ++i) {
				Atr[i] = tempAtr[i];
			}
			delete[] tempAtr;
		}
		int insertIndex = 0; // индекс куда нужно будет вставлять элемент в соответсвии с приоритетом
		for (int i = 0; i < QueueLength; ++i) {
			if (Atrib.Pri <= Atr[i].Pri) {
				insertIndex++;
			}
			else break;
		}
		QueueLength++;
		for (int i = QueueLength - 1; i >= insertIndex; --i){ // раздвигание места, для вставки нового элемента
			Atr[i] = Atr[i - 1];
		}
		Atr[insertIndex] = Atrib;
	} 
}

char* Printer::Print(){
	if (!IsEmpty()){
		time_t temptime = time(NULL);
		PrSt.Add(Atr[0], *localtime(&temptime));
		char* temp = Atr[0].Doc;
		for (int i = 1; i < QueueLength; ++i){
			Atr[i - 1] = Atr[i];
		}
		QueueLength--;
		cout << " Printing >>>> " << temp;
		return temp;
	} else {
		cout << "Error. Queue is Empty"<<endl;
		return 0;
	}
}

void Printer::ShowBuffer(){ // Показывает, что находится в буфере на печеть
	if (IsEmpty()) {
		cout << "Queue is Empty";
	}
	else {
		for (int i = 0; i < QueueLength; ++i) {
			cout << "User: " << Atr[i].User;
			cout << "   Doc: " << Atr[i].Doc << "   Pri: " << Atr[i].Pri;
			cout << "   TimePrintIN   " << Atr[i].timePrintIn.tm_hour << ":" << Atr[i].timePrintIn.tm_min << ":" << Atr[i].timePrintIn.tm_sec << endl;
		}
	}
}

void Printer::ShowStatistics(){
	PrSt.Show();
}

class User { // Пользователь
	Atributes Atr;
public:
	User(char* n = NULL, int p = 1) { Atr.User = n;  Atr.Doc = 0; Atr.Pri = p;}
	void Set(char* n = "default_name", int p = 1){ Atr.User = n; Atr.Pri = p; }
	void Show();
	void PrintDoc(Printer &P) ;
};

void User::Show(){
	cout << " User: ";
	if (Atr.User == NULL){
		cout << "NoName";
	} else cout << Atr.User;
	cout << "\tdoc: ";
	if (Atr.Doc == 0)
		cout << "No";
	else  cout << Atr.Doc;
	cout << "   pri: " << Atr.Pri;
	cout << "   timePrintIN  " << Atr.timePrintIn.tm_hour << ":" << Atr.timePrintIn.tm_min << ":" << Atr.timePrintIn.tm_sec;
}

char* RandomNameDocument(){
	char* temp = new char[6];
	temp[5] = '\0';
	for (int i = 0; i < 5; i++){
		temp[i] = (rand() % ('Z' - 'A') + 'A');
	}
	return temp;
}

void User::PrintDoc(Printer &P){
	Atr.Doc = RandomNameDocument(); // Случайной генерацией букв - имитируем случайные названия документов
	time_t temptime = time(NULL);  // временная переменная для сохранения системного времени в особом формате, получаемого от time()
	Atr.timePrintIn = *localtime(&temptime);
	P.Add(Atr);
}

User& RandomUser(User U[],const int N){  // Случайно выбираем пользователя
	return *(U + rand() % 4);
}

void main() {
	srand((unsigned int)time(NULL));
	Printer Canon;
	User A[4];
	A[0].Set("Vasya");
	A[1].Set("Petya");
	A[2].Set("Ivan ", 2);
	A[3].Set("Fedor", 3); 
	// Генерируем 15 случайных событий - отправка документов  в буфер печати
	cout << " Press Enter to simulate random actions of User's:"; 
	getchar(); // для отправки на печать по нажатию Enter
	for (int i = 0; i < 10; ++i) { 
		User *Temp = & RandomUser(A, 4);
		Temp->PrintDoc(Canon);
		Temp->Show(); // Cмотрим в какой последов-ти отправляли документы на печать
		getchar();
	}
	cout << " This is a buffer of Printer:"<<endl;
	Canon.ShowBuffer(); // можно посмотреть информацию обо всем, что в очереди
	cout << " Press Enter to printers printing it's buffer:";
	getchar();
	for (int i = 0; i < 10; ++i) { // Распечатываем содержимое буфера согласно очереди и приоритетов
		Canon.Print(); 
		getchar();
	}
	cout << "This is statistics of printer printing";
	getchar();
	Canon.ShowStatistics(); // посмотреть статистику печати


	// Убеждаемся что статистика накапливается
	cout << " Two User's print";
	A[1].PrintDoc(Canon);
	A[2].PrintDoc(Canon);
	getchar();
	Canon.Print();
	getchar();
	Canon.Print();
	getchar();
	Canon.ShowStatistics(); // посмотреть статистику печати
}