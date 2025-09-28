/*
 * C/Cpp/Exercises/exercise_20250922_1314/main.cpp
 * Keyboard Knights Coding Challenge
 * 
 * Author: SchponzeePlusPlus
 * 
 * SPP GitHub Link: https://github.com/SchponzeePlusPlus/spp_misc-code/tree/main/C/Cpp/Exercises/exercise_20250922_1314
 *
 * Compilation Command (as per build.sh file in directory):
 * "
 * g++ -o ./build/Program_Main main.cpp -Wpedantic -std='c++23'
 * "
 * 
 * Note: DEVELOPED and COMPILED in a VM with DEBIAN (GNU / LINUX) (XFCE) 12 OS
 * 
 */

#include <stddef.h>
// For console printing to work
#include <iostream>
#include <fstream>
// TODO: remove cmath eventually, use own functions instead
#include <cmath>

//	TODO: enforce casting to unsigned
#define KEYBRD_LAYOUT_ROW_CNT ((uint8_t) 4U)
#define KEYBRD_LAYOUT_COLUMN_CNT ((uint8_t) 5U)

//#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((unsigned long long int) 10)
#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((uint8_t) 3U)
#define INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((int) KEY_PRESSNG_CORRECT_SEQUENC_LENGTH)

#define KNIGHT_MOVE_01_SHIFT_ELEMS ((uint8_t) 2U)
#define KNIGHT_MOVE_02_SHIFT_ELEMS ((uint8_t) 1U)

enum arrElemsOneDimSelctdShiftValidityState
{
	AEODSSVState_UNASSIGNED,
	AEODSSVState_ALLOWED,
	AEODSSVState_DISALLOWED_PRECEDNG_INIT_ELEM,
	AEODSSVState_DISALLOWED_PRECEDS_INIT_ELEM,
	AEODSSVState_DISALLOWED_SUCCEEDNG_FINAL_ELEM,
	AEODSSVState_DISALLOWED_SUCCEEDS_FINAL_ELEM,
	AEODSSVState_DISALLOWED_MISC
};

struct arrElemsTwoDim
{
	size_t elemDimOne;
	size_t elemDimTwo;
};

struct arrTwoDimLength
{
	size_t dimOneLength;
	size_t dimTwoLength;
};

struct arrTwoDimSelctdShiftValidityStates
{
	enum arrElemsOneDimSelctdShiftValidityState dimOneShiftAllowedState;
	enum arrElemsOneDimSelctdShiftValidityState dimTwoShiftAllowedState;
};

struct keyPressngCombinatnsTotalRawCalcElem
{
	struct arrElemsTwoDim keybrdLayoutPositn;
	bool ChkOvrflwIn;
	bool ChkOvrflwOut;
};

struct combinationCriteria
{
	struct arrElemsTwoDim arr_keybrdLayoutPositnSequence[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	bool validKeyCombinationPass;
	bool vowelCriteriaPass;
	bool validKnightMovesPass;
};

// I'm replacing '\0' with '0' and '4'
//	there aren't supposed to be anything in
//	those positions
const char CHARARR_KEYBRD_LAYOUT[KEYBRD_LAYOUT_ROW_CNT][KEYBRD_LAYOUT_COLUMN_CNT] =
{
	{'A', 'B', 'C', 'D', 'E'},
	{'F', 'G', 'H', 'I', 'J'},
	{'K', 'L', 'M', 'N', 'O'},
	{'0', '1', '2', '3', '4'},
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

struct arrElemsTwoDim returnArrElemsTwoDimFromElems(size_t elemDimOne, size_t elemDimTwo)
{
	struct arrElemsTwoDim result;
	result.elemDimOne = elemDimOne;
	result.elemDimTwo = elemDimTwo;
	return result;
}

bool chkCharIsVowel(char char_In)
{
	bool result = false;

	switch (char_In)
	{
		case 'A':
			result = true;
			break;
		case 'E':
			result = true;
			break;
		case 'I':
			result = true;
			break;
		case 'O':
			result = true;
			break;
		default:
			break;
	}

	return result;
}

bool chkKeySelctnValidty(char char_In)
{
	return
	(
		(
			((int) char_In >= (int) 'A') &&
				((int) char_In <= (int) 'O')
		)
		||
		(
			((int) char_In >= (int) '1') &&
				((int) char_In <= (int) '3')
		)
	);
}

enum arrElemsOneDimSelctdShiftValidityState chkShiftArrOneDimElemsSelectd(size_t u8_arrOneDimElemInPositn, size_t u8_arrOneDimLengthIn, int elemDimOneShift)
{
	enum arrElemsOneDimSelctdShiftValidityState result;

	result = AEODSSVState_UNASSIGNED;

	int int_proposdElemPositn = (u8_arrOneDimElemInPositn + elemDimOneShift);

	//cout << "Proposed element posiion: " << int_proposdElemPositn << "\n";

	if ((int_proposdElemPositn >= 0) && (int_proposdElemPositn < u8_arrOneDimLengthIn))
	{
		//cout << "allowed 123\n";
		result = AEODSSVState_ALLOWED;
		
	}
	else if ((int_proposdElemPositn == -1))
	{
		//cout << "disallowed 1\n";
		result = AEODSSVState_DISALLOWED_PRECEDNG_INIT_ELEM;
	}
	else if ((int_proposdElemPositn == (u8_arrOneDimLengthIn)))
	{
		//cout << "disallowed 2\n";
		result = AEODSSVState_DISALLOWED_SUCCEEDNG_FINAL_ELEM;
	}
	else
	{
		cout << "disallowed 3\n";
		result = AEODSSVState_DISALLOWED_MISC;
	}

	return result;
}

struct arrTwoDimSelctdShiftValidityStates chkShiftArrElemsTwoDimSelectd(struct arrElemsTwoDim strArrTwoDimElems_InPositn, struct arrTwoDimLength strArrTwoDimLength_In, int elemDimOneShift, int elemDimTwoShift)
{
	struct arrTwoDimSelctdShiftValidityStates result;

	result.dimOneShiftAllowedState = chkShiftArrOneDimElemsSelectd(strArrTwoDimElems_InPositn.elemDimOne, strArrTwoDimLength_In.dimOneLength, elemDimOneShift);
	
	result.dimTwoShiftAllowedState = chkShiftArrOneDimElemsSelectd(strArrTwoDimElems_InPositn.elemDimTwo, strArrTwoDimLength_In.dimTwoLength, elemDimTwoShift);

	return result;
}

char returnCharFromKeybrdLayout(struct arrElemsTwoDim keybrdPosition)
{
	return CHARARR_KEYBRD_LAYOUT[keybrdPosition.elemDimOne][keybrdPosition.elemDimTwo];
}

struct keyPressngCombinatnsTotalRawCalcElem shiftKeyPosition(struct keyPressngCombinatnsTotalRawCalcElem arrIn)
{
	struct keyPressngCombinatnsTotalRawCalcElem result;

	struct arrElemsTwoDim keybrdPositnTry;
	struct arrTwoDimLength keybrdLayoutLengths;
	struct arrTwoDimSelctdShiftValidityStates shiftValidityStates;

	result.keybrdLayoutPositn.elemDimOne = 0;
	result.keybrdLayoutPositn.elemDimTwo = 0;
	result.ChkOvrflwIn = false;
	result.ChkOvrflwOut = false;

	// the 1st dimension (array[1st][2nd]) is more easiliy intepreted as the 'row number' in C++
	keybrdLayoutLengths.dimOneLength = KEYBRD_LAYOUT_ROW_CNT;
	keybrdLayoutLengths.dimTwoLength = KEYBRD_LAYOUT_COLUMN_CNT;

	shiftValidityStates.dimOneShiftAllowedState = AEODSSVState_UNASSIGNED;
	shiftValidityStates.dimTwoShiftAllowedState = AEODSSVState_UNASSIGNED;

	if (arrIn.ChkOvrflwIn)
	{
		//cout << "Increment Digit Request: True\n";
		shiftValidityStates = chkShiftArrElemsTwoDimSelectd(arrIn.keybrdLayoutPositn, keybrdLayoutLengths, 0, 1);

		if (shiftValidityStates.dimTwoShiftAllowedState == AEODSSVState_ALLOWED)
		{
			// next character to the right
			//cout << "allowed shift right of keyboard\n";
			result.keybrdLayoutPositn.elemDimOne = (arrIn.keybrdLayoutPositn.elemDimOne + 0);
			result.keybrdLayoutPositn.elemDimTwo = (arrIn.keybrdLayoutPositn.elemDimTwo + 1);
			result.ChkOvrflwIn = false;
			result.ChkOvrflwOut = false;
			
		}
		else if
		(
			shiftValidityStates.dimTwoShiftAllowedState
				== AEODSSVState_DISALLOWED_SUCCEEDNG_FINAL_ELEM
		)
		{
			shiftValidityStates = chkShiftArrElemsTwoDimSelectd(arrIn.keybrdLayoutPositn, keybrdLayoutLengths, 1, 0);
			if (shiftValidityStates.dimOneShiftAllowedState == AEODSSVState_ALLOWED)
			{
				// first character next row down
				//cout << "allowed shift down keyboard\n";
				result.keybrdLayoutPositn.elemDimOne = (arrIn.keybrdLayoutPositn.elemDimOne + 1);
				result.keybrdLayoutPositn.elemDimTwo = 0;
				result.ChkOvrflwIn = false;
				result.ChkOvrflwOut = false;
			}
			else if (shiftValidityStates.dimOneShiftAllowedState == AEODSSVState_DISALLOWED_SUCCEEDNG_FINAL_ELEM)
			{
				// overflow increment to next key sequence
				//cout << "end of keyboard\n";
				result.keybrdLayoutPositn.elemDimOne = arrIn.keybrdLayoutPositn.elemDimOne;
				result.keybrdLayoutPositn.elemDimTwo = arrIn.keybrdLayoutPositn.elemDimTwo;
				result.ChkOvrflwIn = false;
				result.ChkOvrflwOut = true;
			}
			else
			{
				// error state
				cout << "error state!\n";
				result.keybrdLayoutPositn.elemDimOne = 0;
				result.keybrdLayoutPositn.elemDimTwo = 0;
				result.ChkOvrflwIn = false;
				result.ChkOvrflwOut = false;
			}
		}
	}
	else
	{
		// a skip state?
		//cout << "Overflow false\n";
		result.keybrdLayoutPositn.elemDimOne = arrIn.keybrdLayoutPositn.elemDimOne;
		result.keybrdLayoutPositn.elemDimTwo = arrIn.keybrdLayoutPositn.elemDimTwo;
		result.ChkOvrflwIn = false;
		result.ChkOvrflwOut = false;
	}
	
	return result;
}

struct keyPressngCombinatnsTotalRawCalcElem* incrementKeyCombinatn
(
	struct keyPressngCombinatnsTotalRawCalcElem* currentKeyCombinatn
)
{
	struct keyPressngCombinatnsTotalRawCalcElem* result
		= new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	bool chkIncrementOccurred = false;
	bool combinatnOvrflow = false;

	bool bo_chkDimOneNotSame = false;
	bool bo_chkDimTwoNotSame = false;
	bool bo_chkKeybrdPositnChngd = false;

	int keyPressngCombinatnElem = (INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1);

	// manual copy 
	for (int cntr_create = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); cntr_create >= 0; cntr_create--)
	{
		result[cntr_create].keybrdLayoutPositn.elemDimOne
			= currentKeyCombinatn[cntr_create].keybrdLayoutPositn.elemDimOne;
		result[cntr_create].keybrdLayoutPositn.elemDimTwo
			= currentKeyCombinatn[cntr_create].keybrdLayoutPositn.elemDimTwo;
		result[cntr_create].ChkOvrflwIn
			= currentKeyCombinatn[cntr_create].ChkOvrflwIn;
		result[cntr_create].ChkOvrflwOut
			= currentKeyCombinatn[cntr_create].ChkOvrflwOut;
	}

	/* cout << "Current Key Combination: ";

	for (j = 0; j < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		cout << CHARARR_KEYBRD_LAYOUT[currentKeyCombinatn[j].keybrdLayoutPositn.elemDimOne][currentKeyCombinatn[j].keybrdLayoutPositn.elemDimTwo];
	}
	cout << "\n"; */

	//cout << "incremet loop\n";
	result[keyPressngCombinatnElem].ChkOvrflwIn = true;

	do
	{
		//cout << "shift\n";
		//cout << "keyPressngCombinatnElem: " << keyPressngCombinatnElem << "\n";
		result[keyPressngCombinatnElem] = shiftKeyPosition(result[keyPressngCombinatnElem]);

		bo_chkDimOneNotSame = (result[keyPressngCombinatnElem].keybrdLayoutPositn.elemDimOne
			!= currentKeyCombinatn[keyPressngCombinatnElem].keybrdLayoutPositn.elemDimOne);

		bo_chkDimTwoNotSame = (result[keyPressngCombinatnElem].keybrdLayoutPositn.elemDimTwo != currentKeyCombinatn[keyPressngCombinatnElem].keybrdLayoutPositn.elemDimTwo);

		bo_chkKeybrdPositnChngd = (bo_chkDimOneNotSame || bo_chkDimTwoNotSame);

		if (bo_chkKeybrdPositnChngd)
		{
			//cout << "shift increment occurred successfully\n";
			result[keyPressngCombinatnElem].ChkOvrflwIn = false;
			chkIncrementOccurred = true;
		}
		else if (!bo_chkKeybrdPositnChngd && ((keyPressngCombinatnElem) > 0) && result[keyPressngCombinatnElem].ChkOvrflwOut)
		{
			//cout << "moving character\n";
			chkIncrementOccurred = false;
			result[keyPressngCombinatnElem].keybrdLayoutPositn.elemDimOne = 0;
			result[keyPressngCombinatnElem].keybrdLayoutPositn.elemDimTwo = 0;
			keyPressngCombinatnElem--;
			result[keyPressngCombinatnElem].ChkOvrflwIn = true;
			result[keyPressngCombinatnElem + 1].ChkOvrflwOut = false;
		}
		else if (!bo_chkKeybrdPositnChngd && ((keyPressngCombinatnElem) == 0) && result[keyPressngCombinatnElem].ChkOvrflwOut)
		{
			cout << "hit the end of the sequence\n";
			chkIncrementOccurred = false;
			combinatnOvrflow = true;
		}
		else
		{
			//cout << "something else\n";
		}
		for (int j = 0; j < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
		{
			//cout << CHARARR_KEYBRD_LAYOUT[result[j].keybrdLayoutPositn.elemDimOne][result[j].keybrdLayoutPositn.elemDimTwo];
		}
		//cout << "\n";
	}
	while (!chkIncrementOccurred && !combinatnOvrflow);

	//cout << "break\n";

	return result;
}

void printCombination(struct arrElemsTwoDim* strArrTwoDimElems_InPositn)
{
	cout << "Print Combination: ";
	for (int j = 0; j < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		cout << CHARARR_KEYBRD_LAYOUT[strArrTwoDimElems_InPositn[j].elemDimOne][strArrTwoDimElems_InPositn[j].elemDimTwo];
	}
	//cout << "\n";
}

void printCombinationCriteriaArr(struct combinationCriteria* arr_ComboCrit, int critListLength)
{
	cout << "Print Criteria List: \n";
	for (int i = 0; i < critListLength; i++)
	{
		printCombination(arr_ComboCrit[i].arr_keybrdLayoutPositnSequence);
		/* cout << "Print Combination: ";
		for (int j = 0; j < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
		{
			cout <<
				CHARARR_KEYBRD_LAYOUT
				[arr_ComboCrit[i].arr_keybrdLayoutPositnSequence[j].elemDimOne]
				[arr_ComboCrit[i].arr_keybrdLayoutPositnSequence[j].elemDimTwo];
		}
		cout << "\n"; */
		cout << "\t";
		cout << "Valid Characters: " << (int) (arr_ComboCrit[i].validKeyCombinationPass);
		cout << "\t";
		cout << "Vowel Pass: " << (int) (arr_ComboCrit[i].vowelCriteriaPass);
		cout << "\t";
		cout << "Knight Moves Pass: " << (int) (arr_ComboCrit[i].validKnightMovesPass);
		cout << "\n";
	}
	cout << "\n";
}

struct keyPressngCombinatnsTotalRawCalcElem* unassignKeyPressngCombinatnBuffer()
{
	struct keyPressngCombinatnsTotalRawCalcElem* result = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	for (int j = 0; j < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		result[j].keybrdLayoutPositn.elemDimOne = 0;
		result[j].keybrdLayoutPositn.elemDimTwo = 0;
		result[j].ChkOvrflwIn = false;
		result[j].ChkOvrflwOut = false;
	}
	return result;
	delete[] result;
}

int main()
{
	cout << "\n";
	cout << "\n";
	cout << "Program Initialised.\n";

	cout << "\n";
	cout << "Exercise\n";
	cout << "\n";

	uint64_t cntr_loopCombinationsList = 0;

	uint8_t u8_cntKeybrdCombinatnVowel = 0;
	uint8_t u8_cntKeybrdCombinatnKeySelctnValid = 0;
	uint8_t u8_cntKeybrdCombinatnKnightMoves = 0;

	uint8_t u8_chkKeybrdDigitColShft = 0;
	uint8_t u8_chkKeybrdDigitRowShft = 0;

	size_t keyPressngCorrectCombinatnLength = KEY_PRESSNG_CORRECT_SEQUENC_LENGTH;

	uint64_t u64_cntValidCombinations = 0;

	/* // https://www.w3schools.com/cpp/ref_iostream_clog.asp
	// Set "info.log" as the output file for the log messages
	ofstream log("info.log");
	clog.rdbuf(log.rdbuf()); */
	
	//unsigned long int keyPressngCombinatnsTotalRaw = pow(((KEYBRD_LAYOUT_COLUMN_CNT * KEYBRD_LAYOUT_ROW_CNT) - 2), KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);
	uint64_t keyPressngCombinatnsTotalRaw = pow(((KEYBRD_LAYOUT_COLUMN_CNT * KEYBRD_LAYOUT_ROW_CNT) - 0), INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);

	// Write to the log file
	//clog << "The number " << 1234 << " was given\n";

	cout << "Unfiltered Total Possible Combination of Key Presses: ";
	cout << keyPressngCombinatnsTotalRaw << "\n";
	cout << "\n";

	cout << "Declaring Buffer...\n";

	struct keyPressngCombinatnsTotalRawCalcElem* strArrOneDim_keyPressngCombinatnBuffer
		= new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	cout << "Declaring raw combinations list...\n";

	// a very long list 1-D array of 10 element arrays 
	struct arrElemsTwoDim**
		strArrTwoDim_keyPressngCombinatns = new struct arrElemsTwoDim*
			[keyPressngCombinatnsTotalRaw];

	cout << "made it here\n";
	
	for
	(
		uint64_t cntr_createCombinationsList = 0;
		cntr_createCombinationsList < keyPressngCombinatnsTotalRaw;
		cntr_createCombinationsList++
	)
	{
		// build rows
		strArrTwoDim_keyPressngCombinatns[cntr_createCombinationsList] = new arrElemsTwoDim[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	}

	// initialise buffer to "AAAAAAAAAA"
	cout << "(Un)assigning Buffer Values...\n";
	
	strArrOneDim_keyPressngCombinatnBuffer = unassignKeyPressngCombinatnBuffer();

	cout << "(Un)assigned Buffer Values.\n";

	cntr_loopCombinationsList = 0;
	while (cntr_loopCombinationsList < keyPressngCombinatnsTotalRaw)
	{
		for (int j = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); j >= 0; j--)
		{
			//cout << "val: " << strArrOneDim_keyPressngCombinatnBuffer[j].keybrdLayoutPositn.elemDimOne << "\n";

			strArrTwoDim_keyPressngCombinatns[cntr_loopCombinationsList][j].elemDimOne
				= strArrOneDim_keyPressngCombinatnBuffer[j].keybrdLayoutPositn.elemDimOne;

			//cout << "val2: " << strArrTwoDim_keyPressngCombinatns[cntr_loopCombinationsList][j].elemDimOne << "\n";
			
			strArrTwoDim_keyPressngCombinatns[cntr_loopCombinationsList][j].elemDimTwo
				= strArrOneDim_keyPressngCombinatnBuffer[j].keybrdLayoutPositn.elemDimTwo;
		}
		//printCombination(strArrTwoDim_keyPressngCombinatns[cntr_loopCombinationsList]);

		//cout << "Incrementing Combination...\n";
		strArrOneDim_keyPressngCombinatnBuffer = incrementKeyCombinatn(strArrOneDim_keyPressngCombinatnBuffer);
		cntr_loopCombinationsList++;
		//cout << "Incremented Combination, repeating loop...\n";
	}

	delete[] strArrOneDim_keyPressngCombinatnBuffer;

	struct combinationCriteria* arr_CombinatnCriteria
		= new struct combinationCriteria[keyPressngCombinatnsTotalRaw];

	for
	(
		int cntrCreateComboCrit = 0;
		cntrCreateComboCrit < keyPressngCombinatnsTotalRaw;
		cntrCreateComboCrit++
	)
	{
		for
		(
			int cntrCreateComboCritKeybrdDig = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); cntrCreateComboCritKeybrdDig >= 0;
			cntrCreateComboCritKeybrdDig--
		)
		{
			arr_CombinatnCriteria[cntrCreateComboCrit]
				.arr_keybrdLayoutPositnSequence[cntrCreateComboCritKeybrdDig].elemDimOne
				= strArrTwoDim_keyPressngCombinatns[cntrCreateComboCrit][cntrCreateComboCritKeybrdDig].elemDimOne;
			
			arr_CombinatnCriteria[cntrCreateComboCrit]
				.arr_keybrdLayoutPositnSequence[cntrCreateComboCritKeybrdDig].elemDimTwo
				= strArrTwoDim_keyPressngCombinatns[cntrCreateComboCrit][cntrCreateComboCritKeybrdDig].elemDimTwo;
		}
		for
		(
			int cntrCreateComboCritKnightMov = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 2); cntrCreateComboCritKnightMov >= 0;
			cntrCreateComboCritKnightMov--
		)
		{
			//
		}
		arr_CombinatnCriteria[cntrCreateComboCrit]
			.validKeyCombinationPass = false;
		arr_CombinatnCriteria[cntrCreateComboCrit].vowelCriteriaPass = false;
		arr_CombinatnCriteria[cntrCreateComboCrit].validKnightMovesPass = false;
	}

	delete[] strArrTwoDim_keyPressngCombinatns;

	u64_cntValidCombinations = 0;
	for
	(
		int cntrCheckEachComboCrit = 0;
		cntrCheckEachComboCrit < keyPressngCombinatnsTotalRaw;
		cntrCheckEachComboCrit++
	)
	{
		u8_cntKeybrdCombinatnKeySelctnValid = 0;
		u8_cntKeybrdCombinatnVowel = 0;
		u8_cntKeybrdCombinatnKnightMoves = 0;
		
		u8_chkKeybrdDigitColShft = 0;
		u8_chkKeybrdDigitRowShft = 0;
		for
		(
			int cntrChkComboCritKeybrdDig = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); cntrChkComboCritKeybrdDig >= 0;
			cntrChkComboCritKeybrdDig--
		)
		{
			if
			(
				chkKeySelctnValidty
				(
					returnCharFromKeybrdLayout
					(
						arr_CombinatnCriteria[cntrCheckEachComboCrit]
							.arr_keybrdLayoutPositnSequence[cntrChkComboCritKeybrdDig]
					)
				)
			)
			{
				u8_cntKeybrdCombinatnKeySelctnValid++;
			}
			if
			(
				chkCharIsVowel
				(
					returnCharFromKeybrdLayout
					(
						arr_CombinatnCriteria[cntrCheckEachComboCrit]
							.arr_keybrdLayoutPositnSequence[cntrChkComboCritKeybrdDig]
					)
				)
			)
			{
				u8_cntKeybrdCombinatnVowel++;
			}
		}
		for
		(
			int cntrChkComboCritKnightMov = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 2); cntrChkComboCritKnightMov >= 0;
			cntrChkComboCritKnightMov--
		)
		{
			u8_chkKeybrdDigitRowShft = 0;
			u8_chkKeybrdDigitColShft = 0;

			u8_chkKeybrdDigitRowShft
				= abs
				(
					(int) arr_CombinatnCriteria[cntrCheckEachComboCrit]
						.arr_keybrdLayoutPositnSequence[cntrChkComboCritKnightMov]
						.elemDimOne
					-
					(int) arr_CombinatnCriteria[cntrCheckEachComboCrit]
						.arr_keybrdLayoutPositnSequence[cntrChkComboCritKnightMov + 1]
						.elemDimOne
				);

			u8_chkKeybrdDigitColShft 
				= abs
				(
					(int) arr_CombinatnCriteria[cntrCheckEachComboCrit]
						.arr_keybrdLayoutPositnSequence[cntrChkComboCritKnightMov]
						.elemDimTwo
					-
					(int) arr_CombinatnCriteria[cntrCheckEachComboCrit]
						.arr_keybrdLayoutPositnSequence[cntrChkComboCritKnightMov + 1]
						.elemDimTwo
				);
			if
			(
				(
					(
						u8_chkKeybrdDigitRowShft == KNIGHT_MOVE_01_SHIFT_ELEMS
					)
					&&
					(
						u8_chkKeybrdDigitColShft == KNIGHT_MOVE_02_SHIFT_ELEMS
					)
				)
				^
				(
					(
						u8_chkKeybrdDigitRowShft == KNIGHT_MOVE_02_SHIFT_ELEMS
					)
					&&
					(
						u8_chkKeybrdDigitColShft == KNIGHT_MOVE_01_SHIFT_ELEMS
					)
				)
			)
			{
				u8_cntKeybrdCombinatnKnightMoves++;
			}
					
		}
		arr_CombinatnCriteria[cntrCheckEachComboCrit].validKeyCombinationPass
			= (u8_cntKeybrdCombinatnKeySelctnValid == KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);
		arr_CombinatnCriteria[cntrCheckEachComboCrit].vowelCriteriaPass
			= (u8_cntKeybrdCombinatnVowel <= 2);
		arr_CombinatnCriteria[cntrCheckEachComboCrit].validKnightMovesPass
			= (u8_cntKeybrdCombinatnKnightMoves == (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1));
		if
		(
			arr_CombinatnCriteria[cntrCheckEachComboCrit].validKeyCombinationPass &&
			arr_CombinatnCriteria[cntrCheckEachComboCrit].vowelCriteriaPass &&
			arr_CombinatnCriteria[cntrCheckEachComboCrit].validKnightMovesPass
		)
		{
			u64_cntValidCombinations++;
		}
		
	}

	printCombinationCriteriaArr(arr_CombinatnCriteria, keyPressngCombinatnsTotalRaw);

	cout << "Valid Combinations: " << u64_cntValidCombinations << "\n";

	delete[] arr_CombinatnCriteria;

	cout << "Program Complete.\n";
	cout << "\n";
	cout << "\n";

	/* // Close the file
	log.close(); */

	return 0;
}