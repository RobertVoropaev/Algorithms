#pragma once
#include "sortBasis.h"
template <class type, class Cmp>
int partitionCmp(type *arr, int left, int right, int pivot, Cmp cmp) {
	swap(arr, pivot, right);
	int j = left;
	for (int i = left; i < right; i++) {
		if (cmp(arr[i],arr[right])) {
			swap(arr, i, j);
			j++;
		}
	}
	swap(arr, j, right);
	return j;
}
template <class type, class Cmp>
void quicksortCmp(type *arr, int left, int right, Cmp cmp) {
	if (left < right) {
		int pivot = partitionCmp(arr, left, right, pivot_selection(arr, left, right), cmp);
		quicksortCmp(arr, left, pivot - 1, cmp);
		quicksortCmp(arr, pivot + 1, right, cmp);
	}
}
template <class type, class Cmp>
void sort(type *arr, int len, Cmp cmp) {
	quicksortCmp(arr, 0, len - 1, cmp);
}
