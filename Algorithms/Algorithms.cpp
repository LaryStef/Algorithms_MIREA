﻿#include <iostream>
#include <vector>

using namespace std;

template <class T> class Stack {
private:
	T* arr;
	int top;
	int size;
	void Reallocate();
public:
	Stack();
	~Stack();
	T Pop();
	T ShowHead();
	void Push(T num);
	bool IsEmpty();
	void ShowAll();
	int GetLength();
};

template <class T> Stack<T>::Stack() {
	top = -1;
	size = 1;
	arr = new T[size];
}

template <class T> Stack<T>::~Stack() {
	delete[] arr;
}

template <class T> void Stack<T>::Reallocate() {
	T* temp = new T[size * 2];
	copy(arr, arr + size, temp);
	arr = move(temp);
	size *= 2;
}

template <class T> bool Stack<T>::IsEmpty() {
	return top == -1;
}

template <class T> int Stack<T>::GetLength() {
	return top + 1;
}

template <class T> void Stack<T>::ShowAll() {
	if (IsEmpty()) {
		cout << "Stack is empty" << endl;
	}
	for (int i = GetLength(); i > 0; i--) {
		cout << arr[i - 1] << " ";
	}
}

template <class T> void Stack<T>::Push(T value) {
	if (GetLength() == size) {
		Reallocate();
	}
	arr[++top] = value;
}

template <class T> T Stack<T>::ShowHead() {
	if (IsEmpty()) {
		return NULL;
	}
	return arr[top];
}

template <class T> T Stack<T>::Pop() {
	if (IsEmpty()) {
		return NULL;
	}
	return arr[top--];
}

template <class T> class StackSort : public Stack<T> {
public:
	using Stack<T>::GetLength;
	using Stack<T>::Pop;
	using Stack<T>::ShowHead;
	using Stack<T>::Push;

	T Get(int pos);
	void Set(int pos, T num);
	void Sort(int N);
};

template <class T> T StackSort<T>::Get(int pos) {
	Stack<T> temp = Stack<T>();
	T target;

	for (int i = GetLength() - 1; i > pos; i--) {
		temp.Push(Pop());
	}
	target = ShowHead();
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());
	}

	return target;
}

template <class T> void StackSort<T>::Set(int pos, T num) {
	Stack<T> temp = Stack<T>();
	
	for (int i = GetLength() - 1; i > pos; i--) {
		temp.Push(Pop());
	}
	Pop();
	Push(num);
	for (int i = temp.GetLength(); i > 0; i--) {
		Push(temp.Pop());
	}
}

template <class T> void StackSort<T>::Sort(int n) {
	int m = 0;

	for (int i = 0; i < n; i++) {
		m = max(m, Get(i));
	}

	StackSort<int> countStack = StackSort<int>();

	for (int i = 0; i <= m; i++) {
		countStack.Push(0);
	}

	for (int i = 0; i < n; i++) {

		countStack.Set(Get(i), countStack.Get(Get(i)) + 1);

	}

	for (int i = 1; i <= m; i++) {
		countStack.Set(i, countStack.Get(i) + countStack.Get(i - 1));

	}

	StackSort<int> outputStack = StackSort<int>();

	for (int i = 0; i < n; i++) { outputStack.Push(0); }

	for (int i = n - 1; i >= 0; i--)
	{
		outputStack.Set(countStack.Get(Get(i)) - 1, Get(i));
		countStack.Set(Get(i), countStack.Get(Get(i)) - 1);
	}

	//*this = outputStack&;

	for (int i = 0; i < n; i++) {
		Set(i, outputStack.Pop());
	}
}

int main()
{
	StackSort<int> stack = StackSort<int>();

	for (int i = 0; i < 5; i++) {
		stack.Push(i);
	}
	for (int i = 3; i < 8; i++) {
		stack.Push(i);
	}

	stack.ShowAll();
	cout << endl;
	stack.Sort(10);
	stack.ShowAll();
	cout << endl;
}
