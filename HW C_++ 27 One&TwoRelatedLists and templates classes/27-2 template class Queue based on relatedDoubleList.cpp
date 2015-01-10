//Реализовать шаблонный класс "Очередь" на основе двусвязного списка. 

#include <iostream>
using namespace std;

template <typename T>
struct Elem {
	T data;
	Elem  *next, *prev;
};

template <typename T>
class Queue {
	Elem <T> *Head, *Tail;
public:
	Queue() {Head = Tail = NULL; }
	~Queue(){ DelAll(); };
	void Add(T);
	T Exctract();
	void DelAll(); 
	void Print();	
};

template <typename T>
void Queue <T>::Add(T dat){
	if (Head) {
		Tail->next = new Elem<T>;
		Tail->next->data = dat;
		Tail->next->next = NULL;
		Tail->next->prev = Tail;
		Tail = Tail->next;
	}
	else {
		Head = new Elem <T>;
		Head->data = dat;
		Head->prev = Head->next = NULL;
		Tail = Head;
	}
}

template <typename T>
T Queue <T>::Exctract(){
	if (Head) {
		if (Head->next) {
			T exctr = Head->data;
			Head = Head->next;
			delete Head->prev;
			Head->prev = NULL;
			return exctr;
		}
		else {
			T exctr = Head->data;
			delete Head;
			Head = Tail = NULL;
			return exctr;
		}
	}
	else {
		cout << "Queue is Empty" << endl;
		return 0;
	}	
}


template <typename T>
void Queue <T>::DelAll(){
	while (Head) {
		if (Head->next) {
			Head = Head->next;
			delete Head->prev;
			Head->prev = NULL;
		}
		else {
			delete Head;
			Head = Tail = NULL;
		}	
	}
}

template <typename T>
void Queue <T>::Print(){
	if (Head) {
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

void main() {
	Queue<int> A;
	for (int i = 1; i < 4; ++i){
		A.Add(i * 2);
		A.Print();
	}
	for (int i = 1; i < 7; ++i){
		A.Exctract();
		A.Print();
	}
}