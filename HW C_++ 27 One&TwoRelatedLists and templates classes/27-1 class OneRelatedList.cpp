/*Добавить в класс "Односвязный список" следующие функции: вставка элемента в заданную позицию, удаление элемента по заданной позиции,
поиск заданного элемента (функция возвращает позицию найденного элемента в случае успеха или NULL в случае неудачи). */

#include <iostream>
using namespace std;

struct Element {
	char data;
	Element* Next;
};

class List {
	Element* Head;
	Element* Tail;
	int Count;
public:
	List() { Count = 0;  Head = Tail = NULL;}
	~List() { DelAll(); }
	void Add(char data); //Добавляем новый элемент (в хвост)
	void Insert(char data, int pos);
	void Del(); 	// Удаление элемента списка (Удаляется головной элемент)
	void Del(int pos);
	void DelAll(); 	// Удаление всего списка
	void Print(); // Распечатка содержимого списка (Распечатка начинается с головного элемента)
	int GetCount(); 
	int Find(char elem);
};

void List::Add(char data) {
    if (Head) {
		Tail->Next = new Element;
		Tail = Tail->Next;	
	}
	else {
		Head = Tail = new Element;
	}
	Tail->data = data;
	Tail->Next = NULL;
	Count++;
}

void List::Insert(char data, int pos){
	if (pos < 1 || pos > Count+1) { //Если позиция за пределами диапазона
		cout << "Error Insert. Wrong position" << endl;
	}
	else {
		if (pos == 1) {
			Element* temp = Head;
			Head = new Element;
			Head->data = data;
			Head->Next = temp;
			Count++;
		} else	if (pos > 1 && pos <= Count){
			Element* preMove = Head;
			for (int i = 1; i < pos - 1; ++i){ // доходим до элемента перед необходимой позицией
				preMove = preMove->Next; // Определяем указатель на элемент, который будет перед той позицией, в которую мы вставляем элемент
			}
			Element* Insert = new Element; // выделили память под новый элемент
			Insert->data = data; // записали в новый элемент значение
			Insert->Next = preMove->Next; // записали в указатель на следующий элемент (Нового элемента)  адрес элемента, который должен располагаться после нового элемента
			preMove->Next = Insert; // заменили в элементе, который будет располагаться перед новым элементом, записанный адрес на адрес нового элемента
			Count++;
		} else if (pos == Count+1) {
			Add(data);
		}
	}
}

void List::Del() {
	Element* temp = Head;
	Head = Head->Next;
	delete temp;
	Count--;
}

void List::Del(int pos){
	if (pos < 1 || pos > Count) { //Если позиция за пределами диапазона
		cout << "Error Delete. Wrong position" << endl;
	}
	else {
		if (pos == 1) {
			Del();
		}
		else if (pos > 1 && pos < Count){
			Element* preDel = Head;
			for (int i = 1; i < pos - 1; ++i){
				preDel = preDel->Next;
			}
			Element* deliting = preDel->Next; // Определяем адрес элемента, который хотим удалить
			preDel->Next = deliting->Next; // записываем адрес элемента, следующего за удаляемым Элементом, в указатель на следующий элемент в элементе, предшествующем удаляемому
			delete deliting;
			Count--;
		}
		else if (pos == Count) {
			Element* preLast = Head;
			for (int i = 1; i < pos - 1; ++i){
				preLast = preLast->Next;
			}
			Tail = preLast;
			Tail->Next = NULL;
			Count--;
		}
		
	}
}

void List::DelAll() {
	while (Head) {
		Del();
	}
}

void List::Print(){
	Element* temp = Head;
	while (temp) {
		cout << temp->data <<" ";
		temp = temp->Next;
	}
	cout << endl;
}

int List::GetCount(){
	return Count;
}

int List::Find(char elem){ // если будет несколько одинаковых символов, то функция вернет позицию первого
	int pos = 1;
	Element* find = Head;
	for (int pos = 1; pos <= Count; ++pos){
		if (find->data == elem){
			return pos;
		} else 
			find = find->Next;
	}
	return NULL;
}

void main() {
	List A;
	A.Add('a');
	A.Add('b');
	A.Add('c');
	A.Add('d');
	A.Insert('i', 5);
	A.Print();
	A.Del(5);
	A.Print();
	cout << A.Find('i') << endl;
}