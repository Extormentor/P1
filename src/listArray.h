#ifndef LISTARRAY_H
#define LISTARRAY_H
#include <ostream>
#include <stdecept>
#include "list.h"

using namespace std;

template <typename T>
class ListArray: public List<T> {
	private:
		T* arr;
		int max, n;
		static const int MINSIZE;
		void resize(int new_size);
	
	public:
		//Métodos clase list
		void insert(int pos, const T& e) override;
		void append(const T& e) override;
		void prepend(const T& e) override;
		T remove(int pos) override;
		T get(int pos) const override;
		int search(const T& e) const override;
		bool empty() const override;
		int size() const override;
		//Métodos clase ListArray
		ListArray();
		~ListArray() override {
			delete arr[];
		}
		T operator[] (int pos);
		template <typename U> //Por warning del compilador, no detecta friend como clase
		friend ostream& operator<<(ostream &out, ListArray<U>& list);
};

int ListArray<T>::MINSIZE = 2;

//Implementamos los métodos en el .h, debido a q es una clase template
template <typename T>
void ListArray<T>::insert(int pos, const T& e) {
	if (pos < 0 || pos > n)
        	throw out_of_range("Posición fuera de rango");

    	if (n == max){ 
        	resize(max*2);
   	 	insert(pos, e);
	}

   	for (int i = n; i > pos; --i) 
       		arr[i] = arr[i - 1];

   	arr[pos] = e;
    	n++;
}

template <typename T>
void ListArray<T>::append(const T& e) {
	insert(n, e);
}

template <typename T>
void ListArray<T>::prepend(const T& e) {
	insert(0, e);
}

template <typename T>
T ListArray<T>::remove(int pos) {
        if (pos < 0 || pos > n)
                throw out_of_range("Posición fuera de rango");

	T pos_eliminada = arr[pos];

	for (int i = pos; i < n-1; i++)      
		arr[i] = arr[i + 1];
	
        n--;
	return pos_eliminada;
}

template <typename T>
T ListArray<T>::get(int pos) {
	if (pos < 0 || pos > n)
                throw out_of_range("Posición fuera de rango");
	
	return arr[pos];
}

template <typename T>
int ListArray<T>::search(const T& e) {
	if(n-1 > 0) {
		for(int i = 0; i < n-1; i++){
			if(arr[i]==e)
				return i;
		}
	}else
		return -1;
}

template <typename T>
bool ListArray<T>::empty() {
	if(n <= 1)
		return true;
	else
		return false;
}

template <typename T>
int ListArray<T>::size() {
	int n = sizeof(arr);
	return n;
}

template <typename T>
ListArray<T>::ListArray() {
	max = MINSIZE;
	arr = new T[MINSIZE];
	n = 0;	
}

template <typename T>
T ListArray<T>::operator[] (int pos) {
	if (pos < 0 || pos > n)
                throw out_of_range("Posición fuera de rango");
	
	return arr[pos];
}

template <typename U>
friend ostream& operator<<(ostream &out, ListArray<U>& list) {
	for(int i = 0; i < list.n; i++) 
		out << list.arr[i] << " ";
	
	cout << endl;
	return out;
}

template <typename T>
void ListArray<T>::resize(int new_size) {
	if (new_size < n || new_size < MINSIZE)
	        throw invalid_argument("Tamaño de redimensionado no válido");

	T* arr2 = new T[new_size];

	for(int i = 0; i < n; i++)
		arr2[i] = arr[i];
	
	delete arr[];
	arr = arr2;
	max = new_size;
}

#endif
