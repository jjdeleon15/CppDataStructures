/*
 * Sorter.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: juliandeleon
 */

#include "Sorter.h"
#include <cstdlib>

int randInRange(int lower, int upper) {
	int r = rand() % (upper - lower + 1);
	return lower + r;
}

template <class T>
T *Sorter<T>::mergeSort(T *array, int size) {
	T *temp = new T[size];
	T *mergeTo = temp;
	T *mergeFrom = array;
	int i, s, mid, rem, remp, n, l;
	for (i = 2; i < size; i *= 2) {
		mid = i/2;
		n = size / i;
		for (s = 0, l = 0; l < n ; s += i, l++)
			merge(&mergeTo[s], &mergeFrom[s], &mergeFrom[s + mid], mid, mid);
		rem = size % i;
		if (rem > mid) {
			remp = size - rem;
			merge(&mergeTo[remp], &mergeFrom[remp], &mergeFrom[remp + mid], mid, rem - mid);
		}
		swap(mergeTo, mergeFrom);
	}
	mid = i / 2;
	merge(&mergeTo[0], &mergeFrom[0], &mergeFrom[mid], mid, size - mid);
	return mergeTo;
}

template <class T>
void Sorter<T>::merge(T *mergedTo, T *a, T *b, int asize, int bsize) {
	int l = 0, r = 0, c = 0;
	while (l < asize && r < bsize) {
		if (*a[l] < *b[r]) {
			mergedTo[c] = a[l];
			l++;
		} else {
			mergedTo[c] = b[r];
			r++;
		}
		c++;
	}
	if (l < asize) {
		do {
			mergedTo[c] = a[l];
			l++;
			c++;
		} while (l < asize);
	} else {
		do {
			mergedTo[c] = b[r];
			r++;
			c++;
		} while (r < bsize);
	}
}

template <class T>
void Sorter<T>::quickSort(T *array, int size) {
	if (size > 1)
		quickSort(array, 0, size - 1);
}

template <class T>
void Sorter<T>::quickSort(T *array, int start, int end) {
	T piv = array[randInRange(start, end)];
	int pIndex = partition(array, start, end, piv);
	if (start < pIndex - 1)
		quickSort(array, start, pIndex - 1);
	if (pIndex < end)
		quickSort(array, pIndex, end);
}

/**
 * will partition the array with the specified piv
 * returns index of first element >= piv
 */
template <class T>
int Sorter<T>::partition(T *array, int start, int end, T piv) {
	int s = start, e = end;
	while (s <= e) {
		if (*array[s] >= *piv) {
			swap(array[s], array[e]);
			e--;
		} else {
			s++;
		}
	}
	if (*array[s] < *piv) {
		s++;
	}
	return s;
}
