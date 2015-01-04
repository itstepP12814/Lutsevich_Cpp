/*Создать имитацию игры "однорукий бандит". Например, при нажатии кнопки "Enter" 
происходит "вращение" трех барабанов (естественно, количество вращений каждого из них
выбирается случайно), на которых изображены разные значки; и если выпадает определенная комбинация,
то игрок получает какой-то выигрыш. */

#include <iostream>
#include <time.h>
using namespace std;

// Реализовываем на основе кольцевой очереди (согласно методички к данному уроку)
class QueueRing { 
	enum {ArrSize = 4};
	char Wait[ArrSize+1];
	int QueueLength;
public:
	QueueRing (): QueueLength(0){}
	~QueueRing() { Clear();}
	void Add(char c); 
	bool Extract();        
	void Clear();    
	bool IsEmpty();    
	bool IsFull();     
	void Show();
	void Show2();
	friend void ShowDrums(QueueRing A[], const int N);
	friend void InitDrums (QueueRing A[], const int N);
	friend void RotateDrums (QueueRing A[], const int N);
	friend void ifWin (QueueRing A[], const int N);
};

void QueueRing::Add(char c) {
	if (!IsFull()) {
		Wait[QueueLength++] = c;
	} else {
		cout << "Error.Array is FULL"<<endl;
	}
}

bool QueueRing::Extract(){
	if (!IsEmpty()){
		int temp = Wait [0];
		for (int i = 1; i < QueueLength; ++i){
			Wait [i-1] = Wait [i];
		}
		Wait [QueueLength-1] = temp;
		return 1;
	} else {
		cout << "Error.Array is Empty"<<endl;
		return 0;
	}
}

void QueueRing::Clear() {
	QueueLength = 0;
}

bool QueueRing::IsFull() {
	return QueueLength == ArrSize;
}

bool QueueRing::IsEmpty() {
	return QueueLength == 0;
}


void QueueRing::Show(){
	Show2();
	cout << endl;
}

void QueueRing::Show2(){
	for (int i = 0; i<QueueLength; ++i) {
		cout << Wait[i]<< " ";
	}
}

void ShowDrums(QueueRing *A,const int N){
	for (int k=0; k<N; ++k) {
		(A+k)->Show ();
	}
}


void InitDrums (QueueRing *A,const int N) { // функция для заполнения барабанов значениями в случайном порядке
	for (int k=0; k<N; ++k) {
		int n1, n2=0;
		while (!((A+k)->IsFull())) {
			m: n1 = rand ()%((A+k)->ArrSize)+1;
			if (n1==n2) { // заполняем так, чтобы не повторялось подряд одно и тоже
				goto m;
			} else {
				(A+k)->Add (n1);
				n2 = n1;
			}
		}
	}
}

void RotateDrums (QueueRing *A,const int N){
	for (int k=0; k<N; ++k) {
		int n =	rand () % 20 + 10;
		for (int i = 0; i < n; ++i) {
			(A+k)->Extract ();
			for (int j = 0; j<444723543; j = j + 7){ // искусственное замедление, подбирается под конкретный компьютер
			}
			(A+k)->Show2();
			for (int i = 0; i<(A+k)->ArrSize;++i){
				cout <<"\r\r";
			}
		}
		(A+k)->Show2 ();
		cout << "   Drum was "<< n << " rotated"<<endl;
	}
}

// Условие выигрыша - совпадение всех элементов в любом столбце 
void ifWin (QueueRing *A,const int N){
	int w = 10; // выигрыш

	for (int k, i = 0; i<(A+k)->ArrSize; ++i){
		int flag = 0; // для проверки элементов на разных барабанах в одном и том же индексе
		for (k = 1; k<N; ++k){
			if ((A+k-1)->Wait[i]==(A+k)->Wait[i]){
				flag++;
			} else {
				flag = 0;
				break;
			}
		}
		if (flag) 
			w*=10;
	}
	
	if (w==10){
		cout<<endl << "You Lose!!!"<<endl<<endl;
	} else {
		cout<<endl << "You Win!!!! "<<w<< "$" <<endl<<endl;
	}

}

void main () {
	const int N = 3;
	srand (time(NULL));
	QueueRing A[N]; 
	InitDrums (A,N);
	ShowDrums(A,N);
	getchar ();
	system("cls");
	RotateDrums (A, N);
	ifWin (A, N);
	
}