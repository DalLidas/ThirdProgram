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

	virtual string Name() override final {
		return "BubbleSort";
	}

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

	virtual string Name() override final {
		return "SelectionSort";
	}

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

	virtual string Name() override final {
		return "InsertionSort";
	}

	virtual void Sort(vector<T>& arr) override final {
		int startTime = clock();

		for (auto i = 1; i < arr.size(); ++i){
			for (auto j = i; j > 0; --j) {
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

	virtual string Name() override final {
		return "ShellSort";
	}

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

				++numOfSwaps;

				// shift earlier gap-sorted elements up until the correct 
				// location for a[i] is found
				int j;
				for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
					arr[j] = arr[j - gap];

					++numOfCompares;
					++numOfSwaps;
				}
				//  put temp (the original a[i]) in its correct location
				arr[j] = temp;
				++numOfCompares;
			}

		}

		int endTime = clock();
		executionTime = endTime - startTime;
	}

};

template <typename T = int>
class QuickSort : public ISort<T> {
	// ��������� ������� ����������
	void quicksort(vector<T>& arr, int start, int end)
	{
		// ������� �������
		if (start >= end) {
			return;
		}

		// ����������� �������� �� ���
		int pivot = partition(arr, start, end);

		// ��������� ���������, ���������� ��������, ������� ������� �����
		quicksort(arr, start, pivot - 1);

		// ��������� ���������, ���������� ��������, ����������� ����� �����
		quicksort(arr, pivot + 1, end);
	}

	int partition(vector<T>& arr, int start, int end)
	{
		// �������� ������� ������ ������� � �������� �������� �������� �������
		T pivot = arr[end];

		++numOfCompares;

		// ��������, ������� ����� ��������, ����� ���������� ����� �� `pIndex`
		// �������� ������, ��� ����� ��������, ����� �������� ������ �� `pIndex`
		// ������ �������� ����� ���� � ����� �����������
		int pIndex = start;

		// ������ ���, ����� �� ������� �������, ������� ��� ������ ��������, `pIndex`
		// �������������, � ���� ������� ����� ������� ����� ������� ������.
		for (int i = start; i < end; i++)
		{
			if (arr[i] <= pivot)
			{
				swap(arr[i], arr[pIndex]);
				pIndex++;

				++numOfCompares;
				++numOfSwaps;
			}
		}

		// �������� ������� `pIndex` � �������
		swap(arr[pIndex], arr[end]);
		++numOfSwaps;

		// ������� `pIndex` (������ �������� ��������)
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

	virtual void Sort(vector<T>& arr) override final { // ���������� �� ����� Lomuto
		int startTime = clock();

		quicksort(arr, 0, arr.size() - 1);

		int endTime = clock();
		executionTime = endTime - startTime;
	}
};
