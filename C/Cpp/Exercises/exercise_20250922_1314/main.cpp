/*
 * C/Cpp/Exercises/exercise_20250922_1314/main.cpp
 * KEYBRD Knights Coding Challenge
 * 
 * Author: SchponzeePlusPlus
 * 
 * SPP GitHub Link: https://github.com/SchponzeePlusPlus/spp_misc-code/tree/main/C/Cpp/Exercises/exercise_20250922_1314
 *
 */

// For console printing to work
#include <iostream>
#include <fstream>
// TODO: remove cmath eventually, use own functions instead
#include <cmath>

//	TODO: enforce casting to unsigned
#define KEYBRD_LAYOUT_ROW_CNT 4
#define KEYBRD_LAYOUT_COLUMN_CNT 5


#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH 10

const char CHARARR_KEYBRD_LAYOUT[KEYBRD_LAYOUT_ROW_CNT][KEYBRD_LAYOUT_COLUMN_CNT] =
{
	{'A', 'B', 'C', 'D', 'E'},
	{'F', 'G', 'H', 'I', 'J'},
	{'K', 'L', 'M', 'N', 'O'},
	{'\0', '1', '2', '3', '\0'},
};

// TODO: make power calculation formula
/* int calcIntPwrExponentOfBase(int base, int exponent)
{
	int result = 0;

	for (i = 2; i <= exponent; i++)
	{

	}

	return result;
} */

using namespace std;

int main()
{
	cout << "\n";
	cout << "\n";
	cout << "Program Initialised.\n";

	cout << "\n";
	cout << "Exercise\n";
	cout << "\n";

	int
		i = 0,
		j = 0,
		selctdKeybrdRowElem = 0,
		selctdKeybrdColumnElem = 0
	;

	/* // https://www.w3schools.com/cpp/ref_iostream_clog.asp
	// Set "info.log" as the output file for the log messages
	ofstream log("info.log");
	clog.rdbuf(log.rdbuf()); */
	
	//unsigned long int keyPressngCombinatnsTotalRaw = pow(((KEYBRD_LAYOUT_COLUMN_CNT * KEYBRD_LAYOUT_ROW_CNT) - 2), KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);
	unsigned long int keyPressngCombinatnsTotalRaw = pow(((KEYBRD_LAYOUT_COLUMN_CNT * KEYBRD_LAYOUT_ROW_CNT) - 0), KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);

	// Write to the log file
	//clog << "The number " << 1234 << " was given\n";

	cout << "Unfiltered Total Possible Combination of Key Presses: ";
	cout << keyPressngCombinatnsTotalRaw << "\n";
	cout << "\n";

	char* charArrOneDim_keyPressngCombinatnBuffer[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	// a very long list 1-D array of 10 element arrays 
	char* charArrTwoDim_keyPressngCombinatns[keyPressngCombinatnsTotalRaw][KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	...
	AAAA
	AAAB
	AAAC
	AAAD
	AAAE
	AAAF
	AAAH
	AAAI
	AAAJ
	AAAK
	AAAL
	AAAM
	AAAN
	AAAO
	AAA1
	AAA2
	AAA3
	AABA

	kind of like a base 17 numbering system

	i = 0;
	j = 0;

	// assign buffer null values
	for (j = 0; j < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		*charArrOneDim_keyPressngCombinatnBuffer[j] = CHARARR_KEYBRD_LAYOUT[0][0];
	}

	i = 0;
	j = 0;
	selctdKeybrdRowElem = 0;
	selctdKeybrdColumnElem = 0;
	
	while(i < keyPressngCombinatnsTotalRaw)
	{
		*charArrOneDim_keyPressngCombinatnBuffer[0] =
			CHARARR_KEYBRD_LAYOUT[selctdKeybrdRowElem][selctdKeybrdColumnElem];
		
		// save buffer to list
		for (j = 0; j < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
		{	
			charArrTwoDim_keyPressngCombinatns[i][j] =
				*charArrOneDim_keyPressngCombinatnBuffer[j];
		}

		if (selctdKeybrdRowElem < KEYBRD_LAYOUT_ROW_CNT) && (selctdKeybrdColumnElem < KEYBRD_LAYOUT_COLUMN_CNT)
		{
			selctdKeybrdRowElem++;
		}
		else if (selctdKeybrdRowElem >= KEYBRD_LAYOUT_ROW_CNT) && (selctdKeybrdColumnElem < KEYBRD_LAYOUT_COLUMN_CNT)
		{
			selctdKeybrdRowElem = 0;
			selctdKeybrdColumnElem++;
		}
		else if (selctdKeybrdRowElem >= KEYBRD_LAYOUT_ROW_CNT) && (selctdKeybrdColumnElem >= KEYBRD_LAYOUT_COLUMN_CNT)
		{
			selctdKeybrdRowElem = 0;
			selctdKeybrdColumnElem = 0;
			selctdKeybrdRowElem = 0;
			selctdKeybrdColumnElem++;....
		}

		i++;
	}
	

	for (selctdKeybrdRowElem = 0; selctdKeybrdRowElem < KEYBRD_LAYOUT_ROW_CNT; selctdKeybrdRowElem++)
	{
		for (selctdKeybrdColumnElem = 0; selctdKeybrdColumnElem < KEYBRD_LAYOUT_COLUMN_CNT; selctdKeybrdColumnElem++)
		{
					
		}
	}

	cout << "Program Complete.\n";
	cout << "\n";
	cout << "\n";

	/* // Close the file
	log.close(); */
	
	return 0;
}