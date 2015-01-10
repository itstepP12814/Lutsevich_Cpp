//Реализовать шаблонный класс "Очередь" на основе двусвязного списка. 

#include <iostream>
using namespace std;

template <typename T>
struct Elem {
	T data;
	Elem  *next, *prev;
};

template <typename T>
class List {
	Elem <T> *Head, *Tail;
	int Count;
	Elem <T>* GetElem(int);
public:
	List() :Head(NULL), Tail(NULL), Count(0){ ; }
	~List(){ DelAll(); };
	int GetCount ();
	void Del(int); // если параметр не указывается, то функция его запросит
	void DelAll(); 
	void Insert(int); // если параметр не указывается, то функция его запросит
	void AddTail(T);
	void AddHead(T);
	void Print();
	void Print(int);
	List(const List&); // Конструктор копирования
	List& operator=(const List&);
	List operator+(const List&); // сложение двух списков (дописывание)
	bool operator==(const List&); // сравнение по элементам
	bool operator!=(const List&);
	bool operator<=(const List&);
	bool operator>=(const List&);
	bool operator>(const List&);
	bool operator<(const List&);
	List operator-(); // переворачивание списка
};

template <typename T>
Elem <T>*  List<T>::GetElem(int pos){
	if (pos<1 || pos>Count) {
		cout << "Incorrect position"<<endl;
		return NULL;
	}
	else {
		Elem <T>* GetEl = NULL;
		if (pos <= Count / 2) {
			GetEl = Head;
			for (int i = 1; i < pos; ++i) {
				GetEl = GetEl->next;
			}
		}
		else if (pos>Count / 2)  {
			GetEl = Tail;
			for (int i = 1; i < Count + 1 - pos; ++i) {
				GetEl = GetEl->prev;
			}
		}
		return GetEl;
	}
}

template <typename T>
void List <T>::AddTail(T n){
	Elem <T>* temp = new Elem <T>;
	temp->data = n;
	temp->next = NULL;
	temp->prev = Tail;
	if (Count) {
		Tail->next = temp;
		Tail = temp;
	} else {
		Head = Tail = temp;
	}
	Count++;
}

template <typename T>
void List <T>::AddHead(T n){
	Elem <T>* temp = new Elem<T>;
	temp->data = n; 
	temp->prev = NULL; // Предыдущего нет
	temp->next = Head; // Следующий - бывшая голова
	
	if (Count) {//Если элементы есть
		Head->prev = temp;
		Head = temp;
	} else { 
		Head = Tail = temp;
	}
	Count++;
}

template <typename T>
void List <T>::Insert(int pos = 0){
	if (!pos) { // Если не указали позицию
		cout << "Enter position" << endl;
		cin  >> pos;
	}
	if (pos<1|| pos>Count+1) { // если за пределами 
		cout << "Incorrect position"<<endl;
	} else {
		int data;
		cout << "input data"<<endl;
		cin >> data;
		if (pos == 1) { // если вставка в начало
			AddHead(data);
		} else if (pos == Count+1) { // если вставка в конец
			AddTail(data);
		} else { // (pos >1 && pos <=Count)
			Elem <T>* temp = new Elem <T>;
			temp->data = data;
			Elem <T>* Move = GetElem(pos); // Получаем указатель на элемент, который будем сдвигать
			temp->next = Move;
			temp->prev = Move->prev;
			Move->prev->next = temp;
			Move->prev = temp;
			Count++;
		}
	}
}

template <typename T>
void List <T>::Del(int pos = 0){
	if (!pos) { // Если не указали позицию
		cout << "Enter position" << endl;
		cin  >> pos;
	}
	if (pos<1 || pos>Count) { // если за пределами 
		cout << "Incorrect position"<<endl;
	} else {
		Elem <T>* Del = GetElem(pos);
		Elem <T>* prevDel = Del->prev;
		Elem <T>* afterDel = Del->next;
		// Удаляем крайние
		if (pos==1 && Count!=1) { // prevDel = 0
			Head = Head->next; //	Head = afterDel;
			Head->prev = NULL;  
		} else
		if (pos==Count && Count!=1) { // afterDel = 0
			Tail = Tail->prev;  // Tail = preDel;
			Tail->next = NULL;
		} else {
			// если удаляем не хвост
			if (Count != 1) { // afterDel!=0 
				afterDel->prev = prevDel;
			}
			// если удаляем не голову
			if (Count !=1) { // prevDel != 0 
				prevDel->next = afterDel;
			}
		}		
		delete Del;
		--Count;
	}
}

template <typename T>
void List <T>::DelAll(){
	while (Count){
		Del(1);
	}
}

template <typename T>
int List <T>::GetCount() {
	return Count;
}

template <typename T>
void List <T>::Print(){
	if (Count) {
		Elem <T>* temp = Head;
		while (temp) {
			cout << temp->data<<" ";
			temp = temp->next;
		}
		cout << endl;
	} else {
		cout <<"No Elements"<<endl;
	}
}

template <typename T>
void List <T>::Print(int pos){
	if (GetElem(pos)){
		cout << GetElem(pos)->data << endl;
	}
}

template <typename T>
List<T>::List(const List& obj) : Head(NULL), Tail(NULL), Count(0) {
	*this = obj; // тут сработает оператор присваивания
}

template <typename T>
List<T>& List <T>::operator=(const List& obj){
	if (this != &obj) { // Проверка присваивания элемента "самому себе"
		this->~List(); //DelAll(); // очистим список от того, что в нем есть
		Elem <T>* temp = Head = obj.Head; // берем голову
		while (temp) {
			AddTail(temp->data); // последовательно перебирая перекопируем
			temp = temp->next;
		}
	}
	return *this;
}

template <typename T>
List<T> List <T>::operator+(const List& obj){
	List Add(*this); // создаем на копию первого слагаемого
	Elem <T>* temp = obj.Head;
	while (temp){ // Добавляем в хвост певого слагаемого все элементы последующего
		Add.AddTail(temp->data);
		temp = temp->next;
	}
	return Add; // возвращаем копию первого слагаемого в котором хранится уже вся сумма
}

template <typename T>
bool List <T>::operator==(const List& obj) {
	if (Count != obj.Count) { 	// быстрое Сравнение по количеству
		return false;
	}
	else {
		Elem <T>* temp1 = Head;
		Elem <T>* temp2 = obj.Head;
		while (temp1!=NULL) {
			if (temp1->data != temp2->data) 
				return false;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	return true;
}

template <typename T>
bool List <T>::operator!=(const List& obj){
	return !(*this == obj);
}

template <typename T>
bool List <T>::operator>(const List& obj){
	if (Count > obj.Count)  {  // сравниваем по количеству
		return true;
	}
	else return false;
}

template <typename T>
bool List <T>::operator<(const List& obj){
	return !(*this > obj);
}

template <typename T>
bool List <T>::operator>=(const List& obj) {
	return (*this > obj || *this == obj);
}

template <typename T>
bool List<T>::operator<=(const List& obj) {
	return (*this < obj || *this == obj);
}

template <typename T>
List <T> List <T>::operator-(){
	List Result;
	Elem <T>* temp = Tail;
	while (temp){ //добавляем элементы из имевшегося списка с конца
		Result.AddTail(temp->data);
		temp = temp->prev;
	}
	return Result;
}

void main() {
	List<int> A;
	for (int i = 1; i < 4; ++i){
		A.AddTail(i * 2);
	}
	A.AddHead(1);
	A.Print();
	cout << endl;
	List<int> B;
	B = A;
	B.Print();
	List<int> C;
	C = A + B;
	C.Print();
	C = -C;
	C.Print();
}