/*Разработать класс Person, который содержит соответствующие члены для хранения: имени, возраста, пола и телефонного номера. 
Напишите  функции-члены,  которые  смогут  изменять  эти  члены  данных индивидуально. 
Напишите  функцию-член  Person::Print(),  которая  выводит отформатированные данные о человеке. */
#include <iostream>
#include <string>
using namespace std;
class Person {
	string Name;
	int Age;
	string Sex;
	string TelNum;
public:
	Person () {
		Name = "defaultName";
		Age = 0;
		Sex = "noSex";
		TelNum = "No tel number";
	}
	Person (string name, int age, string sex, string telnum) {
		Name = name;
		Age = age;
		Sex = sex;
		TelNum = telnum;
	}
	void setName (string name) {
		Name = name;
	}
	void setAge (int age) {
		Age = age;
	}
	void setSex (string sex) {
		Sex = sex;
	}
	void setTel (string telnum) {
		TelNum = telnum;
	}
	void Print () {
		cout << Name<< "\t"<<Age<<"\t"<<Sex<<"\t"<<TelNum<<endl;
	}
	~Person () {
	};
};
void main () {
	Person A;
	A.Print ();
	A.setName ("Petya");
	A.setAge (22);
	A.setSex ("female");
	A.setTel ("55-33-44");
	A.Print ();
	Person B ( "fedor", 24, "female", "34-23-34");
	B.Print ();
}