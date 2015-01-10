//Создать шаблонный класс - контейнер Array, который представляет собой массив, позволяющий хранить объекты заданного типа.

#include <iostream>
using namespace std;

template <typename T>
class Array {
	T *Arr;
	size_t count; // текущее число элементов
	size_t size; // текущий размер массива
	size_t grow; // кратность увеличения(уменьшения) размера массива
public:
	Array(){ count = 0; size = grow = 3; Arr = NULL; }   
	~Array(){ free(Arr); } //  delete[] Arr;
	Array(const Array&);
	size_t GetSize(){ return size; } // получение размера массива(количество элементов, под которые выделена память)
	void SetSize(size_t, size_t); // установка размера массива(если параметр size больше предыдущего размера массива, то выделяется дополнительный блок памяти, если нет, то "лишние" элементы теряются и память освобождается); параметр grow определяет для какого количества элементов необходимо выделить память, если количество элементов превосходит текущий размер массива.Например, SetSize(5, 5); означает, что при добавлении 6 - го элемента размер массива становится равным 10, при добавлении 11 - го - 15 и т.д.
	size_t GetUpperBound(){ return count-1; } // получение последнего допустимого индекса в массиве.Например, если при размере массива 10, вы добавляете в него 4 элемента, то функция вернет 3.
	bool IsEmpty(){ return count==0; }
	void FreeExtra(); // удалить "лишнюю" память(выше последнего допустимого индекса)
	void RemoveAll(); // удалить все
	T GetAt(size_t); // получение определенного элемента(по индексу)
	void SetAt(size_t, T); // установка нового значения для определенного элемента(индекс элемента должен быть меньше текущего размера массива)
	T& operator [] (const size_t);  // для реализации двух предыдущих функций
	void Add(T); //добавление элемента в массив(при необходимости массив увеличивается на значение grow функции SetSize)
	Array Append(const Array&) const; //"сложение" двух массивов
	Array& operator =(const Array&);
	T* GetData() { return Arr; } // получения адреса массива с данными
	void InsertAt(size_t, T); //вставка элемента(-ов) в заданную позицию
	void RemoveAt(size_t); // удаление элемента(-ов) с заданной позиции
	void Print(){
		if (count) {
			for (size_t i = 0; i < count; ++i) {
				cout << Arr[i] << "  ";
			}
		}
		else {
			cout << "Empty array";
		}
		cout << "\nsize = " << size << "  count = " << count << "  grow = " << grow << endl << endl;	
	}
};

template <typename T>
void Array<T>::SetSize(size_t size2, size_t grow2 = 3){
	grow = grow2;
	if (size2 > size) {
		if ((size2 - size) % grow) {
			size = size + ((size2 - size) / grow + 1)*grow;
		}
		else {
			size = size2;
		}
	}
	else if (size2 < size) {
		if ((size - size2) % grow) {
			size = size - ((size - size2) / grow )*grow;
		}
		else {
			size = size2;
		}
	}
	if (Arr){ // если память на массив уже выделена
		Arr = (T*)realloc(Arr, sizeof(T)*size);
	}
}

template <typename T>
void Array<T>::FreeExtra(){
	size = count;
	Arr = (T*)realloc(Arr, sizeof(T)*size);
}

template <typename T>
void Array<T>::RemoveAll(){
	free(Arr);  // delete [] Arr
	Arr = NULL;
	count = size = 0;
}

template <typename T>
void Array<T>::Add(T data){
	if (!Arr){ // если память на массив не выделена
		Arr = (T*) malloc(sizeof(T)*size); //Arr = new T[size]; 
	}
	if (count < size) {
		Arr[count++] = data;
	}
	else {
		SetSize(size + grow, grow);
		Arr[count++] = data;
	}
	
}

template <typename T>
T& Array<T>::operator [] (const size_t index){
	if (Arr&&index<count){
		return Arr[index];
	}
	else {
		cout << "ERROR [] - no Elements or no such index" << endl;
	}
}

template <typename T>
T Array<T>::GetAt(size_t index){
	if (index<count){
		T temp = (*this)[index];  // this->operator[](index); //Arr[index]
		return temp;
	} else return 0;
}

template <typename T>
void Array<T>::SetAt(size_t index, T data){ // this->operator[](index); //Arr[index]
	if (index<count){
		(*this)[index] = data;
	}
	else cout << "Error SetAt, because wrong index" << endl;
}

template <typename T>
Array<T> Array<T>::Append(const Array& obj) const{
	Array temp = *this;
	temp.SetSize(size + obj.size, grow);
	for (size_t i = 0; i < obj.count; ++i) {
		temp.Add(obj.Arr[i]);
	}
	return temp;
}

template <typename T>
Array<T>::Array(const Array& obj){
	*this = obj;
}

template <typename T>
Array<T>& Array<T>::operator = (const Array &obj){
	if (this != &obj) {
		count = obj.count;
		size = obj.size;
		grow = obj.grow;
		Arr = (T*)malloc(sizeof(T)*size);  //Arr = new T[size]; 
		for (size_t i = 0; i < count; ++i) {
			Arr[i] = obj.Arr[i];
		}
	}	else return *this;
}

template <typename T>
void Array<T>::InsertAt(size_t index, T data){
	SetSize(++size, grow);
	++count;
	for (size_t i = count - 1; i >= index; --i){
		this->Arr[i] = this->Arr[i - 1];
	}
	(*this)[index] = data;
}

template <typename T>
void Array<T>::RemoveAt(size_t index){
	--count;
	for (size_t i = index; i < count; ++i){
		this->Arr[i] = this->Arr[i + 1];
	}
	SetSize(--size, grow);
}


void main() {
	Array <char> A, C;
	for (int i = 0; i < 3; ++i) {
		A.Add('A'+i);
	}
	A.Print();

	Array <char> B = A;
	B.Add('Z'); B.Add('S');
	B.Print();

	C = B.Append(A);
	C.Print();

	C.InsertAt(3, 'W');
	C.Print();

	C.RemoveAt(5);
	C.Print();
}
