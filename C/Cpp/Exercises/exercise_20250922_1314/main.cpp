/*
 * C/Cpp/Exercises/exercise_20250922_1314/main.cpp
 * Keyboard Knights Coding Challenge
 * 
 * Author: SchponzeePlusPlus
 * 
 * Version: V0.0.0.1 (WIP)
 * 
 * Solution Attempt: No. 2
 * 
 * SPP GitHub Link: https://github.com/SchponzeePlusPlus/spp_misc-code/tree/main/C/Cpp/Exercises/exercise_20250922_1314
 *
 * Compilation Command (as per build.sh file in directory):
 * "
 * g++ -o ./build/Program_Main main.cpp -Wpedantic -std='c++23'
 * "
 * 
 * Note: DEVELOPED and COMPILED via Git Bash in a Windows 11 x64 Bare-Metal OS, 16 GB RAM, Intel i7-7700K CPU
 * 
 */

#include <stddef.h>
#include <cstdint>
// For console printing to work
#include <iostream>
#include <fstream>
// TODO: remove cmath eventually, use own functions instead
#include <cmath>

//	TODO: enforce casting to unsigned
#define KEYBRD_LAYOUT_ROW_CNT ((uint8_t) 4U)
#define KEYBRD_LAYOUT_COLUMN_CNT ((uint8_t) 5U)

//#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((unsigned long long int) 10)
#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((uint8_t) 10U)
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

enum dirTwoDimState
{
	DTDState_UNASSIGNED,
	DTDState_NULL,
	DTDState_ERROR,
	DTDState_UP,
	DTDState_DOWN,
	DTDState_LEFT,
	DTDState_RIGHT
};

struct arrElemsTwoDim
{
	uint8_t elemDimOne;
	uint8_t elemDimTwo;
};

struct arrTwoDimLength
{
	uint8_t dimOneLength;
	uint8_t dimTwoLength;
};

struct i8TwoVals
{
	int8_t i8_valOne;
	int8_t i8_valTwo;
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

struct keyPressdPositnCalcs
{
	struct arrElemsTwoDim keyPressdArrayPositn;
	bool bo_chkOvrflwIn;
	bool bo_chkOvrflwOut;
	bool bo_chkKeyPressdVowel;
	bool bo_chkKeyPressdValid;
	bool bo_chkKeyPressTransitndKnightMovesM01;
	bool bo_chkKeyPressTransitndKnightMovesM02;
	struct i8TwoVals str_cntKeyPressTransitndTwoDimShft;
	enum dirTwoDimState knightMove01DirState;
};

struct combinationCriteria
{
	struct arrElemsTwoDim arr_keybrdLayoutPositnSequence[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	bool validKeyCombinationPass;
	bool vowelCriteriaPass;
	bool validKnightMovesMove01Pass;
	bool validKnightMovesMove02Pass;
};

struct keyPressCombinatnCriteriaPassCnts
{	
	uint8_t u8_cntKeybrdCombinatnVowel;
	uint8_t u8_cntKeybrdCombinatnKeySelctnValid;
	uint8_t u8_cntKeybrdCombinatnKnightMovesM01;
	uint8_t u8_cntKeybrdCombinatnKnightMovesM02;
};

struct keyPressCombinatnCriteriaPasses
{
	bool validKeyCombinationPass;
	bool vowelCriteriaPass;
	bool validKnightMovesMove01Pass;
	bool validKnightMovesMove02Pass;
};

struct keyPressCombinatnBuffr
{
	struct keyPressdPositnCalcs strArr_keyPressdPositnCalc[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	struct keyPressCombinatnCriteriaPassCnts str_criteriaPassCnts;
	struct keyPressCombinatnCriteriaPasses str_criteriaPasses;
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

enum arrElemsOneDimSelctdShiftValidityState unassignEnumArrElemsOneDimSelctdShiftValidityState()
{
	return AEODSSVState_UNASSIGNED;
}

enum dirTwoDimState unassignEnumDirTwoDimState()
{
	return DTDState_UNASSIGNED;
}

struct arrElemsTwoDim unassignStrArrElemsTwoDim()
{
	struct arrElemsTwoDim result;
	result.elemDimOne = 0U;
	result.elemDimTwo = 0U;
	return result;
}

struct arrElemsTwoDim returnArrElemsTwoDimFromElems(uint8_t elemDimOne, uint8_t elemDimTwo)
{
	struct arrElemsTwoDim result;
	result.elemDimOne = elemDimOne;
	result.elemDimTwo = elemDimTwo;
	return result;
}

struct i8TwoVals unassignStri8TwoVals()
{
	struct i8TwoVals result;
	result.i8_valOne = 0;
	result.i8_valTwo = 0;
	return result;
}

struct keyPressngCombinatnsTotalRawCalcElem unassignKeyPressForIncrementCalc()
{
	struct keyPressngCombinatnsTotalRawCalcElem result;
	result.keybrdLayoutPositn = unassignStrArrElemsTwoDim();
	result.ChkOvrflwIn = false;
	result.ChkOvrflwOut = false;
	
	return result;
}

struct keyPressngCombinatnsTotalRawCalcElem* unassignKeyPressngCombinatnBuffer()
{
	struct keyPressngCombinatnsTotalRawCalcElem* result = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	for (int j = 0; j < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		result[j] = unassignKeyPressForIncrementCalc();
	}
	return result;
	delete[] result;
}

struct keyPressngCombinatnsTotalRawCalcElem copyKeyPressForIncrement(struct keyPressngCombinatnsTotalRawCalcElem currentKeyPress)
{
	struct keyPressngCombinatnsTotalRawCalcElem result = unassignKeyPressForIncrementCalc();
	result.keybrdLayoutPositn.elemDimOne = currentKeyPress.keybrdLayoutPositn.elemDimOne;
	result.keybrdLayoutPositn.elemDimTwo = currentKeyPress.keybrdLayoutPositn.elemDimTwo;
	result.ChkOvrflwIn = currentKeyPress.ChkOvrflwIn;
	result.ChkOvrflwOut = currentKeyPress.ChkOvrflwOut;
	return result;
}

struct keyPressngCombinatnsTotalRawCalcElem* copyKeyCombinatnForIncrement(struct keyPressngCombinatnsTotalRawCalcElem* currentKeyCombinatn)
{
	struct keyPressngCombinatnsTotalRawCalcElem* result = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	result = unassignKeyPressngCombinatnBuffer();
	// manual copy 
	for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
	{
		result[k] = copyKeyPressForIncrement(currentKeyCombinatn[k]);
	}
	return result;
	delete[] result;
}

struct keyPressdPositnCalcs unassignStrKeyPressdPositnCalcs()
{
	struct keyPressdPositnCalcs result;
	result.keyPressdArrayPositn = unassignStrArrElemsTwoDim();
	result.bo_chkOvrflwIn = false;
	result.bo_chkOvrflwOut = false;
	result.bo_chkKeyPressdVowel = false;
	result.bo_chkKeyPressdValid = false;
	result.bo_chkKeyPressTransitndKnightMovesM01 = false;
	result.bo_chkKeyPressTransitndKnightMovesM02 = false;
	result.str_cntKeyPressTransitndTwoDimShft = unassignStri8TwoVals();
	result.knightMove01DirState = unassignEnumDirTwoDimState();
	return result;
}

struct keyPressdPositnCalcs* unassignStrArrKeyPressdPositnCalcs()
{
	struct keyPressdPositnCalcs* result = new struct keyPressdPositnCalcs[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	for (int k = 0; k < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; k++)
	{
		result[k] = unassignStrKeyPressdPositnCalcs();
	}
	return result;
	delete[] result;
}

struct keyPressdPositnCalcs initNextStrKeyPressdPositnCalcs(struct keyPressdPositnCalcs inVal)
{
	struct keyPressdPositnCalcs result;
	result.keyPressdArrayPositn = inVal.keyPressdArrayPositn;
	result.bo_chkOvrflwIn = false;
	result.bo_chkOvrflwOut = false;
	result.bo_chkKeyPressdVowel = false;
	result.bo_chkKeyPressdValid = false;
	result.bo_chkKeyPressTransitndKnightMovesM01 = false;
	result.bo_chkKeyPressTransitndKnightMovesM02 = false;
	result.str_cntKeyPressTransitndTwoDimShft = unassignStri8TwoVals();
	result.knightMove01DirState = unassignEnumDirTwoDimState();
	return result;
}

struct keyPressCombinatnCriteriaPassCnts unassignStrKeyPressCombinatnCriteriaPassCnts()
{
	struct keyPressCombinatnCriteriaPassCnts result;
	result.u8_cntKeybrdCombinatnVowel = 0U;
	result.u8_cntKeybrdCombinatnKeySelctnValid = 0U;
	result.u8_cntKeybrdCombinatnKnightMovesM01 = 0U;
	result.u8_cntKeybrdCombinatnKnightMovesM02 = 0U;
	return result;
}

struct keyPressCombinatnCriteriaPasses unassignStrKeyPressCombinatnCriteriaPasses()
{
	struct keyPressCombinatnCriteriaPasses result;
	result.validKeyCombinationPass = false;
	result.vowelCriteriaPass = false;
	result.validKnightMovesMove01Pass = false;
	result.validKnightMovesMove02Pass = false;
	return result;
}

struct keyPressCombinatnBuffr unassignStrKeyPressCombinatnBuffr()
{
	struct keyPressCombinatnBuffr result;
	//result.strArr_keyPressdPositnCalc = unassignStrArrKeyPressdPositnCalcs();
	for (int k = 0; k < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; k++)
	{ //easier for now
		result.strArr_keyPressdPositnCalc[k] = unassignStrKeyPressdPositnCalcs();
	}
	result.str_criteriaPassCnts = unassignStrKeyPressCombinatnCriteriaPassCnts();
	result.str_criteriaPasses = unassignStrKeyPressCombinatnCriteriaPasses();
	return result;
}

uint8_t conditionalIncrementU8Val(bool bo_chkConditnTrue, uint8_t u8_cntr)
{
	uint8_t result = u8_cntr;
	if (bo_chkConditnTrue)
	{
		result++;
	}
	return result;
}

uint64_t conditionalIncrementU64Val(bool bo_chkConditnTrue, uint64_t u64_cntr)
{
	uint64_t result = u64_cntr;
	if (bo_chkConditnTrue)
	{
		result++;
	}
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

enum arrElemsOneDimSelctdShiftValidityState chkShiftArrOneDimElemsSelectd(uint8_t u8_arrOneDimElemInPositn, uint8_t u8_arrOneDimLengthIn, int elemDimOneShift)
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
	char result = '\0';

	if (((keybrdPosition.elemDimOne >= 0U) && (keybrdPosition.elemDimOne < KEYBRD_LAYOUT_ROW_CNT)) && ((keybrdPosition.elemDimTwo >= 0U) && (keybrdPosition.elemDimTwo < KEYBRD_LAYOUT_COLUMN_CNT)))
	{
		result = CHARARR_KEYBRD_LAYOUT[keybrdPosition.elemDimOne][keybrdPosition.elemDimTwo];
	}
	else
	{
		result = '!'; // not sure what else i could use to return an error
	}
	return result;
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

// more like increment key press array position ? no more like increment value in buffer ?
struct keyPressngCombinatnsTotalRawCalcElem* incrementKeyCombinatn
(
	struct keyPressngCombinatnsTotalRawCalcElem* currentKeyCombinatn
)
{
	struct keyPressngCombinatnsTotalRawCalcElem* result
		= new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	result = unassignKeyPressngCombinatnBuffer();
	bool chkIncrementOccurred = false;
	bool combinatnOvrflow = false;

	bool bo_chkDimOneNotSame = false;
	bool bo_chkDimTwoNotSame = false;
	bool bo_chkKeybrdPositnChngd = false;

	int keyPressngCombinatnElem = (INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1);

	for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
	{
		result[k] = copyKeyPressForIncrement(currentKeyCombinatn[k]);
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

	delete[] result;
}

/* void printKeyPressChar(struct arrElemsTwoDim strArrTwoDimElems_InPositn)
{
	cout << returnCharFromKeybrdLayout(strArrTwoDimElems_InPositn);
}

void printCombination(struct arrElemsTwoDim* strArrTwoDimElems_InPositn)
{
	cout << "Print Combination: ";
	for (int k = 0; k < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; k++)
	{
		printKeyPressChar(strArrTwoDimElems_InPositn[k]);
	}
	//cout << "\n";
}

void printCombinationCriteriaBuffr(struct keyPressCombinatnBuffr critBuffr)
{
	
	//printCombination(critBuffr.strArr_keyPressdPositnCalc);
	cout << "Print Combination: ";
	for (int k = 0; k < KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; k++)
	{
		printKeyPressChar(critBuffr.strArr_keyPressdPositnCalc[k].keyPressdArrayPositn);
	}
	cout << "\t";
	cout << "Valid Characters: " << (int) (critBuffr.str_criteriaPasses.validKeyCombinationPass);
	cout << "\t";
	cout << "Vowel Pass: " << (int) (critBuffr.str_criteriaPasses.vowelCriteriaPass);
	cout << "\t";
	cout << "Knight Moves (M01) Pass: " << (int) (critBuffr.str_criteriaPasses.validKnightMovesMove01Pass);
	cout << "\t";
	cout << "Knight Moves (M02) Pass: " << (int) (critBuffr.str_criteriaPasses.validKnightMovesMove02Pass);
	cout << "\n";
} */

struct i8TwoVals calcStrCntKeyPressTransitndTwoDimShft(struct arrElemsTwoDim keyPressdArrayPositn, struct arrElemsTwoDim keyPressdPrevArrayPositn)
{
	struct i8TwoVals result = unassignStri8TwoVals();
	result.i8_valOne = ((int8_t) keyPressdArrayPositn.elemDimOne -
		(int8_t) keyPressdPrevArrayPositn.elemDimOne);
	result.i8_valTwo = ((int8_t) keyPressdArrayPositn.elemDimTwo -
		(int8_t) keyPressdPrevArrayPositn.elemDimTwo);
	return result;
}

bool chkKeyPressTransitndKnightMoveM02ShiftValid(struct i8TwoVals str_cntKeyPressTransitndTwoDimShft)
{
	return
	(
		(
			(
				abs(str_cntKeyPressTransitndTwoDimShft.i8_valOne) == KNIGHT_MOVE_01_SHIFT_ELEMS
			)
			&&
			(
				abs(str_cntKeyPressTransitndTwoDimShft.i8_valTwo) == KNIGHT_MOVE_02_SHIFT_ELEMS
			)
		)
		^
		(
			(
				abs(str_cntKeyPressTransitndTwoDimShft.i8_valOne) == KNIGHT_MOVE_02_SHIFT_ELEMS
			)
			&&
			(
				abs(str_cntKeyPressTransitndTwoDimShft.i8_valTwo) == KNIGHT_MOVE_01_SHIFT_ELEMS
			)
		)
	);
}

enum dirTwoDimState getTransitningKnightMoveDirTwoDimStateFromShiftVals(struct i8TwoVals str_cntKeyPressTransitndTwoDimShft)
{
	enum dirTwoDimState result = unassignEnumDirTwoDimState();
	if
	(
		(str_cntKeyPressTransitndTwoDimShft.i8_valOne == -(KNIGHT_MOVE_01_SHIFT_ELEMS))
		&&
		(abs(str_cntKeyPressTransitndTwoDimShft.i8_valTwo) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_UP;
	}
	else if
	(
		(str_cntKeyPressTransitndTwoDimShft.i8_valOne == (KNIGHT_MOVE_01_SHIFT_ELEMS))
		&&
		(abs(str_cntKeyPressTransitndTwoDimShft.i8_valTwo) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_DOWN;
	}
	else if
	(
		(abs(str_cntKeyPressTransitndTwoDimShft.i8_valOne) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		&&
		((str_cntKeyPressTransitndTwoDimShft.i8_valTwo) == -(KNIGHT_MOVE_01_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_LEFT;
	}
	else if
	(
		(abs(str_cntKeyPressTransitndTwoDimShft.i8_valOne) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		&&
		((str_cntKeyPressTransitndTwoDimShft.i8_valTwo) == (KNIGHT_MOVE_01_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_RIGHT;
	}
	else
	{
		result = DTDState_ERROR;
	}
	return result;
}

struct arrElemsTwoDim calcKeyPressTransitningKnightMoveM01ArrayPositn(struct arrElemsTwoDim keyPressdPrevArrayPositn, enum dirTwoDimState knightMove01DirState)
{
	struct arrElemsTwoDim result = unassignStrArrElemsTwoDim();

	switch (knightMove01DirState)
	{
		case DTDState_UP:
			result.elemDimOne =
				((uint8_t) abs(((int) keyPressdPrevArrayPositn.elemDimOne) -
					((int) KNIGHT_MOVE_01_SHIFT_ELEMS)));
			result.elemDimTwo = ((uint8_t) (keyPressdPrevArrayPositn.elemDimTwo));
			break;
		case DTDState_DOWN:
			result.elemDimOne =
				((uint8_t) abs(((int) keyPressdPrevArrayPositn.elemDimOne) +
					((int) KNIGHT_MOVE_01_SHIFT_ELEMS)));
			result.elemDimTwo = ((uint8_t) (keyPressdPrevArrayPositn.elemDimTwo));
			break;
		case DTDState_LEFT:
			result.elemDimOne = ((uint8_t) (keyPressdPrevArrayPositn.elemDimOne));
			result.elemDimTwo =
				((uint8_t) abs(((int) keyPressdPrevArrayPositn.elemDimTwo) -
					((int) KNIGHT_MOVE_01_SHIFT_ELEMS)));
			break;
		case DTDState_RIGHT:
			result.elemDimOne = ((uint8_t) (keyPressdPrevArrayPositn.elemDimOne));
			result.elemDimTwo =
				((uint8_t) abs(((int) keyPressdPrevArrayPositn.elemDimTwo) +
					((int) KNIGHT_MOVE_01_SHIFT_ELEMS)));
			break;
		default:
			result.elemDimOne = ((uint8_t) 255U);
			result.elemDimTwo = ((uint8_t) 255U);
			break;
	}
	return result;
}

bool chkKeyPressTransitningKnightMoveM01ArrayPositnValid(struct arrElemsTwoDim keyPressTransitningKnightMoveM01ArrayPositn)
{
	return (chkKeySelctnValidty
		(returnCharFromKeybrdLayout(keyPressTransitningKnightMoveM01ArrayPositn)));
}

struct keyPressCombinatnCriteriaPasses chkKeyPressCombinatnCriteriaPasses(struct keyPressCombinatnCriteriaPassCnts str_passCnts)
{
	struct keyPressCombinatnCriteriaPasses result = unassignStrKeyPressCombinatnCriteriaPasses();

	result.validKeyCombinationPass
			= (str_passCnts.u8_cntKeybrdCombinatnKeySelctnValid == KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);
		result.vowelCriteriaPass
			= (str_passCnts.u8_cntKeybrdCombinatnVowel <= 2U);
		result.validKnightMovesMove01Pass
			= (str_passCnts.u8_cntKeybrdCombinatnKnightMovesM01 == (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1U));
		result.validKnightMovesMove02Pass
			= (str_passCnts.u8_cntKeybrdCombinatnKnightMovesM02 == (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1U));
	return result;
}

uint64_t incrementCntValidCombinations(struct keyPressCombinatnCriteriaPasses str_criteriaPasses, uint64_t u64_inVal)
{
	return conditionalIncrementU64Val
	(
		(
			str_criteriaPasses.validKeyCombinationPass &&
			str_criteriaPasses.vowelCriteriaPass &&
			str_criteriaPasses.validKnightMovesMove01Pass &&
			str_criteriaPasses.validKnightMovesMove02Pass
		),
		u64_inVal
	);
}

int main()
{
	cout << "\n";
	cout << "\n";
	cout << "Program Initialised.\n";

	cout << "\n";
	cout << "Exercise\n";
	cout << "\n";
	
	// attempt to use static? keep in data memory?
	uint64_t l = 0;

	cout << "Declaring Buffer & (Un)assigning Buffer Values...\n";
	// initialise buffer to "AAAAAAAAAA"

	struct arrElemsTwoDim keyPressdArrPositnCombinatnBuffr[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	struct keyPressngCombinatnsTotalRawCalcElem* strArrOneDim_keyPressngCombinatnBuffer
		= new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	struct keyPressCombinatnBuffr str_buffr = unassignStrKeyPressCombinatnBuffr();

	cout << "(Un)assigned Buffer Values.\n";

	//unsigned long int keyPressngCombinatnsTotalRaw = pow(((KEYBRD_LAYOUT_COLUMN_CNT * KEYBRD_LAYOUT_ROW_CNT) - 2), KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);
	uint64_t keyPressngCombinatnsTotalRaw = pow(((KEYBRD_LAYOUT_COLUMN_CNT * KEYBRD_LAYOUT_ROW_CNT) - 0), INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH);

	uint64_t u64_cntValidCombinations = 0;

	/* // https://www.w3schools.com/cpp/ref_iostream_clog.asp
	// Set "info.log" as the output file for the log messages
	ofstream log("info.log");
	clog.rdbuf(log.rdbuf()); */	

	// Write to the log file
	//clog << "The number " << 1234 << " was given\n";

	cout << "Unfiltered Total Possible Combination of Key Presses: ";
	cout << keyPressngCombinatnsTotalRaw << "\n";
	cout << "\n";

	cout << "made it here\n";

	for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
	{
		keyPressdArrPositnCombinatnBuffr[k] = unassignStrArrElemsTwoDim();
	}

	strArrOneDim_keyPressngCombinatnBuffer = unassignKeyPressngCombinatnBuffer();

	cout << "loop begin\n";
	l = 0;
	while (l < keyPressngCombinatnsTotalRaw)
	{
		cout << "l: " << l << "\n";
		str_buffr = unassignStrKeyPressCombinatnBuffr();
		strArrOneDim_keyPressngCombinatnBuffer = unassignKeyPressngCombinatnBuffer();
		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			str_buffr.strArr_keyPressdPositnCalc[k].keyPressdArrayPositn = keyPressdArrPositnCombinatnBuffr[k];
		}
		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressdValid =
				chkKeySelctnValidty(returnCharFromKeybrdLayout(str_buffr.strArr_keyPressdPositnCalc
					[k].keyPressdArrayPositn));
			str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressdVowel =
				chkCharIsVowel(returnCharFromKeybrdLayout(str_buffr.strArr_keyPressdPositnCalc
					[k].keyPressdArrayPositn));
		}
		for
		(int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 2); k >= 0; k--)
		{
			str_buffr.strArr_keyPressdPositnCalc[k].str_cntKeyPressTransitndTwoDimShft =
				calcStrCntKeyPressTransitndTwoDimShft(str_buffr.strArr_keyPressdPositnCalc[k].keyPressdArrayPositn, str_buffr.strArr_keyPressdPositnCalc[k + 1U].keyPressdArrayPositn);
			
			str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressTransitndKnightMovesM02 = chkKeyPressTransitndKnightMoveM02ShiftValid(str_buffr.strArr_keyPressdPositnCalc[k].str_cntKeyPressTransitndTwoDimShft);
			
			str_buffr.strArr_keyPressdPositnCalc[k].knightMove01DirState = getTransitningKnightMoveDirTwoDimStateFromShiftVals(str_buffr.strArr_keyPressdPositnCalc[k].str_cntKeyPressTransitndTwoDimShft);
			
			str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressTransitndKnightMovesM01 =
			chkKeyPressTransitningKnightMoveM01ArrayPositnValid(calcKeyPressTransitningKnightMoveM01ArrayPositn(str_buffr.strArr_keyPressdPositnCalc[k + 1].keyPressdArrayPositn, str_buffr.strArr_keyPressdPositnCalc[k].knightMove01DirState));
		}
		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnKeySelctnValid = conditionalIncrementU8Val(str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressdValid, str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnKeySelctnValid);

			str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnVowel = conditionalIncrementU8Val(str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressdVowel, str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnVowel);

			str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnKnightMovesM01 = conditionalIncrementU8Val(str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressTransitndKnightMovesM01, str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnKnightMovesM01);

			str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnKnightMovesM02 = conditionalIncrementU8Val(str_buffr.strArr_keyPressdPositnCalc[k].bo_chkKeyPressTransitndKnightMovesM02, str_buffr.str_criteriaPassCnts.u8_cntKeybrdCombinatnKnightMovesM02);
		}

		str_buffr.str_criteriaPasses = chkKeyPressCombinatnCriteriaPasses(str_buffr.str_criteriaPassCnts);

		u64_cntValidCombinations = incrementCntValidCombinations(str_buffr.str_criteriaPasses, u64_cntValidCombinations);

		//printCombinationCriteriaBuffr(str_buffr);

		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			strArrOneDim_keyPressngCombinatnBuffer[k].keybrdLayoutPositn = keyPressdArrPositnCombinatnBuffr[k];
			strArrOneDim_keyPressngCombinatnBuffer[k].ChkOvrflwIn = false;
			strArrOneDim_keyPressngCombinatnBuffer[k].ChkOvrflwOut = false;
		}
		
		//cout << "Incrementing Combination...\n";
		strArrOneDim_keyPressngCombinatnBuffer = incrementKeyCombinatn(strArrOneDim_keyPressngCombinatnBuffer);
		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			keyPressdArrPositnCombinatnBuffr[k] = strArrOneDim_keyPressngCombinatnBuffer[k].keybrdLayoutPositn;
		}
		l++;
		//cout << "Incremented Combination, repeating loop...\n";
	}

	cout << "Valid Combinations: " << u64_cntValidCombinations << "\n";

	delete[] strArrOneDim_keyPressngCombinatnBuffer;

	cout << "Program Complete.\n";
	cout << "\n";
	cout << "\n";

	/* // Close the file
	log.close(); */

	return 0;
}