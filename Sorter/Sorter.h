#ifndef SORTER_H_
#define SORTER_H_


/*
 * Sorter will be able to sort any array of pointers
 * It is assumed that the object of these pointers will have their
 * comparison operators overloaded to the correct matter of comparison
 */

template <class T>
class Sorter {
public:
	T *mergeSort(T *array, int size);
	void quickSort(T *array, int size);
private:
	void quickSort(T *array, int start, int end);
	int partition(T *array, int start, int end, T piv);
	void merge(T *mergedTo, T *a, T *b, int asize, int bsize);
};

#endif /* SORTER_H_ */
