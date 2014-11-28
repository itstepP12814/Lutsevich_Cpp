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
	Array  operator+(const Array &source); 
	Array  operator-(const Array &source);
	Array& operator++();
	Array& operator--();
	void ShowArray();
	const size_t& GetSize() const;
};

Array::Array() {
	size = 1;
	Ar = (int*)malloc(size*sizeof(int));
}

Array::~Array() {
	free(Ar);
};

Array::Array(size_t SIZE) {
	size = SIZE;
	Ar = (int*)malloc(size*sizeof(int));
}

Array::Array(const Array &source){
	size = source.size;
	Ar = (int*)malloc(size*sizeof(int));
	this->operator=(source);  
};

int& Array::operator[] (int index) {
	if (index < size) {
		return Ar[index];
	}
	else {
		cout << "Error of index range" << endl;
	}
};

Array& Array::operator=(const Array &source) {
	if (this == &source)
		return *this;
	size = source.size;
	Ar = (int*)realloc(Ar, size * sizeof(int));
	for (int i = 0; i < size; ++i) {
		Ar[i] = source.Ar[i];
	}
	return *this; 
};

Array  Array::operator+(const Array &source) {
	Array temp (size + source.size);
	for (int i = 0; i < size; ++i) {
		temp.Ar[i] = Ar[i];
	}
	for (int i = size; i < temp.size; ++i) {
		temp.Ar[i] = source.Ar[i-size];
	}
	return temp;
};

Array  Array::operator-(const Array &source) {
	if (size >= source.size) {
		Array temp(size);
		for (int i = 0; i < source.size; ++i) {
			temp.Ar[i] = Ar[i] - source.Ar[i];
		}
		for (int i = source.size; i < temp.size; ++i) {
			temp.Ar[i] = Ar[i] - 0;
		}
		return temp;
	}
	else {
		Array temp(source.size);
		for (int i = 0; i < size; ++i) {
			temp.Ar[i] = Ar[i] - source.Ar[i];
		}
		for (int i = size; i < temp.size; ++i) {
			temp.Ar[i] = 0 - source.Ar[i];
		}
		return temp;
	}
};

Array& Array::operator++() {
	Ar = (int*)realloc(Ar, ++size*sizeof(int));
	return *this;
}

Array& Array::operator--() {
	Ar = (int*)realloc(Ar, --size*sizeof(int));
	return *this;
}


void Array::ShowArray() {
	for (int i = 0; i < size; ++i) {
		printf("%-4d", Ar[i]);
	}
	cout << endl;
}

const size_t &Array::GetSize() const {
	return size;
};


void main() {
	Array A;
	A.operator[](0) = 2;
	cout << "A =     ";  A.ShowArray();

	Array B(7);
	int x = 3;
	for (int i = 0; i < B.GetSize(); ++i) {
		B[i] = x+=3;
	}
	cout << "B =     ";  B.ShowArray();

	Array C(5);
	C = A;
	cout << "C = A = ";  C.ShowArray();

	C = B;
	cout << "C = B = ";  C.ShowArray();

	C = A + B;
	cout << "C =A+B= ";  C.ShowArray();

	C = B - A;
	cout << "C =B-A= ";  C.ShowArray();

	C = A - B;
	cout << "C =A-B= ";  C.ShowArray();

	C = ++ A; C[1] = 3;
	cout << "C =++A= ";  C.ShowArray();

	C = --C;
	cout << "C =--C= ";  C.ShowArray();

}



