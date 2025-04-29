/*
 * exercise_20250429_2037 / main.cpp
 * Simple Coding Test for Job Application Screening Process
 * 
 * SPP GitHub Link: https://github.com/SchponzeePlusPlus/spp_misc-code/tree/main/C/Exercises/exercise_20250429_2037
 * 
 * Many thanks for your application to our position of Senior Embedded Software Engineer.
 * 
 * As part of our screening process we would also like to gain a greater understanding of
 * your core abilities through a simple coding test.
 * These examples aim to satisfy us of your base competency level in embedded software development tasks.
 * Please provide a solution in single plain text file (with either .txt or .cpp extension) with the 2 requested functions included.
 * 
 * In providing your solution, assume you're writing code for the Linux kernel, so use only C, without any high-level functions or libraries.
 * Please do not try to google answers or revert to previous solutions or external sources for your response.
 * If you feel you cannot answer these questions reasonably quickly without external help, then our further testing processes throughout
 * the screening and interview stages will identify this very quickly, including whether there is consistency with how long your solutions
 * took to develop. Be honest.
 * 
 * Also, we don't require your solution to be syntactically perfect and won't try to compile it.
 * We just want to make sure you can develop the core algorithms required to solve these basic problems.
 *
 */

// For console printing to work
#include <iostream>

using namespace std;

// Exercise #1.

// In your text file write a function that reverses an array of ints:

void reverse(int* array, int numElements)
{
// your code here
	int* intArr_rvsBuffr = array;
	
	int i = 0;
	int j = numElements - 1;
	
	while((i < numElements + 1) && (j > -1))
	{
		array[j] = intArr_rvsBuffr[i];
		i++;
		j--;
	}
	
}

/*
 * Example input:
 * int a[6] = {3,6,8,1,4,6}
 * reverse(a, 6);
 */
// should result in {6,4,1,8,6,3}


// Exercise #2.

// Write a function that efficiently merges two already sorted arrays (allows duplicates) into a new sorted array

int* mergeSortedArray(int* array1, int numElements1, int* array2, int numElements2)
{
// your code here
	return 0;
}

/*
 * For example:
 * int a[4] = {1,4,6,8};
 * int b[6] = {3,5,5,6,9,10};
 * int* merged = mergeSortedArray(a, 4, b, 6);
 */
// merged should contain {1,3,4,5,5,6,6,8,9,10}

// Exercise Result:

int main()
{

	
	int exOneA[6] = {3,6,8,1,4,6};
	int exOneAPreReversed[6];
	for (int i = 0; i < 6 ; i++)
	{
		exOneAPreReversed[i] = exOneA[i];
	}
	reverse(exOneA, 6);

	int exTwoA[4] = {1,4,6,8};
	int exTwoB[6] = {3,5,5,6,9,10};
	//int* exTwoMerged = mergeSortedArray(exTwoA, 4, exTwoB, 6);

	cout << "\n";
	cout << "\n";
	cout << "Program Console Print Initialised.\n";
	cout << "\n";
	cout << "Exercise 01\n";

	cout << "Exercise 01 Pre-Reverse Array:\n";
	cout << "{";
	for (int i = 0; i < 6 ; i++)
	{
		cout << exOneAPreReversed[i];
		cout << ", ";
	}
	cout << "}";
	cout << "\n";
	cout << "\n";

	cout << "Exercise 01 Post-Reverse Array:\n";
	cout << "{";
	for (int i = 0; i < 6 ; i++)
	{
		cout << exOneA[i];
		cout << ", ";
	}
	cout << "}";
	cout << "\n";
	cout << "\n";

	cout << "Program Console Print Ending.\n";
	cout << "\n";
	cout << "\n";

	return 0;
}