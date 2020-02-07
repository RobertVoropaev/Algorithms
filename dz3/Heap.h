#pragma once
#include <vector>
#include <iostream>
using namespace std;
template <class type>
class Heap {
	vector <type> heap;
	void siftUp(int i);
	void siftDown(int i);
	void heapfly();
public:
	Heap(vector<type> a);
	Heap(type *m, int len);
	Heap(vector<int>::iterator i1, vector<int>::iterator i2);
	void add(type a);
	void update(type a, int i);
	type extractMax();
	type getMax();
	void show();
	int size();
	bool empty();
	vector<type> sort();
	Heap operator=(const Heap &A);
};
template <class type>
void Heap<type>::siftUp(int i) {
	int parent = (i - 1) / 2;
	while (heap[i] > heap[parent]) {

		swap(heap[i], heap[parent]);
		i = parent;
		parent = (i - 1) / 2;
	}
}
template <class type>
void Heap<type>::siftDown(int i) {
	while ((i * 2) + 1 < heap.size()) {
		int left = (i * 2) + 1, right = (i * 2) + 2;
		int j = left;
		if (right < heap.size() && heap[right] > heap[left])
			j = right;
		if (heap[i] >= heap[j])
			break;
		swap(heap[i], heap[j]);
		siftDown(i);
		i = j;
	}
}
template <class type>
void Heap<type>::heapfly() {
	for (int i = heap.size() / 2; i >= 0; i--)
		siftDown(i);
}
template <class type>
Heap<type>::Heap(vector<type> a) {
	for (int i = 0; i < a.size(); i++) {
		heap.push_back(a[i]);
	}
	heapfly();
}
template <class type>
Heap<type>::Heap(type *m, int len) {
	for (int i = 0; i < len; i++)
		heap.push_back(m[i]);
	heapfly();
}
template <class type>
Heap<type>::Heap(vector<int>::iterator i1, vector<int>::iterator i2) {
	while (i1 != i2) {
		heap.push_back(*i1);
		i1++;
	}
	heapfly();
}
template <class type>
void Heap<type>::add(type a) {
	heap.push_back(a);
	siftUp(heap.size() - 1);
}
template <class type>
void Heap<type>::update(type a, int i) {
	if (heap[i] < a) {
		heap[i] = a;
		siftUp(i);
	}
	else if (heap[i] > a) {
		heap[i] = a;
		siftDown(i);
	}
}
template <class type>
type Heap<type>::extractMax() {
	type max = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.pop_back();
	siftDown(0);
	return max;
}
template <class type>
type Heap<type>::getMax() {
	return heap[0];
}
template <class type>
void Heap<type>::show() {
	for (int i = 0;i < heap.size(); i++)
		cout << heap[i] << " ";
	cout << endl;
}
template <class type>
int Heap<type>::size() {
	return heap.size();
}
template <class type>
bool Heap<type>::empty() {
	return !heap.size();
}
template <class type>
vector <type> Heap<type>::sort() {
	Heap A = *this;
	vector <type> m;
	while (!A.empty())
		m.push_back(A.extractMax());
	return m;
}
template <class type>
Heap<type> Heap<type>::operator=(const Heap &A) {
	Heap B(A.heap);
	B.heapfly();
	return B;
}