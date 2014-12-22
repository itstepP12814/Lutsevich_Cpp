/*Создать класс для работы с матрицами.Предусмотреть, как минимум, функции для сложения матриц, умножения матриц, 
транспонирования матриц, присваивания матриц друг другу, установка и получение произвольного элемента матрицы.*/

#include <iostream>
using namespace std;

class Matrix {
	int rows;
	int columns;
	int **Arr;
	
public:
	Matrix(int r, int c);
	~Matrix();
	void printMatrix();
	void resize(int r, int c);
	int* operator[] (int);
	Matrix (const Matrix& source);
	Matrix& operator=(const Matrix& source);
	Matrix operator+(const Matrix& source) const;
	Matrix operator*(const Matrix& source) const;
	Matrix operator * (int number);
	friend Matrix& operator * (int number, Matrix& source); // вариант через дружественную перегрузку
	Matrix Transposition();
	
};

Matrix::Matrix(int r = 0, int c = 0) {
	int a = 0;
	rows = r;
	columns = c;
	if (r == 0 && c == 0) {
		Arr = NULL;
	}
	else {
		Arr = new int*[rows];
		for (int i = 0; i < rows; ++i) {
			Arr[i] = new int[columns];
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				Arr[i][j] = ++a;
			}
		}
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; ++i) {
		delete [ ] Arr[i];
	}
	delete [] Arr;
}

void Matrix::printMatrix() {
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < columns; ++j) {
			cout << Arr[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}

void Matrix::resize(int r, int c) {
	for (int i = 0; i < rows; ++i) {
		delete[] Arr[i];
	}
	delete[] Arr;
	rows = r;
	columns = c;
	int a = 0;
	Arr = new int*[rows];
	for (int i = 0; i < rows; ++i) {
		Arr[i] = new int[columns];
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			Arr[i][j] = ++a;
		}
	}
}

int* Matrix::operator[] (int row) {
	return Arr[row];
}

Matrix::Matrix (const Matrix& source){
	cout << "Copy"<<endl;
	rows = source.rows;
	columns = source.columns;
	if (rows == 0 && columns == 0) {
		Arr = NULL;
	}
	else {
		Arr = new int*[rows];
		for (int i = 0; i < rows; ++i) {
			Arr[i] = new int[columns];
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				Arr[i][j] = source.Arr [i][j];
			}
		}
	}
}

Matrix& Matrix::operator=(const Matrix& source){
	cout << "operator ="<<endl;
	this->rows = source.rows;
	this->columns = source.columns;
	if (rows == 0 && columns == 0) {
		Arr = NULL;
	}
	else {
		Arr = new int*[rows];
		for (int i = 0; i < rows; ++i) {
			Arr[i] = new int[columns];
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				Arr[i][j] = source.Arr [i][j];
			}
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& source) const {
	if (rows==source.rows && columns == source.columns) {
		Matrix Temp(rows,columns);
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < columns; ++j) {
			Temp.Arr[i][j] = Arr[i][j] + source.Arr[i][j];
		}
	}
		return Temp;
	} else {
		cout << "ERROR. Differense sizes of Matrix" <<endl;
		return 1;
	}	
}

Matrix Matrix::operator*(const Matrix& source) const {
	if (columns!=source.rows){
		cout << "ERROR. Wrong sizes of Matrix"<<endl;
		return 1;
	} else {
 		Matrix Temp(rows,source.columns);
		for (int s = 0; s < rows; ++s) { // индекс прохода по строкам исходной матрицы
		// ----------------------------------------
			for (int i = 0; i < source.columns; ++i){ // индекс прохода по столбцам матрицы на которую умножаем
				int sum = 0;  
				for (int j = 0; j < columns; ++j) { // индекс перебора одинакового
					sum += Arr[s][j] * source.Arr [j] [i];
				}
				Temp.Arr[s][i] = sum;
			}
		}
		return Temp;
	}
}	

Matrix Matrix::operator*(int number) {
	Matrix Temp = *this;
	for (int i = 0; i < Temp.rows; ++i){
		for (int j = 0; j < Temp.columns; ++j) {
			Temp.Arr[i][j] *= number;
		}
	}
	return  Temp;
}

Matrix& operator * (int number, Matrix& source) {
	for (int i = 0; i < source.rows; ++i){
		for (int j = 0; j < source.columns; ++j) {
			source.Arr[i][j] *= number;
		}
	}
	return  source;
}

Matrix Matrix::Transposition(){
	Matrix Temp = *this;
	this->resize(columns, rows);
	for (int i = 0; i < columns; ++i)
		for (int j = 0; j <rows ; ++j)
			Arr[j][i] = Temp.Arr[i][j];
	return Temp;
}

void main() {
	Matrix B;
	B.printMatrix();

	Matrix A (4,5);
	A.printMatrix();
	cout << A[3][4]<<endl;
	
	A[2][0] = 99;
	A.printMatrix ();

	
	Matrix C = A;
	cout << " Matrix C before:" << endl;
	C.printMatrix();
	cout << " Matrix C after:" << endl;
	C.resize(2, 6);
	C.printMatrix();

	Matrix D;
	D = C;
	D.printMatrix();

	cout << "D+C"<<endl;
	Matrix E;
	E = D + C;
	E.printMatrix ();
	Matrix F (3,6);
	E = F + D;

	cout << "operator *"<< endl;
	Matrix H (2,3);
	H.printMatrix ();
	Matrix W (3,2);
	W.printMatrix ();
	Matrix Q ;
	Q = W * H;
	Q.printMatrix ();

	cout << "transposition" <<endl;
	D.Transposition ();
	D.printMatrix ();

	cout << "multiply number" << endl;
	D = D * 4;
	D.printMatrix();

	cout << "multiply number" << endl;
	operator* (4,D);
	D.printMatrix();
}