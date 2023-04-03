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

	void Swap(vector<T>& arr, int position) {
		
		swap(arr[position], arr[position+1]);

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
		cout << "Num of compares: " << numOfCompares << endl
			<< "Num of swaps: " << numOfSwaps << endl
			<< "Execution time: " << executionTime << endl;
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
		for (auto i = 0; i < arr.size() - 1; ++i) {
			for (auto j = 0; j < arr.size() - i - 1; ++j) {
				if (ISort<T>::isBigger(arr[j], arr[j + 1])) {
					ISort<T>::Swap(arr, j);
				}
			}
		}
	}

};