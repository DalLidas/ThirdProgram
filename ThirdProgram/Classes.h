#pragma once

#include "pch.h"

template <typename T = int>
class ISort {
protected:
	int numOfCompares;
	int numOfSwaps;
	int executionTime;

public:
	ISort() { 
		numOfCompares = 0;
		numOfSwaps = 0;
		executionTime = 0;
	}

	virtual ~ISort() = default;

	void Swap(vector<T>& arr, int first, int second) {
		swap(arr[first], arr[second]);
		++numOfSwaps;
	}
	
	inline bool IsBigger(T a, T b){
		++numOfCompares;
		return a > b;
	}
	
	inline bool IsSmaller(T a, T b){
		++numOfCompares;
		return a < b;
	}

	virtual void Sort(vector<T>& arr) = 0;

	virtual string Name() = 0;
	
	inline int GetNumOfCompares() const{
		return numOfCompares;
	}

	inline int GetNumOfOperations() const{ 
		return numOfSwaps;
	}

	inline int GetTime() const{
		return executionTime;
	}

	inline string Info() const{
		return  "Num of compares: " + to_string(numOfCompares) + " || "
			+ "Num of swaps: " + to_string(numOfSwaps) + " || "
			+ "Execution time: " + to_string(executionTime);
	}

	inline void Clear() {
		numOfCompares = 0;
		numOfSwaps = 0;
		executionTime = 0;
	}

};

template <typename T = int>
class BubbleSort : public ISort<T> {
public:
	using ISort<T>::numOfCompares;
	using ISort<T>::numOfSwaps;
	using ISort<T>::executionTime;

	BubbleSort(){}

	virtual ~BubbleSort() = default;

	virtual string Name() override final {
		return "BubbleSort";
	}

	virtual void Sort(vector<T>& arr) override final{
		int startTime = clock();

		for (auto i = 0; i < arr.size() - 1; ++i) {
			for (auto j = 0; j < arr.size() - i - 1; ++j) {
				if (ISort<T>::IsBigger(arr[j], arr[j + 1])) {
					ISort<T>::Swap(arr, j, j+1);
				}
			}
		}

		int endTime = clock();
		executionTime = endTime - startTime;
	}

};

template <typename T = int>
class SelectionSort : public ISort<T> {
public:
	using ISort<T>::numOfCompares;
	using ISort<T>::numOfSwaps;
	using ISort<T>::executionTime;

	SelectionSort() {}

	virtual ~SelectionSort() = default;

	virtual string Name() override final {
		return "SelectionSort";
	}

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		for (auto step = 0; step < arr.size() - 1; step++) {
			auto min_idx = step;
			for (auto i = step + 1; i < arr.size(); i++) {
				if (ISort<T>::IsSmaller(arr[i], arr[min_idx])) {
					min_idx = i;
				}
			}
			ISort<T>::Swap(arr, min_idx, step);
		}
		
		int endTime = clock();
		executionTime = endTime - startTime;
	}

};

template <typename T = int>
class InsertionSort : public ISort<T> {
public:
	using ISort<T>::numOfCompares;
	using ISort<T>::numOfSwaps;
	using ISort<T>::executionTime;

	InsertionSort() {}

	virtual ~InsertionSort() = default;

	virtual string Name() override final {
		return "InsertionSort";
	}

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		for (auto i = 1; i < arr.size(); ++i){
			for (auto j = i; j > 0; --j) {
				if (ISort<T>::IsBigger(arr[j - 1], arr[j])) {
					ISort<T>::Swap(arr, j - 1, j);
				}
				else {
					break;
				}
			}
		}
			
		int endTime = clock();
		executionTime = endTime - startTime;
	}

};

template <typename T = int>
class ShellSort : public ISort<T> {
public:
	using ISort<T>::numOfCompares;
	using ISort<T>::numOfSwaps;
	using ISort<T>::executionTime;

	ShellSort() {}

	virtual ~ShellSort() = default;

	virtual string Name() override final {
		return "ShellSort";
	}

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		for (int interval = arr.size() / 2; interval > 0; interval /= 2) {
			for (int i = interval; i < arr.size(); i += 1) {
				T temp = arr[i];
				int j;
				for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
					arr[j] = arr[j - interval];
					++numOfCompares;
					++numOfSwaps;
				}
				arr[j] = temp;
			}
		}

		int endTime = clock();
		executionTime = endTime - startTime;
	}

};

template <typename T = int>
class QuickSort : public ISort<T> {
	// Процедура быстрой сортировки
	void quicksort(vector<T>& arr, int start, int end)
	{
		// базовое условие
		if (start >= end) {
			return;
		}

		// переставить элементы по оси
		int pivot = partition(arr, start, end);

		// повторяем подмассив, содержащий элементы, меньшие опорной точки
		quicksort(arr, start, pivot - 1);

		// повторяем подмассив, содержащий элементы, превышающие точку опоры
		quicksort(arr, pivot + 1, end);
	}

	int partition(vector<T>& arr, int start, int end)
	{
		// Выбираем крайний правый элемент в качестве опорного элемента массива
		T pivot = arr[end];

		// элементы, меньшие точки поворота, будут перемещены влево от `pIndex`
		// элементы больше, чем точка поворота, будут сдвинуты вправо от `pIndex`
		// равные элементы могут идти в любом направлении
		int pIndex = start;

		// каждый раз, когда мы находим элемент, меньший или равный опорному, `pIndex`
		// увеличивается, и этот элемент будет помещен перед опорной точкой.
		for (int i = start; i < end; i++)
		{
			if (arr[i] <= pivot)
			{
				swap(arr[i], arr[pIndex]);
				pIndex++;
				
				++numOfSwaps;
			}
			++numOfCompares;
		}

		// поменять местами `pIndex` с пивотом
		swap(arr[pIndex], arr[end]);
		++numOfSwaps;

		// вернуть `pIndex` (индекс опорного элемента)
		return pIndex;
	}

public:
	using ISort<T>::numOfCompares;
	using ISort<T>::numOfSwaps;
	using ISort<T>::executionTime;

	QuickSort() {}

	virtual ~QuickSort() = default;

	virtual string Name() override final {
		return "QuickSort";
	}

	virtual void Sort(vector<T>& arr) override final { // Разделение по схеме Lomuto
		int startTime = clock();

		quicksort(arr, 0, static_cast<int>(arr.size() - 1));

		int endTime = clock();
		executionTime = endTime - startTime;
	}
};
