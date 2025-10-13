/*
 * C/Cpp/Exercises/exercise_xxx/main.cpp
 * Fibonacci
 * 
 * Author: SchponzeePlusPlus
 * 
 * Version: V0.0.0.1 (WIP)
 * 
 * SPP GitHub Link: 
 * 
 */

#include <stddef.h>
#include <cstdint>
// For console printing to work
#include <iostream>
#include <fstream>
// TODO: remove cmath eventually, use own functions instead
#include <cmath>

using namespace std;

// Global for tracking calls
int calls;

// Baseline Fibonacci
// Basic repetitive and recursive Fibonacci function
int calcFibonacciBaseline(int N)
{
	// increment calls
	calls++;

	// base case for recursion
	if (N <= 1)
	{
		return N;
	}

	return calcFibonacciBaseline(N - 1) + calcFibonacciBaseline(N - 2);
}

// Fibonacci using memoization
// tmp is a little int array to store temporary results of Fibonacci
int calcFibonacciViaMemoization(int N, int *tmp)
{
	// increment calls
	calls++;

	// base case for recursion
	if (N <= 1)
	{
		return N;
	}

	// Use cached value instead of re-calculating
	// stops recursion when we've hit a value that some other call has already computed
	if (tmp[N] != 0)
	{
		return tmp[N];
	}

	// Store the value in our tmp array
	// if the value hasn't been computed already, so store it in the array
	tmp[N] = calcFibonacciViaMemoization(N - 1, tmp) + calcFibonacciViaMemoization(N - 2, tmp);
	// then return
	return tmp[N];
}

// Helper function to call the memoization function
// function not discussed in video
int callCalcFibonacciViaMemoization(int N)
{
  // Create an array for caching results
  // Use N + 1 to avoid 0 indexing

  // SPP note: array is assigned 0 for each element as a way of showing array elements haven't been assigned values yet

  int *tmp = new int[N + 1];
  for (int i = 0; i < N + 1; i++) {
    tmp[i] = 0;
  }

  // Call our better version
  int result = calcFibonacciViaMemoization(N, tmp);
  delete[] tmp;
  return result;
}

int main()
{
	cout << "\n";
	cout << "\n";
	cout << "Program Initialised.\n";

	cout << "\n";
	cout << "C++ Exercise: 2025/10/13 11:50: Fibonacci & Memoization\n";
	cout << "\n";
	
	// Set the number of calls = 0
	calls = 0;

	// Set the problem size
	int N = 40;

	// Use one of our implementations
	int result = calcFibonacciBaseline(N);

	// Print the result
	cout << "C++ Exercise: 2025/10/13 11:50: Fibonacci via Baseline Method (No Memoization, Pure Recursiveness and Repetition)\n";
	cout << "Fibonacci of " << N << " is " << result << endl;
	cout << "Number of calls = " << calls << endl;

	cout << "\n";

	// reset for next calculation method
	calls = 0;
	result = 0;

	// Memoization implemetation
	result = callCalcFibonacciViaMemoization(N);

	cout << "C++ Exercise: 2025/10/13 11:50: Fibonacci via Memoization Method (Less Recursiveness and Minimal Repetition)\n";
	cout << "Fibonacci of " << N << " is " << result << endl;
	cout << "Number of calls = " << calls << endl;

	cout << "Program Complete.\n";
	cout << "\n";
	cout << "\n";

	return 0;
}