/*Добавить  в  строковый  класс  функцию, которая  создает  строку,
содержащую пересечение двух строк, то есть общие символы для двух строк.
Например, результатом  пересечения  строк  "sdqcg"  "rgfas34"  будет  строка
"sg".Для  реализации  функции  перегрузить  оператор  *  (бинарное
умножение).*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
class String {
	char *s;
	size_t lenght;
public:
	~String ();
	String () ;
	String(const char* str);
	String (const String &user);
	void Print ();
	String operator*(const String &source) const;
};
String::~String () {
	free (s);
}
String::String (){
	s = (char *) malloc (81);
	lenght = 81;
	s [80] = '\0';
}
String::String(const char* str){
	lenght = strlen(str);
	s = (char*)malloc((lenght + 1)*sizeof(char));
	strcpy(s, str);
}
String::String (const String &user) {
	lenght = user.lenght;
	s = (char*)malloc((lenght + 1) * sizeof(char)); // память выделяется на 1 больше длины!!
	strcpy (s, user.s);
}
String String::operator*(const String &source) const {
	String temp;
	int k = 0;
	for (size_t i = 0; i < lenght; ++i) {
		for (size_t j = 0; j < source.lenght; ++j) {
			if (s[i] == source.s[j]) {
				temp.s[k] = s[i];
				++k;
			}
		}
	}
	temp.s[k] = '\0';
	temp.lenght = k;
	return temp;
}

void String::Print( ){
	cout << s << endl;
}

void main () {
	String S1("sdqcg");
	String S2("rgfas34");
	String SS = S1*S2;
	SS.Print();
}