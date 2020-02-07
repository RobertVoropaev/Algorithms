#include <iostream>
#include <string>
using namespace std;
template <class T>
class FenwickTree
{
public:
	FenwickTree(int len);
	FenwickTree(T* arr, int len);
	~FenwickTree();
	T sum(int leftIndex, int rightIndex) const;
	void updateOnNew(int index, T newValue);
	void updateOnDelta(int index, T delta);
private:
	T* _fenwickArray;
	int _len;
	int _fenwickFunctionAnd(int x) const;
	int _fenwickFunctionOr(int x) const;
};

template <class T>
FenwickTree<T>::FenwickTree(int len)
{
	_len = len;
	_fenwickArray = new T[_len];
	for (int i = 0; i < _len; i++)
		_fenwickArray[i] = 0;

}

template <class T>
FenwickTree<T>::FenwickTree(T* arr, int len)
{
	_len = len;
	_fenwickArray = new T[_len];
	for (int i = 0; i < _len; i++)
		_fenwickArray[i] = 0;
	for (int i = 0; i < _len; i++)
		updateOnDelta(i, arr[i]);
}

template <class T>
FenwickTree<T>::~FenwickTree()
{
	delete[] _fenwickArray;
}

template <class T>
T FenwickTree<T>::sum(int leftIndex, int rightIndex) const
{

	T result = 0;
	while (rightIndex >= 0 && rightIndex < _len)
	{
		result += _fenwickArray[rightIndex];
		rightIndex = _fenwickFunctionAnd(rightIndex) - 1;
	}
	leftIndex--;
	while (leftIndex >= 0 && leftIndex <_len)
	{
		result -= _fenwickArray[leftIndex];
		leftIndex = _fenwickFunctionAnd(leftIndex) - 1;
	}
	return result;
}

template <class T>
int FenwickTree<T>::_fenwickFunctionAnd(int x) const
{
	return (x & (x + 1));
}

template <class T>
int FenwickTree<T>::_fenwickFunctionOr(int x) const
{
	return (x | (x + 1));
}

template <class T>
void FenwickTree<T>::updateOnNew(int index, T newValue)
{
	T oldValue = sum(index, index);
	T delta = newValue - oldValue;
	while (index < _len) {
		_fenwickArray[index] += delta;
		index = _fenwickFunctionOr(index);
	}
}

template <class T>
void FenwickTree<T>::updateOnDelta(int index, T delta)
{
	while (index < _len) {
		_fenwickArray[index] += delta;
		index = _fenwickFunctionOr(index);
	}
}
int main() {
	cout.precision(15);
	int N;
	cin >> N;
	FenwickTree<double> A(N);
	for (int i = 0; i < N; i++)
	{
		double x;
		cin >> x;
		A.updateOnDelta(i,x);
	}
	int M;
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		char str;
		cin >> str;
		if (str == 's')
		{
			int l, r;
			cin >> l >> r;
			cout << A.sum(l - 1, r - 1) << " ";
		}
		else if (str == 'u')
		{
			int i;
			double x;
			cin >> i >> x;
			A.updateOnNew(i - 1, x);
		}
	}
	//system("pause");
	return 0;
}