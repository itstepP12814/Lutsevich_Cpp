/*Создайте класс Date, который будет содержать информацию о дате (день, месяц, год).
С   помощью   механизма   перегрузки   операторов,   определите операцию   разности   
двух   дат   (результат   в   виде   количества   дней   между датами),  а  также
операцию увеличения даты на определенное  количество дней.*/

#include <iostream>
using namespace std;
// это будет пока упрощенная реализация пока без учета настоящей математики дат 
class Date
{
	int day;
	int month;
	int year;
public:
	Date ();
	Date (int d, int m, int y);
	Date (const Date &source);
	void set (int day, int month, int year);
	void print ();
	int operator-(const Date &source) const;
	Date operator+(const int &days) const;
};
Date::Date () {
	day = 0;
	month = 0;
	year = 0;
}
Date::Date (int d, int m, int y) {
	if (d > 0 && d < 31) {
		day = d;
	} else {
		cout << "Error day range! ";
		day = 0;
	}
	if (m > 0 && m < 13) {
		month = m;
	} else {
		cout << "Error month range! ";
		month = 0;
	}
	if (y > 0 && y < 2200) {
		year = y;
	} else {
		cout << "Error year range! ";
		year = 0;
	}
}
Date::Date (const Date &source){
	day = source.day;
	month = source.month;
	year = source.year;
};
void Date::set (int d, int m, int y) {
	if (d > 0 && d < 31) {
		day = d;
	} else {
		cout << "Error day range! ";
		day = 0;
	}
	if (m > 0 && m < 13) {
		month = m;
	} else {
		cout << "Error month range! ";
		month = 0;
	}
	if (y > 0 && y < 2200) {
		year = y;
	} else {
		cout << "Error year range! ";
		year = 0;
	}
}
void Date::print ( ) {
	cout << day << "." << month << "."<< year << endl;
}
int Date::operator-(const Date &source) const {
	int res;
	Date temp;
	temp.day = day - source.day;
	temp.month = month - source.month;
	temp.year = year - source.year;
	res = temp.day + 30 * temp.month + 365 * temp.year;
	return res;
}

Date Date::operator+(const int &days) const {
	Date temp;
	temp.day = day + days;
	temp.month = month;
	temp.year = year;
	return temp;
}

void main () {
	Date D;
	D.print (); 
	Date D2 (35, 13, 2014);  // проверка ошибочного ввода
	D2.set (12, 12, 2012);
	D2.print ();

	Date D3 (D2);
	D3.print ();

	Date D4 (11,11,2010);
	int minus = D3 - D4;

	minus = D3-D4;
	cout << minus<<endl;

	Date D5 = D4+minus;
	D5.print();
}

