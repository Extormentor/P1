#ifndef LISTARRAY_H
#define LISTARRAY_H
#include <ostream>
#include <iostream>
#include <stdexcept>
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
        // Métodos clase list
        void insert(int pos, T e) override;
        void append(T e) override;
        void prepend(T e) override;
        T remove(int pos) override;
        T get(int pos) const override;
        int search(T e) const override;
        bool empty() const override;
        int size() const override;

        // Métodos clase ListArray
        ListArray();

        ~ListArray() override {
                delete[] arr;
        }

        T operator[](int pos);

        // friend se debe declarar siempre dentro de la clase
        friend ostream& operator<<(ostream &out, ListArray<T>& list) {
                out << "[";
                if (list.n > 0)
                        out << "\n";

                for (int i = 0; i < list.n; i++)
                        out << "  " << list.arr[i] << "\n";

                out << "]";
                return out;
        }
};

template <typename T>
const int ListArray<T>::MINSIZE = 2;

// Implementamos los métodos en el .h, debido a que es una clase template
template <typename T>
void ListArray<T>::insert(int pos, T e) {
        if (pos < 0 || pos > n)
                throw out_of_range("Posición inválida!");

        if (n == max)
                resize(max * 2);

        for (int i = n; i > pos; --i)
                arr[i] = arr[i - 1];

        arr[pos] = e;
        n++;
}

template <typename T>
void ListArray<T>::append(T e) {
        insert(n, e);
}

template <typename T>
void ListArray<T>::prepend(T e) {
        insert(0, e);
}

template <typename T>
T ListArray<T>::remove(int pos) {
        if (pos < 0 || pos >= n)
                throw out_of_range("Posición inválida!");

        T pos_eliminada = arr[pos];

        for (int i = pos; i < n - 1; i++)
                arr[i] = arr[i + 1];

        n--;
        return pos_eliminada;
}

template <typename T>
T ListArray<T>::get(int pos) const {
        if (pos < 0 || pos >= n)
                throw out_of_range("Posición inválida!");

        return arr[pos];
}

template <typename T>
int ListArray<T>::search(T e) const {
        for (int i = 0; i < n; i++) {
                if (arr[i] == e)
                        return i;
        }

        return -1;
}

template <typename T>
bool ListArray<T>::empty() const {
        return n == 0;
}

template <typename T>
int ListArray<T>::size() const {
        return n;
}

template <typename T>
ListArray<T>::ListArray() {
        max = MINSIZE;
        arr = new T[MINSIZE];
        n = 0;
}

template <typename T>
T ListArray<T>::operator[](int pos) {
        if (pos < 0 || pos >= n)
                throw out_of_range("Posición inválida!");

        return arr[pos];
}

template <typename T>
void ListArray<T>::resize(int new_size) {
        if (new_size < n || new_size < MINSIZE)
                throw invalid_argument("Tamaño de redimensionado no válido");

        T* arr2 = new T[new_size];

        for (int i = 0; i < n; i++)
                arr2[i] = arr[i];

        delete[] arr;
        arr = arr2;
        max = new_size;
}

#endif
