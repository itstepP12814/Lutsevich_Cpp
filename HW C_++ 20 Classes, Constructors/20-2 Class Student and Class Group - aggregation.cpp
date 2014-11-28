//   Написать  класс,  описывающий  группу  студентов.  Студент  также реализуется с помощью соответствующего класса. 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
const int MaxStudentsInGroup = 15;
class Student {
	string Name;
	int Age;
	float Rate;
public:
	Student(){
		Name = "defaultName";
		Age = 0;
		Rate = 0;
	}
	void SetStudent(string name, int age, float rate) {
		Name = name;
		Age = age;
		Rate = rate;
	}
	void ShowStudent() {
		cout << "Name Student is " << Name << "\tAge = " << Age << " \tRate = " << Rate << endl;
	}
	~Student(){
	}
};

class Group {
	int NumberOfGroup;
	int NumberOfStudents;
	Student ListOfStudents[MaxStudentsInGroup];
public:
	Group(){
		NumberOfGroup = 111111;
		NumberOfStudents = 0;
	}
	Group(int NumberOfGroup){ // создание группы с номером
		Group::NumberOfGroup = NumberOfGroup;
		NumberOfStudents = 0;
	}
	~Group() {
	};
	void SetGroupName(int grN) { // присвоение номера группы
		NumberOfGroup = grN;
	}
	void AddStudent(Student a) {
		ListOfStudents[NumberOfStudents] = a;
		++NumberOfStudents;
	}
	void ShowGroup() {
		cout << "Group " << NumberOfGroup << ":" << endl;
		for (int i = 0; i < NumberOfStudents; ++i) {
			ListOfStudents[i].ShowStudent ();
		}
	}
};


void main() {
	Student A; // создаем первого студента 
	A.SetStudent("Lutsevich", 22, 4.5);
	A.ShowStudent();
	Student B; // создаем второго студента 
	B.SetStudent("Micaelin", 21, 4.2);
	B.ShowStudent();
	
	Group C; // создаем первую группу
	C.AddStudent(A);
	C.AddStudent(A);
	C.AddStudent(B);
	C.ShowGroup(); // пока номер группы по умолчанию

	C.SetGroupName(112313); // настраиваем номер группы
	C.AddStudent(B);
	C.ShowGroup();

	Group D(123363); // создаем группу с номером сразу
	D.AddStudent(B);
	D.AddStudent(A);
	D.ShowGroup();
}