/*����������� ����������, ����������� ������� ������ ��������.������ ���� �������, ���������� ������� �� �������, 
� ������� �� ������� ���� ���� ���������.������ ����� ������ �������� � ������� � ����������� �� ������ ����������.
���������� ��������� ���������� ������(������������, �����) � ��������� �������.������������� ����� ���������� �� �����.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;

struct Atributes{ // ��������� ��� �������� ��������� ���������
	char* User; // ��� ������������
	char* Doc; // ��� ���������
	int Pri; // ���������
	tm timePrintIn; // ������ ��� �������� ������� ������� ��������� �� ������
};

struct Atributes2{ // ������������������� Atributes c ����� timePrintOut
	Atributes Atributes1;
	tm timePrintOut; // ������ ��� �������� ������� �������������� ���������
};

class PrinterStatistics { // ����� ��� �������� ���������� ������ ��������
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
	if (IsFull()){ // ��������� ������ ��� �������� ����������, ���� ��� �����������
		// ����� ���� �� ������� ��� ������� �������� � �������� � ������� realloc, �� �������� ��������� ��� ��� �������� � new
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

class Printer {// ������� � ������������ �����������
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
		if (IsFull()) { // �������� �������������� ������, ���� ������� ��� ���������
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
		int insertIndex = 0; // ������ ���� ����� ����� ��������� ������� � ����������� � �����������
		for (int i = 0; i < QueueLength; ++i) {
			if (Atrib.Pri <= Atr[i].Pri) {
				insertIndex++;
			}
			else break;
		}
		QueueLength++;
		for (int i = QueueLength - 1; i >= insertIndex; --i){ // ����������� �����, ��� ������� ������ ��������
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

void Printer::ShowBuffer(){ // ����������, ��� ��������� � ������ �� ������
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

class User { // ������������
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
	Atr.Doc = RandomNameDocument(); // ��������� ���������� ���� - ��������� ��������� �������� ����������
	time_t temptime = time(NULL);  // ��������� ���������� ��� ���������� ���������� ������� � ������ �������, ����������� �� time()
	Atr.timePrintIn = *localtime(&temptime);
	P.Add(Atr);
}

User& RandomUser(User U[],const int N){  // �������� �������� ������������
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
	// ���������� 15 ��������� ������� - �������� ����������  � ����� ������
	cout << " Press Enter to simulate random actions of User's:"; 
	getchar(); // ��� �������� �� ������ �� ������� Enter
	for (int i = 0; i < 10; ++i) { 
		User *Temp = & RandomUser(A, 4);
		Temp->PrintDoc(Canon);
		Temp->Show(); // C������ � ����� ��������-�� ���������� ��������� �� ������
		getchar();
	}
	cout << " This is a buffer of Printer:"<<endl;
	Canon.ShowBuffer(); // ����� ���������� ���������� ��� ����, ��� � �������
	cout << " Press Enter to printers printing it's buffer:";
	getchar();
	for (int i = 0; i < 10; ++i) { // ������������� ���������� ������ �������� ������� � �����������
		Canon.Print(); 
		getchar();
	}
	cout << "This is statistics of printer printing";
	getchar();
	Canon.ShowStatistics(); // ���������� ���������� ������


	// ���������� ��� ���������� �������������
	cout << " Two User's print";
	A[1].PrintDoc(Canon);
	A[2].PrintDoc(Canon);
	getchar();
	Canon.Print();
	getchar();
	Canon.Print();
	getchar();
	Canon.ShowStatistics(); // ���������� ���������� ������
}