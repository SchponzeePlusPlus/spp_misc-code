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
}

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
	for (int k = 0; k < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; k++)
	{ // easier to implement array loop here than it's own function for now
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
		cout << "Knight Moves (M01) Pass: " << (int) (arr_ComboCrit[i].validKnightMovesMove01Pass);
		cout << "\t";
		cout << "Knight Moves (M02) Pass: " << (int) (arr_ComboCrit[i].validKnightMovesMove02Pass);
		cout << "\n";
	}
	cout << "\n";
}

struct i8TwoVals calcStrCntKeyPressTransitndTwoDimShft(struct arrElemsTwoDim keyPressdArrayPositn, struct arrElemsTwoDim keyPressdPrevArrayPositn)
{
	struct i8TwoVals result = unassignStri8TwoVals();
	result.i8_valOne = ((int8_t) keyPressdArrayPositn.elemDimOne -
		(int8_t) keyPressdPrevArrayPositn.elemDimOne);
	result.i8_valTwo = ((int8_t) keyPressdArrayPositn.elemDimTwo -
		(int8_t) keyPressdPrevArrayPositn.elemDimTwo);
	return result;
}

bool chkKeyPressTransitndKnightMoveM02ShiftValid(int8_t i8_chkKeybrdDigitRowShft, int8_t i8_chkKeybrdDigitColShft)
{
	return
	(
		(
			(
				abs(i8_chkKeybrdDigitRowShft) == KNIGHT_MOVE_01_SHIFT_ELEMS
			)
			&&
			(
				abs(i8_chkKeybrdDigitColShft) == KNIGHT_MOVE_02_SHIFT_ELEMS
			)
		)
		^
		(
			(
				abs(i8_chkKeybrdDigitRowShft) == KNIGHT_MOVE_02_SHIFT_ELEMS
			)
			&&
			(
				abs(i8_chkKeybrdDigitColShft) == KNIGHT_MOVE_01_SHIFT_ELEMS
			)
		)
	);
}

enum dirTwoDimState getTransitningKnightMoveDirTwoDimStateFromShiftVals(int8_t i8_chkKeybrdDigitRowShft, int8_t i8_chkKeybrdDigitColShft)
{
	enum dirTwoDimState result = unassignEnumDirTwoDimState();
	if
	(
		(i8_chkKeybrdDigitRowShft == -(KNIGHT_MOVE_01_SHIFT_ELEMS))
		&&
		(abs(i8_chkKeybrdDigitColShft) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_UP;
	}
	else if
	(
		(i8_chkKeybrdDigitRowShft == (KNIGHT_MOVE_01_SHIFT_ELEMS))
		&&
		(abs(i8_chkKeybrdDigitColShft) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_DOWN;
	}
	else if
	(
		(abs(i8_chkKeybrdDigitRowShft) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		&&
		((i8_chkKeybrdDigitColShft) == -(KNIGHT_MOVE_01_SHIFT_ELEMS))
		
	)
	{
		result = DTDState_LEFT;
	}
	else if
	(
		(abs(i8_chkKeybrdDigitRowShft) == (KNIGHT_MOVE_02_SHIFT_ELEMS))
		&&
		((i8_chkKeybrdDigitColShft) == (KNIGHT_MOVE_01_SHIFT_ELEMS))
		
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
	uint64_t cntr_loopCombinationsList = 0;

	cout << "Declaring Buffer & (Un)assigning Buffer Values...\n";
	// initialise buffer to "AAAAAAAAAA"
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

	cntr_loopCombinationsList = 0;
	while (cntr_loopCombinationsList < keyPressngCombinatnsTotalRaw)
	{
		

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
		arr_CombinatnCriteria[cntrCreateComboCrit].validKnightMovesMove01Pass = false;
		arr_CombinatnCriteria[cntrCreateComboCrit].validKnightMovesMove02Pass = false;
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
		u8_cntKeybrdCombinatnKnightMovesM01 = 0;
		u8_cntKeybrdCombinatnKnightMovesM02 = 0;
		
		i8_chkKeybrdDigitColShft = 0;
		i8_chkKeybrdDigitRowShft = 0;
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
			i8_chkKeybrdDigitRowShft = 0;
			i8_chkKeybrdDigitColShft = 0;

			knightMove01DirState = DTDState_UNASSIGNED;

			
			calcStrCntKeyPressTransitndTwoDimShft()
			
			u8_cntKeybrdCombinatnKnightMovesM02 = conditionalIncrementU8Val(chkKeyPressTransitndKnightMoveM02ShiftValid())
			...calcKeyPressTransitningKnightMoveM01ArrayPositn()

			chkKeyPressTransitningKnightMoveM01ArrayPositnValid()

			conditionalIncrement()
			
		chkKeyPressCombinatnCriteriaPasses()
		
		incrementCntValidCombinations()
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