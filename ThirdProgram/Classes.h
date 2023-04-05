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
	
	inline bool isBigger(T a, T b){
		++numOfCompares;
		return a > b;
	}
	
	inline bool isSmaller(T a, T b){
		++numOfCompares;
		return a < b;
	}

	virtual void Sort(vector<T>& arr) = 0;
	
	inline int GetNumOfCompares() const{
		return numOfCompares;
	}

	inline int GetNumOfOperations() const{ 
		return numOfSwaps;
	}

	inline int GetTime() const{
		return executionTime;
	}

	inline void Info() const{
		cout << "Num of compares: " << numOfCompares << " || "
			<< "Num of swaps: " << numOfSwaps << " || "
			<< "Execution time: " << executionTime;
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

	virtual void Sort(vector<T>& arr) override final{
		int startTime = clock();

		for (auto i = 0; i < arr.size() - 1; ++i) {
			for (auto j = 0; j < arr.size() - i - 1; ++j) {
				if (ISort<T>::isBigger(arr[j], arr[j + 1])) {
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

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		for (auto i = 0; i < arr.size(); ++i){
			for (auto j = i + 1; j < arr.size(); ++j){
				if (ISort<T>::isBigger(arr[i], arr[j])){
					ISort<T>::Swap(arr, i, j);
				}
			}
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

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		for (auto i = 1; i < arr.size(); i++){
			for (auto j = i; j > 0; j--) {
				if (ISort<T>::isBigger(arr[j - 1], arr[j])) {
					ISort<T>::Swap(arr, j - 1, j);
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

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		// Start with a big gap, then reduce the gap
		for (auto gap = arr.size() / 2; gap > 0; gap /= 2)
		{
			// Do a gapped insertion sort for this gap size.
			// The first gap elements a[0..gap-1] are already in gapped order
			// keep adding one more element until the entire array is
			// gap sorted 
			for (auto i = gap; i < arr.size(); i += 1)
			{
				// add a[i] to the elements that have been gap sorted
				// save a[i] in temp and make a hole at position i
				T temp = arr[i];

				// shift earlier gap-sorted elements up until the correct 
				// location for a[i] is found
				int j;
				for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
					arr[j] = arr[j - gap];

				//  put temp (the original a[i]) in its correct location
				arr[j] = temp;
			}
			
		}

		/*for (int i = 1; i < arr.size(); i++) {
			for (int j = i; j > 0; j--) {
				if (ISort<T>::isBigger(arr[j - 1], arr[j])) {
					ISort<T>::Swap(arr, j - 1, j);
				}
			}
		}*/

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
			}
		}

		// поменять местами `pIndex` с пивотом
		swap(arr[pIndex], arr[end]);

		// вернуть `pIndex` (индекс опорного элемента)
		return pIndex;
	}

public:
	using ISort<T>::numOfCompares;
	using ISort<T>::numOfSwaps;
	using ISort<T>::executionTime;

	QuickSort() {}

	virtual ~QuickSort() = default;

	virtual void Sort(vector<T>& arr) override final { // Разделение по схеме Lomuto
		int startTime = clock();

		quicksort(arr, 0, arr.size()-1);

		/*for (int i = 1; i < arr.size(); i++) {
			for (int j = i; j > 0; j--) {
				if (ISort<T>::isBigger(arr[j - 1], arr[j])) {
					ISort<T>::Swap(arr, j - 1, j);
				}
			}
		}*/

		int endTime = clock();
		executionTime = endTime - startTime;
	}
};
