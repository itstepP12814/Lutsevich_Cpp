// Описать класс счетчика

#include <iostream>
using namespace std;
class Counter {
	int k, MIN, MAX;
public:
	Counter() { // конструктор для установки значений по умолчанию
		MIN = 0;
		MAX = 100;
		k = MIN;
		cout << "default values was set k=0 and 0 < k < 100\n";
	}
	void SetMin() { // функция для установки минимального значения
		cout << "Enter min" << endl;
		cin >> MIN;
		k = MIN;
	}
	void SetMax() { // функция для установки максимального значения
		cout << "Enter max" << endl;
		cin >> MAX;
	}
	int Current(){ //функция для возвращения текущего значения счетчика
		return k;
	}
	void Increment() { // функция для увеличения счетчика на 1
		if (k<MAX){
			++k;
		}
		else {
			k = MIN;
		}
	}
	void ShowValues() { // функция для просмотра всех переменных счетчика
		cout << "k = " << k << ", MIN = " << MIN << ", MAX = " << MAX << endl;
	}
};

void main() {
	Counter A; // создали класс счетчика со значениями по умолчанию
	A.ShowValues(); // убедились в предполагаемых значениях

	A.SetMin(); // установили новое минимальное значение
	A.SetMax(); // установили новое максимальное значение
	A.ShowValues();
	for (int i = 0; i<15; ++i) { // проверили, как сработает 15 изменений значения k
		A.Increment();
		A.ShowValues();
	}
	
	cout << "Current value k = " << A.Current() << endl; // проверим как возвращается значение счетчика
}