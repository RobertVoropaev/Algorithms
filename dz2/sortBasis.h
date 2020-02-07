#pragma once
template <class type>
void swap(type *arr, int index1, int index2) {
	if (index1 != index2) {
		type k = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = k;
	}
}
template <class type>
int partition(type *arr, int left, int right, int pivot) {
	swap(arr, pivot, right);
	int j = left;
	for (int i = left; i < right; i++) {
		if (arr[i] <= arr[right]) {
			swap(arr, i, j);
			j++;
		}
	}
	swap(arr, j, right);
	return j;
}
template <class type>
int elements_selection(type *arr, int left, int right) {
	int len = right - left + 1;
	type e1 = arr[left], e2 = arr[left + len / 2], e3 = arr[right];
	if (e1 < e2 && e2 < e3)
		return left + len / 2;
	else if (e2 < e1 && e1 < e3)
		return left;
	else if (e3 < e1 && e1 < e2)
		return left;
	else if (e1 < e3 && e3 < e2)
		return right;
	else if (e2 < e3 && e3 < e1)
		return right;
	else if (e3 < e2 && e2 < e1)
		return left + len / 2;
	else
		return right;
}
template <class type>
int pivot_selection(type *arr, int left, int right) {
	return elements_selection(arr, left, right);
}
template <class type>
void quicksort(type *arr, int left, int right) {
	if (left < right) {
		int pivot = partition(arr, left, right, pivot_selection(arr, left, right));
		quicksort(arr, left, pivot - 1);
		quicksort(arr, pivot + 1, right);
	}
}
template <class type>
void sort(type *arr, int len) {
	quicksort(arr, 0, len - 1);
}