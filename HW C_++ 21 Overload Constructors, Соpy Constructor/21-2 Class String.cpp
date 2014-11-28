/*Разработать класс String, содержащий: 
	конструктор  по  умолчанию,  позволяющий  создать  строку  длиной  80 символов; 
	конструктор, позволяющий создавать строку произвольного размера; 
	конструктор,  который  создаёт  строку  и  инициализирует  её  строкой, полученной от пользователя. 
	методы  для  ввода  строк  с  клавиатуры  и  вывода строк на экран. */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class String {
	char *s;
	size_t lenght; // тип для хранения длины это тоже unsigned т.е. это для эффективного создания ассемблерного кода
public:
	~String ();
	String () ; // конструктор по умолчанию без параметров
	String (const int size); // конструктор для создания строки определенной длинны
	String (const String &user); // конструктор копирования
	char* Input ();
	void Print ();
};
String::~String () {
	free (s);
}
 
String::String (){
	s = (char *) malloc (81);
	lenght = 81;
	s [80] = '\0';
}
String::String (int size){
	s = (char *) malloc (size+1); 
	lenght = size+1;
	s [size] = '\0';
}

String::String (const String &user) {
	//cout << "COPY" << endl;
	lenght = user.lenght;
	s = (char*) malloc (lenght);
	strcpy (s, user.s);
}

char* String::Input () { // как быть с превышениями строки??
	cin >> s;
	return s;
}


void String::Print( ){
	cout << s << endl;
}

void main () {
	String A;
	A.Input ();
	A.Print ();

	cout << endl;
	String C=A;
	C.Print ();
}