/*Создайте класс Время, в котором реализованы операции сложения, вычитания, сравнения,
ввода и вывод на экран.
Возможность конвертации времени из американского формата am (pm): 10:00 pm = 22:00, 12:00 pm =00:00 */

#include <iostream>
using namespace std;

//в данном коде сознательно не учтены многие нюансы, т.к. нет пока времени их выводить
class Time {
	unsigned hours;
	unsigned minutes;
public:
	Time(unsigned h = 0, unsigned m = 0, char* apm = 0);
	void ShowTime();
	~Time(){};
	Time operator+(const Time &source) const;
	Time operator-(const Time &source) const;
	bool operator>(const Time &source) const;
	bool operator<(const Time &source) const;
	bool operator==(const Time &source) const;
	bool operator>=(const Time &source) const;
	bool operator<=(const Time &source) const;
	bool operator!=(const Time &source) const;
	void operator() (unsigned, unsigned);
	friend istream& operator>>(istream& is, Time& T);
	friend ostream& operator<<(ostream& os,const Time& T);
	void ConvertTime();	
};

Time::Time(unsigned h, unsigned m, char* apm){
	if (apm == "pm")
		h = h + 12;
	if ((h >= 0 && h < 24)&&(m>=0 && h<60))  {
		hours = h;
		minutes = m;
	}
	else {
		hours = 23;
		minutes = 59;
		cout << "ERROR time is out of range" << endl;
	}	
}

void Time::ShowTime() {
	if (hours < 10) {
		cout << "0" << hours;
	}
	else {
		cout << hours;
	}
	cout << ":";
	if (minutes < 10) {
		cout << "0" << minutes;
	}
	else {
		cout << minutes;
	}
	cout << endl;
}

Time Time::operator+(const Time &source) const {
	Time temp;
	int fullminutes1;
	int fullminutes2;
	fullminutes1 = hours * 60 + minutes;
	fullminutes2 = source.hours * 60 + source.minutes;
	int count = 0;
	temp.hours = (fullminutes1 + fullminutes2) / 60;
	for (; temp.hours >= 24; ++count, temp.hours -= 24);
	temp.minutes = fullminutes1+fullminutes2 - temp.hours*60 - count*24*60;
	return temp;
}

Time Time::operator-(const Time &source) const {// скорее всего математически плохой подсчет, но пока нет времени придумать получше.
	Time temp;
	int fullminutes1, fullminutes2;
	fullminutes1 = hours * 60 + minutes;
	fullminutes2 = source.hours * 60 + source.minutes;
	int R = fullminutes1 - fullminutes2;
	if (R >= 0) {
		int count = 0;
		temp.hours = R / 60;
		for (; temp.hours >= 24; ++count, temp.hours -= 24);
		temp.minutes = R - temp.hours * 60 - count * 24 * 60;
	}
	else {
		int count = 0;
		temp.hours = -R / 60;
		for (; temp.hours >= 24; ++count, temp.hours -= 24);
		temp.minutes = -R - temp.hours * 60 - count * 24 * 60;
		int fullminutes3 = temp.hours * 60 + temp.minutes;
		temp.hours = (1440 - fullminutes3) / 60;
		temp.minutes = (1440-fullminutes3) - temp.hours * 60;
	}
	return temp;
}

bool Time::operator>(const Time &source) const{
	int fullmunutes1 = hours * 60 + minutes;
	int fullmunutes2 = source.hours * 60 + source.minutes;
	if (fullmunutes1 > fullmunutes2)
		return true;
	else return false;
}

bool Time::operator<(const Time &source) const{
	if (this->operator>(source))
		return false;
	else return true;
}

bool Time::operator==(const Time &source) const{
	if ((hours == source.hours) && (minutes == source.minutes))
		return true;
	else
		return false;
}

bool Time::operator>=(const Time &source) const{
	if (this->operator>(source) || this->operator==(source))
		return true;
	else
		return false;
}

bool Time::operator<=(const Time &source) const{
	if (this->operator<(source) || this->operator==(source))
		return true;
	else
		return false;
}

bool Time::operator!=(const Time &source) const{
	if (this->operator==(source))
		return false;
	else
		return true;
}

void Time::operator() (unsigned h, unsigned m){
	hours = h;
	minutes = m;
}

istream& operator>>(istream& is, Time& T){
	cout << "Set Hours ";
	int temp;
	is >> temp;
	if (temp >= 0 && temp < 24) {
		T.hours = temp;
	} 	else cout << "ERROR hour enter" << endl;
	cout << "Set minutes ";
	is >> temp;
	if (temp >= 0 && temp < 60) {
		T.minutes = temp;
	}
	else cout << "ERROR minutes enter" << endl;
	return is;
}

ostream& operator<<(ostream& os, const Time& T){
	if (T.hours < 10)
		os << 0;
	os << T.hours << ":";
	if (T.minutes < 10)
		os << 0;
	os << T.minutes<<"\n";
	return os;
}


void main() {
	Time T1 (1,45,"pm");
	T1.ShowTime();

	Time T2(2,50);
	T2.ShowTime();

	Time T3 = T1+T2;
	T3.ShowTime();

	T3 = T1 - T2;
	T3.ShowTime();
	
	cout << (T2 > T1) << endl;
	cout << (T1 < T2) << endl;
	cout << (T1 == T2) << endl;
	T3(3, 4);
	T3.ShowTime();
	Time C;
	cin >> C;
	system("cls");
	cout << C;
}