#pragma once
template <class T>
class FenwickTree
{
public:
	FenwickTree(int len);
	FenwickTree(T* arr, int len);
	FenwickTree(const FenwickTree& obj);
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
FenwickTree<T>::FenwickTree(const FenwickTree<T>& obj)
{
	_len = obj._len;
	_fenwickArray = new T[_len];
	for (int i = 0; i < _len; i++)
		_fenwickArray[i] = obj._fenwickArray[i];
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