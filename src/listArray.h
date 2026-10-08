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
		T operator[] (int pos);
		template <typename U> //Por warning del compilador, no detecta friend como clase
		friend ostream& operator<<(ostream &out, ListArray<U>& list);
		void resize(int new_size);
};

//Implementamos los métodos en el .h, debido a q es una clase template
void insert(int pos, const T& e) {
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

void append(const T& e) {
	insert(n, e);
}

void prepend(const T& e) {
	insert(0, e);
}

T remove(int pos) {
        if (pos < 0 || pos > n)
                throw out_of_range("Posición fuera de rango");
	

#endif
