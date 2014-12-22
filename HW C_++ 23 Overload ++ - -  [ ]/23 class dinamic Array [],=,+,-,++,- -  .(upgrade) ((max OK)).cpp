/*Создайте  класс  динамического  массива,  в  котором  реализована  проверка выхода  за  границы  массива.
Перегрузите  операторы:  [  ],  =,  +,  -,++ (добавление  элемента  в  конец  массива),  --  (удаление  элемента  из  конца массива). */

#include <iostream>
using namespace std;
class Array {
	int *Ar;
	size_t size;
public:
	Array();
	~Array();
	Array(size_t size);
	Array(const Array &source); 
	int& operator[](int index);  
	Array& operator=(const Array &source); 
	Array operator+(const Array &source) const; 
	Array operator-(const Array &source) const;
	Array& operator++(); 
	Array& operator--();
	Array operator++(int k);
	Array operator--(int k);
	void ShowArray();
};

// конструктор по умолчанию
Array::Array() {
	size = 1;
	Ar = (int*)malloc(size*sizeof(int));
	Ar[0] = 0;
}

// деструктор - освобождаем память
Array::~Array() { 
	free(Ar);
};

// конструктор с параметром размер создаваемого массива
Array::Array(size_t SIZE) {
	int x = 0; // переменная для задания значений массива
	size = SIZE;
	Ar = (int*)malloc(size*sizeof(int));
	for (int i = 0; i < SIZE; ++i) {
		Ar[i] = x +=3;
	}
}

// конструктор копирования
Array::Array(const Array &source) { 
	size = source.size; // копируем размер
	Ar = (int*)malloc(size*sizeof(int)); // выделяем новую память
	for (int i = 0; i < size; ++i) { // копируем каждое значение
		Ar[i] = source.Ar[i];
	}
};

// перегрузка оператора индексирования
int& Array::operator[] (int index) { 
	if (index < size) {
		return Ar[index];
	}
	else {
		cout << "Error of index range" << endl;
		return Ar[index] = 0;
	}
}; 

// перегрузка оператора присвоения
Array& Array::operator=(const Array &source) {
	if (this == &source)
		return * this;
	else {
		size = source.size;
		Ar = (int*)malloc(size * sizeof(int));
		for (int i = 0; i < size; ++i) {
			Ar[i] = source.Ar[i];
		}
	}
	return *this;
};

// перегрузка оператора сложения (ок)
Array  Array::operator+(const Array &source) const {
	if (size >= source.size) {
		Array temp (size);
		temp = *this;
		for (int i = 0; i < source.size; ++i) {
			temp.Ar[i]+= source.Ar[i];
		}
		return temp;
	} else {
		Array temp(source.size);
		temp = source;
		for (int i = 0; i < size; ++i) {
			temp.Ar[i] += Ar[i];
		}
		return temp;
	}
};

// перегрузка оператора вычитания (ок)
Array  Array::operator-(const Array &source) const{
	if (size >= source.size) {
		Array temp(size);
		temp = *this;
		for (int i = 0; i < source.size; ++i) {
			temp.Ar[i] = Ar[i] - source.Ar[i];
		}
		return temp;
	}
	else {
		Array temp(source.size);
		temp = source;
		for (int i = 0; i < size; ++i) {
			temp.Ar[i] = Ar[i] - source.Ar[i];
		}
		for (int i = size; i < temp.size; ++i) {
			temp.Ar[i] = 0 - source.Ar[i];
		}
		return temp;
	}
};

//префиксный инкремент - увеличиваем на одну ячейку массив
Array& Array::operator++() {
	Ar = (int*)realloc(Ar, ++size*sizeof(int));
	Ar[size - 1] = 0;
	return *this;
}

//префиксный декремент - уменьшаем на одну ячейку массив
Array& Array::operator--() {
	Ar = (int*)realloc(Ar, --size*sizeof(int));
	return *this;
}

//постфиксный инкремент - увеличиваем на одну ячейку массив
Array Array::operator++(int k)  {
	Array temp(*this);
	Ar = (int*)realloc(Ar, ++size*sizeof(int));
	Ar[size - 1] = 0;
	return temp;
}

//постфиксный декремент - уменьшаем на одну ячейку массив
Array Array::operator--(int k) {
	Array temp(*this);
	Ar = (int*)realloc(Ar, --size*sizeof(int));
	return temp;
}

//функция для показа содержимого массива
void Array::ShowArray() {
	for (int i = 0; i < size; ++i) {
		printf("%-4d", Ar[i]);
	}
	cout << endl;
}

void main() {
	Array A;
	A[0] = 2;
	cout << "A =     ";  A.ShowArray();

	Array B(6);
	cout << "B =     ";  B.ShowArray();

	Array C(4);
	C = A;
	cout << "C = A = ";  C.ShowArray();

	C = B;
	cout << "C = B = ";  C.ShowArray();

	C = A + B;
	cout << "C =A+B= ";  C.ShowArray();
	
	C = B + A;
	cout << "С =B+A= ";  C.ShowArray();

	C = B - A;
	cout << "C =B-A= ";  C.ShowArray();

	C = A - B;
	cout << "C =A-B= ";  C.ShowArray();

	C = ++A; 
	cout << "C =++A= ";  C.ShowArray();

	C = --C;
	cout << "C =--C= ";  C.ShowArray();

	Array D;
	D = A++;
	cout << "D =A++= ";
	D.ShowArray(); cout << "A =     ";  A.ShowArray(); 

	Array E;
	E = A--;
	cout << "E =A--= ";
	E.ShowArray(); cout << "A =     ";  A.ShowArray(); 
}



