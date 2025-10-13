/*
 * C/Cpp/Exercises/exercise_xxx/main.cpp
 * Fibonacci
 * 
 * Author: SchponzeePlusPlus
 * 
 * Version: V0.0.0.0 (WIP)
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

int main()
{
	cout << "\n";
	cout << "\n";
	cout << "Program Initialised.\n";

	cout << "\n";
	cout << "Exercise\n";
	cout << "\n";
	
	// Set the number of calls = 0
	calls = 0;

	// Set the problem size
	int N = 40;

	// Use one of our implementations
	int result = calcFibonacciBaseline(N);
	// int result = callMemo(N);

	// Print the result
	cout << "Fibonacci of " << N << " is " << result << endl;
	cout << "Number of calls = " << calls << endl;

	cout << "Program Complete.\n";
	cout << "\n";
	cout << "\n";

	return 0;
}