/*
 * exercise_20250429_2037 / main.cpp
 * Simple Coding Test for Job Application Screening Process
 * 
 * Author: SchponzeePlusPlus
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
#include <cstdio>

// Exercise #1.

// In your text file write a function that reverses an array of ints:

void reverse(int* array, int numElements)
{
// your code here
	int intArr_rvsBuffr[numElements];
	for (int i = 0; i < numElements; i++)
	{
		intArr_rvsBuffr[i] = array[i];
	}
	
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
	int* result;
	//int buffrSmallrNum = 0;
	int buffrBiggrNum = 0;

	for (int i = 0; i < numElements1; i++)
	{
		result[i] = array1[i];
	}
	for (int i = 0; i < numElements2; i++)
	{
		result[i + numElements1] = array2[i];
	}

	for (int i = 0; i < (numElements1 + numElements2); i++)
	{
		for (int j = i + 1; j < (numElements1 + numElements2); j++)
		{
			if (result[i] > result[j])
			{
				//buffrSmallrNum = result[j];
				buffrBiggrNum = result[i];
				result[i] = result[j];
				result[j] = buffrBiggrNum;
				buffrBiggrNum = 0;
			}
		}
	}

	return result;
}

/*
 * For example:
 * int a[4] = {1,4,6,8};
 * int b[6] = {3,5,5,6,9,10};
 * int* merged = mergeSortedArray(a, 4, b, 6);
 */
// merged should contain {1,3,4,5,5,6,6,8,9,10}

// Exercise Result:

void calcExOne(int* arr, int numElements)
{
	printf("\n");
	printf("Exercise 01 Calculation Procedure:\n");
	printf("\n");

	int exOneAPreReversed[numElements];
	for (int i = 0; i < numElements; i++)
	{
		exOneAPreReversed[i] = arr[i];
	}

	reverse(arr, numElements);

	printf("Exercise 01 Pre-Reverse Array:\n");
	printf("{");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d", exOneAPreReversed[i]);
		printf(", ");
	}
	printf("}\n");
	printf("\n");

	printf("Exercise 01 Post-Reverse Array:\n");
	printf("{");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d", arr[i]);
		printf(", ");
	}
	printf("}\n");
	printf("\n");
}

int* calcExTwo(int* array1, int numElements1, int* array2, int numElements2)
{
	int* result;

	printf("\n");
	printf("Exercise 02 Calculation Procedure:\n");
	printf("\n");

	result = mergeSortedArray(array1, numElements1, array2, numElements2);

	printf("Exercise 02 Input Array 01:\n");
	printf("{");
	for (int i = 0; i < numElements1; i++)
	{
		printf("%d", array1[i]);
		printf(", ");
	}
	printf("}\n");
	printf("\n");

	printf("Exercise 02 Input Array 02:\n");
	printf("{");
	for (int i = 0; i < numElements2; i++)
	{
		printf("%d", array2[i]);
		printf(", ");
	}
	printf("}\n");
	printf("\n");

	printf("Exercise 02 Merged & Sorted Array:\n");
	printf("{");
	for (int i = 0; i < (numElements1 + numElements2); i++)
	{
		printf("%d", result[i]);
		printf(", ");
	}
	printf("}\n");
	printf("\n");

	return result;
}

int main()
{
	printf("\n");
	printf("\n");
	printf("Program Initialised.\n");

	printf("\n");
	printf("Exercise 01:\n");
	printf("\n");
	
	int exOneA[6] = {3,6,8,1,4,6};
	calcExOne(exOneA, 6);

	// extra test cases
	exOneA[0] = 1;
	exOneA[1] = 2;
	exOneA[2] = 3;
	exOneA[3] = 4;
	exOneA[4] = 5;
	exOneA[5] = 6;
	calcExOne(exOneA, 6);

	exOneA[0] = 5;
	exOneA[1] = 4;
	exOneA[2] = 3;
	exOneA[3] = 2;
	exOneA[4] = 1;
	exOneA[5] = 0;
	calcExOne(exOneA, 6);

	int exOneA_2[10] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
	calcExOne(exOneA_2, 10);

	printf("\n");
	printf("Exercise 02:\n");
	printf("\n");

	int exTwoA[4] = {1,4,6,8};
	int exTwoB[6] = {3,5,5,6,9,10};
	int* exTwoMerged = calcExTwo(exTwoA, 4, exTwoB, 6);

	exTwoA[0] = 5;
	exTwoA[1] = 4;
	exTwoA[2] = 3;
	exTwoA[3] = 2;

	exTwoB[0] = 5;
	exTwoB[1] = 4;
	exTwoB[2] = 3;
	exTwoB[3] = 2;
	exTwoB[4] = 1;
	exTwoB[5] = 0;

	exTwoMerged = calcExTwo(exTwoA, 4, exTwoB, 6);

	exTwoA[0] = 100;
	exTwoA[1] = 75;
	exTwoA[2] = 50;
	exTwoA[3] = 25;

	exTwoB[0] = 0;
	exTwoB[1] = 20;
	exTwoB[2] = 40;
	exTwoB[3] = 60;
	exTwoB[4] = 80;
	exTwoB[5] = 98;

	exTwoMerged = calcExTwo(exTwoA, 4, exTwoB, 6);

	int exTwoA_2[11] = {-100, -80, -60 , -40, -20, 0, 20, 40, 60, 80, 100};
	int exTwoB_2[10] = {-90, -70, -50, -30, -10, 10, 30, 50, 70, 90};
	exTwoMerged = calcExTwo(exTwoA_2, 11, exTwoB_2, 10);

	printf("Program Complete.\n");
	printf("\n");
	printf("\n");

	return 0;
}