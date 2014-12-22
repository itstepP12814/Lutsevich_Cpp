/*��������  �����  �������������  �������,  �  �������  �����������  �������� ������  ��  �������  �������.
�����������  ���������:  [  ],  =,  +,  -,++ (����������  ��������  �  �����  �������),  --  (��������  ��������  ��  ����� �������). */

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

// ����������� �� ���������
Array::Array() {
	size = 1;
	Ar = (int*)malloc(size*sizeof(int));
	Ar[0] = 0;
}

// ���������� - ����������� ������
Array::~Array() { 
	free(Ar);
};

// ����������� � ���������� ������ ������������ �������
Array::Array(size_t SIZE) {
	int x = 0; // ���������� ��� ������� �������� �������
	size = SIZE;
	Ar = (int*)malloc(size*sizeof(int));
	for (int i = 0; i < SIZE; ++i) {
		Ar[i] = x +=3;
	}
}

// ����������� �����������
Array::Array(const Array &source) { 
	size = source.size; // �������� ������
	Ar = (int*)malloc(size*sizeof(int)); // �������� ����� ������
	for (int i = 0; i < size; ++i) { // �������� ������ ��������
		Ar[i] = source.Ar[i];
	}
};

// ���������� ��������� ��������������
int& Array::operator[] (int index) { 
	if (index < size) {
		return Ar[index];
	}
	else {
		cout << "Error of index range" << endl;
		return Ar[index] = 0;
	}
}; 

// ���������� ��������� ����������
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

// ���������� ��������� �������� (��)
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

// ���������� ��������� ��������� (��)
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

//���������� ��������� - ����������� �� ���� ������ ������
Array& Array::operator++() {
	Ar = (int*)realloc(Ar, ++size*sizeof(int));
	Ar[size - 1] = 0;
	return *this;
}

//���������� ��������� - ��������� �� ���� ������ ������
Array& Array::operator--() {
	Ar = (int*)realloc(Ar, --size*sizeof(int));
	return *this;
}

//����������� ��������� - ����������� �� ���� ������ ������
Array Array::operator++(int k)  {
	Array temp(*this);
	Ar = (int*)realloc(Ar, ++size*sizeof(int));
	Ar[size - 1] = 0;
	return temp;
}

//����������� ��������� - ��������� �� ���� ������ ������
Array Array::operator--(int k) {
	Array temp(*this);
	Ar = (int*)realloc(Ar, --size*sizeof(int));
	return temp;
}

//������� ��� ������ ����������� �������
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
	cout << "� =B+A= ";  C.ShowArray();

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



