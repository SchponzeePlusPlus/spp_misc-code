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
#include <array>
#include <vector>

//	TODO: enforce casting to unsigned
#define KEYBRD_LAYOUT_ROW_CNT ((uint8_t) 4U)
#define KEYBRD_LAYOUT_COLUMN_CNT ((uint8_t) 5U)

//#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((unsigned long long int) 10)
#define KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((uint8_t) 4U)
#define INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH ((int) KEY_PRESSNG_CORRECT_SEQUENC_LENGTH)

#define KNIGHT_MOVE_01_SHIFT_ELEMS ((uint8_t) 2U)
#define KNIGHT_MOVE_02_SHIFT_ELEMS ((uint8_t) 1U)

#define CHESS_MOVE_KNIGHT_POSITN_SHFT_POSSIBLTIES ((uint8_t) 8U)

// position in a 2-dim array(i,j), 2 dimensions
#define D_LEN ((uint8_t) 2U)
// e is element 
#define I_LEN KEYBRD_LAYOUT_ROW_CNT
#define J_LEN KEYBRD_LAYOUT_COLUMN_CNT
#define K_LEN KEY_PRESSNG_CORRECT_SEQUENC_LENGTH
// L is reserved for combination list, which doesn't have a constant value
// m: chess move for knight
#define M_LEN ((uint8_t) 2U)
// p for chess move possibilities of current position
#define P_LEN CHESS_MOVE_KNIGHT_POSITN_SHFT_POSSIBLTIES
#define T_LEN ((uint8_t) 2U) // transition betwen old position and new position


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

enum dirTwoDimState : int8_t
{
	DTDState_ERROR = -2,
	DTDState_NULL = -1,
	DTDState_UNASSIGNED = 0,
	DTDState_UP = 1,
	DTDState_DOWN = 2,
	DTDState_LEFT = 3,
	DTDState_RIGHT = 4
};

// first label direction is 2 position shift, second label direction is 1 position shift
enum chessMovKnightDirState : int8_t
{
	CMKDState_ERROR = -2,
	CMKDState_NULL = -1,
	CMKDState_UNASSIGNED = 0,
	CMKDState_UP_RGHT = 1,
	CMKDState_UP_LEFT = 2,
	CMKDState_DOWN_RGHT = 3,
	CMKDState_DOWN_LEFT = 4,
	CMKDState_LEFT_UP = 5,
	CMKDState_LEFT_DOWN = 6,
	CMKDState_RGHT_UP = 7,
	CMKDState_RGHT_DOWN = 8
};

// check whether transition is valid (physically possible, valid characters)
enum chessMovKnightTransitnValidtyState : int8_t
{
	CMKTVState_ERROR = -3,
	CMKTVState_NULL = -2,
	CMKTVState_INVALID = -1,
	CMKTVState_UNASSIGNED = 0,
	CMKTVState_VALID = 1,
};

enum keyPressComboCharProcState : int8_t
{
	EState_ERROR = -3,
	EState_NULL = -2,
	EState_CEASED = -1,
	EState_UNASSIGNED = 0,
	EState_VALID = 1,
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

struct u8ArrTwoDim
{
	uint8_t u8ArrTwoDim[2];
};

struct i8TwoVals
{
	int8_t i8_valOne;
	int8_t i8_valTwo;
};

struct i8ArrTwoDim
{
	uint8_t i8ArrTwoDim[2];
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

struct chessMoveKnightPositnNewPossiblty
{
	// old -> new position direction
	enum chessMovKnightDirState enmCMKDS_transitnDirState;
	std::array<enum dirTwoDimState, 2U> transitnmovsDirArr;
	enum chessMovKnightTransitnValidtyState enmCMKTVS_transitnValidtyState;
	std::array<uint8_t, 2> U8StdArr_positnNew;
};

struct keyPressComboBuffrElems
{
	uint8_t i;
	uint8_t j;
	uint8_t p;
	uint8_t k;
};

struct keyPressComboCharProc
{
	std::array<uint8_t, D_LEN> kPPositnArr;
	enum keyPressComboCharProcState kPPCCPState;
};

typedef std::array<uint8_t, D_LEN> U8ArrStdOf02;
typedef std::array<std::array<uint8_t, D_LEN>, K_LEN> U8ArrStdOf10Of02;
typedef std::array<std::array<uint8_t, D_LEN>, T_LEN> U8ArrStdOf02Of02;
typedef U8ArrStdOf02 kPPositnArr;
typedef std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN> PossibilitiesArr;
typedef U8ArrStdOf10Of02 KPComboArr;
typedef U8ArrStdOf02Of02 KPTransArr; //old position and new position

//typedef std::vector

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

const std::array<std::array<char, KEYBRD_LAYOUT_COLUMN_CNT>, KEYBRD_LAYOUT_ROW_CNT> STD_CHARARR_KEYBRD_LAYOUT 
{{
	{'A', 'B', 'C', 'D', 'E'},
	{'F', 'G', 'H', 'I', 'J'},
	{'K', 'L', 'M', 'N', 'O'},
	{'0', '1', '2', '3', '4'},
}};

const std::array<uint8_t, D_LEN>
	U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS 
{{
	KEYBRD_LAYOUT_ROW_CNT,
	KEYBRD_LAYOUT_COLUMN_CNT
}};

const std::array<uint8_t, M_LEN>
	U8_STD_ARR_ONE_DIM_CHESS_MOV_KNIGHT_SHIFTS 
{{
	KNIGHT_MOVE_01_SHIFT_ELEMS,
	KNIGHT_MOVE_02_SHIFT_ELEMS
}};

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

enum chessMovKnightDirState unassignEnumChessMovKnightDirState()
{
	return CMKDState_UNASSIGNED;
}

enum chessMovKnightTransitnValidtyState unassignEnumChessMovKnightTransitnValidtyState()
{
	return CMKTVState_UNASSIGNED;
}

std::array<enum dirTwoDimState, 2U> unassignArrStdTwoDimEnumDirTwoDimState()
{
	std::array<enum dirTwoDimState, 2U> result;
	for (uint8_t m = 0; m < M_LEN; m++)
	{
		result[m] = unassignEnumDirTwoDimState();
	}
	return result;
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

struct u8ArrTwoDim unassignStrU8ArrTwoDim()
{
	struct u8ArrTwoDim result;
	for (uint8_t e = 0U; e < 2; e++)
	{
		result.u8ArrTwoDim[e] = 0U;
	}
	return result;
}

std::array<uint8_t, 2> unassignU8ArrTwoDim()
{
	std::array<uint8_t,2> result;
	for (uint8_t e = 0U; e < 2; e++)
	{
		result[e] = 0U;
	}
	return result;
}

struct i8TwoVals unassignStri8TwoVals()
{
	struct i8TwoVals result;
	result.i8_valOne = 0;
	result.i8_valTwo = 0;
	return result;
}

struct i8ArrTwoDim unassignStrI8ArrTwoDim()
{
	struct i8ArrTwoDim result;
	for (uint8_t e = 0U; e < 2; e++)
	{
		result.i8ArrTwoDim[e] = 0;
	}
	return result;
}

std::array<int8_t, 2> unassignI8ArrOf02Elems()
{
	std::array<int8_t, 2> result;
	for (uint8_t e = 0U; e < 2; e++)
	{
		result[e] = 0;
	}
	return result;
}

std::array<std::array<int8_t, 2U>, 2U> unassignI8ArrOf02Of02Elems()
{
	std::array<std::array<int8_t, 2U>, 2U> result;
	for (uint8_t e = 0U; e < 2; e++)
	{
		result[e] = unassignI8ArrOf02Elems();
	}
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

//int (&foo( int (&a)[5] ))[5] { return a; }
//struct keyPressngCombinatnsTotalRawCalcElem* unassignKeyPressngCombinatnBuffer()
struct keyPressngCombinatnsTotalRawCalcElem (&unassignKeyPressngCombinatnBuffer(struct keyPressngCombinatnsTotalRawCalcElem (&result)[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]))[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]
{
	//struct keyPressngCombinatnsTotalRawCalcElem* result = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	//static struct keyPressngCombinatnsTotalRawCalcElem result[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	for (int j = 0; j < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		result[j] = unassignKeyPressForIncrementCalc();
	}
	return result;
	//delete[] result;
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

//int (&foo( int (&a)[5] ))[5] { return a; }
//struct keyPressngCombinatnsTotalRawCalcElem* copyKeyCombinatnForIncrement(struct keyPressngCombinatnsTotalRawCalcElem* currentKeyCombinatn)
struct keyPressngCombinatnsTotalRawCalcElem (&copyKeyCombinatnForIncrement(struct keyPressngCombinatnsTotalRawCalcElem (&result)[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH], struct keyPressngCombinatnsTotalRawCalcElem (&currentKeyCombinatn)[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]))[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]
{
	//struct keyPressngCombinatnsTotalRawCalcElem* result = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	//static struct keyPressngCombinatnsTotalRawCalcElem result[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	//result = unassignKeyPressngCombinatnBuffer();
	//unassignKeyPressngCombinatnBuffer() function content:
	for (int j = 0; j < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		result[j] = unassignKeyPressForIncrementCalc();
	}
	// manual copy 
	for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
	{
		result[k] = copyKeyPressForIncrement(currentKeyCombinatn[k]);
	}
	return result;
	//delete[] result;
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

//int (&foo( int (&a)[5] ))[5] { return a; }
//struct keyPressdPositnCalcs* unassignStrArrKeyPressdPositnCalcs()
struct keyPressdPositnCalcs (&unassignStrArrKeyPressdPositnCalcs(struct keyPressdPositnCalcs (&result)[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]))[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]
{
	//struct keyPressdPositnCalcs* result = new struct keyPressdPositnCalcs[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	//static struct keyPressdPositnCalcs result[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	for (int k = 0; k < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; k++)
	{
		result[k] = unassignStrKeyPressdPositnCalcs();
	}
	return result;
	//delete[] result;
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

struct chessMoveKnightPositnNewPossiblty unassignStrChessMoveKnightPositnNewPossiblty()
{
	struct chessMoveKnightPositnNewPossiblty result;
	result.enmCMKDS_transitnDirState = unassignEnumChessMovKnightDirState();
	result.transitnmovsDirArr = unassignArrStdTwoDimEnumDirTwoDimState();
	result.enmCMKTVS_transitnValidtyState = unassignEnumChessMovKnightTransitnValidtyState();
	result.U8StdArr_positnNew = unassignU8ArrTwoDim();
	return result;
}

KPComboArr unassignKPComboArr()
{
	KPComboArr result;
	for (uint8_t k = 0U; k < K_LEN; k++)
	{
		result[k] = unassignU8ArrTwoDim();
	}
	return result;
}

KPTransArr unassignKPTransArr()
{
	KPTransArr result;
	for (uint8_t t = 0U; t < T_LEN; t++)
	{
		result[t] = unassignU8ArrTwoDim();
	}
	return result;
}

uint8_t conditionalIncrementU8Val(bool bo_chkConditnTrue, uint8_t u8_cntr)
{
	return (bo_chkConditnTrue ? (u8_cntr + 1) : u8_cntr);
}

uint64_t conditionalIncrementU64Val(bool bo_chkConditnTrue, uint64_t u64_cntr)
{
	return (bo_chkConditnTrue ? (u64_cntr + 1) : u64_cntr);
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

// while 0 and 4 are not valid key presses, they are valid intermediate positions for knight moves (move 01 / 02), this is a quick fix to validate them
bool chkKeySelctnOnKeybrd(char char_In)
{
	return
	(
		(
			((int) char_In >= (int) 'A') &&
				((int) char_In <= (int) 'O')
		)
		||
		(
			((int) char_In >= (int) '0') &&
				((int) char_In <= (int) '4')
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

std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U> chkArrTwoDimDrrElemsOneDimSelctdShiftValidityState
(
	std::array<uint8_t, 2> u8StdArrOneDim_InArrPositn,
	std::array<uint8_t, 2> u8StdArrOneDim_InArrLengths,
	std::array<int8_t, 2> i8StdArrOneDim_positnChngs
)
{
	std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U> result;

	for (uint8_t d = 0; d < D_LEN; d++)
	{
		result[d] = chkShiftArrOneDimElemsSelectd(u8StdArrOneDim_InArrPositn[d], u8StdArrOneDim_InArrLengths[d], i8StdArrOneDim_positnChngs[d]);
	}
	return result;
}

std::array<std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U>, 2U> chkArrTwoDimDrrElemsOneDimSelctdShiftValidityStateMOVE
(
	std::array<uint8_t, 2> u8StdArrOneDim_InArrPositn,
	std::array<uint8_t, 2> u8StdArrOneDim_InArrLengths,
	std::array<std::array<int8_t, 2U>, 2U> shifts
)
{
	std::array<std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U>, 2U> result;

	for (uint8_t m = 0; m < M_LEN; m++)
	{
		result[m] = chkArrTwoDimDrrElemsOneDimSelctdShiftValidityState(u8StdArrOneDim_InArrPositn, u8StdArrOneDim_InArrLengths, shifts[m]);
	}
	return result;
}

bool chkMoveShiftOneDimTries
(
	const enum arrElemsOneDimSelctdShiftValidityState& oneDimShiftTry
)
{
	return (oneDimShiftTry == AEODSSVState_ALLOWED);
}

bool chkMoveShiftTwoDimTries
(
	const std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U>& moveShiftTries
)
{
	uint8_t chkTrueCntr = 0U;
	for (uint8_t d = 0; d < D_LEN; d++)
	{
		chkTrueCntr = ((chkMoveShiftOneDimTries(moveShiftTries[d])) ? chkTrueCntr + 1 : chkTrueCntr);
	}
	return (chkTrueCntr == D_LEN);
}

bool chkAllMoveShiftTries
(
	const std::array<std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U>, 2U>& allMovesShiftTries
)
{
	uint8_t chkTrueCntr = 0U;

	for (uint8_t m = 0; m < M_LEN; m++)
	{
		chkTrueCntr = ((chkMoveShiftTwoDimTries(allMovesShiftTries[m])) ? chkTrueCntr + 1 : chkTrueCntr);
	}
	return (chkTrueCntr == M_LEN);
}

std::array<enum dirTwoDimState, 2U> returnArrStdTwoDimEnumDirTwoDimStateFromChessMovKnightDir(enum chessMovKnightDirState enmCMKDS_transitnDirState)
{
	
	std::array<enum dirTwoDimState, 2U> result = unassignArrStdTwoDimEnumDirTwoDimState();

	switch (enmCMKDS_transitnDirState)
	{
		// up right
		case CMKDState_UP_RGHT:
			result[0] = DTDState_UP;
			result[1] = DTDState_RIGHT;
			break;
		// up left
		case CMKDState_UP_LEFT:
			result[0] = DTDState_UP;
			result[1] = DTDState_LEFT;
			break;
		// down right
		case CMKDState_DOWN_RGHT:
			result[0] = DTDState_DOWN;
			result[1] = DTDState_RIGHT;
			break;
		// down left
		case CMKDState_DOWN_LEFT:
			result[0] = DTDState_DOWN;
			result[1] = DTDState_LEFT;
			break;
		// left up
		case CMKDState_LEFT_UP:
			result[0] = DTDState_LEFT;
			result[1] = DTDState_UP;
			break;
		// left down
		case CMKDState_LEFT_DOWN:
			result[0] = DTDState_LEFT;
			result[1] = DTDState_DOWN;
			break;
		// right up
		case CMKDState_RGHT_UP:
			result[0] = DTDState_RIGHT;
			result[1] = DTDState_UP;
			break;
		// right down
		case CMKDState_RGHT_DOWN:
			result[0] = DTDState_RIGHT;
			result[1] = DTDState_DOWN;
			break;
		default:
			result[0] = DTDState_NULL;
			result[1] = DTDState_NULL;
			break;
	}

	return result;
}

int8_t returnChessMovKnightTransitnShiftOneDim(enum chessMovKnightDirState enmCMKDS_transitnDirState, uint8_t u8_dimSelect)
{
	int8_t result = 0;

	// up right
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_UP_RGHT)
	{
		result = (int8_t) (- KNIGHT_MOVE_01_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_UP_RGHT)
	{
		result = (int8_t) (KNIGHT_MOVE_02_SHIFT_ELEMS);
	}

	// up left
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_UP_LEFT)
	{
		result = (int8_t) (- KNIGHT_MOVE_01_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_UP_LEFT)
	{
		result = (int8_t) (- KNIGHT_MOVE_02_SHIFT_ELEMS);
	}

	// down right
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_DOWN_RGHT)
	{
		result = (int8_t) (KNIGHT_MOVE_01_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_DOWN_RGHT)
	{
		result = (int8_t) (KNIGHT_MOVE_02_SHIFT_ELEMS);
	}

	// down left
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_DOWN_LEFT)
	{
		result = (int8_t) (KNIGHT_MOVE_01_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_DOWN_LEFT)
	{
		result = (int8_t) (- KNIGHT_MOVE_02_SHIFT_ELEMS);
	}

	// left up
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_LEFT_UP)
	{
		result = (int8_t) (- KNIGHT_MOVE_02_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_LEFT_UP)
	{
		result = (int8_t) (- KNIGHT_MOVE_01_SHIFT_ELEMS);
	}

	// left down
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_LEFT_DOWN)
	{
		result = (int8_t) (KNIGHT_MOVE_02_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_LEFT_DOWN)
	{
		result = (int8_t) (- KNIGHT_MOVE_01_SHIFT_ELEMS);
	}

	// right up
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_RGHT_UP)
	{
		result = (int8_t) (- KNIGHT_MOVE_02_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_RGHT_UP)
	{
		result = (int8_t) (KNIGHT_MOVE_01_SHIFT_ELEMS);
	}

	// right down
	if (u8_dimSelect == 0U && enmCMKDS_transitnDirState == CMKDState_RGHT_DOWN)
	{
		result = (int8_t) (KNIGHT_MOVE_02_SHIFT_ELEMS);
	}
	else if (u8_dimSelect == 1U && enmCMKDS_transitnDirState == CMKDState_RGHT_DOWN)
	{
		result = (int8_t) (KNIGHT_MOVE_01_SHIFT_ELEMS);
	}

	else
	{
		result = 0;
	}

	return result;
}

uint8_t returnArrPositnDimFromDirTwoDimState(enum dirTwoDimState dir)
{
	uint8_t result = 0;

	if ((dir == DTDState_UP) || (dir == DTDState_DOWN))
	{
		result = 0;
	}
	else if ((dir == DTDState_LEFT) || (dir == DTDState_RIGHT))
	{
		result = 1;
	}

	return result;
}

int8_t returnArrTwoDimShftPolartyFromDirTwoDimState(enum dirTwoDimState dir)
{
	int8_t result = 0;

	if ((dir == DTDState_UP) || (dir == DTDState_LEFT))
	{
		result = -1;
	}
	else if ((dir == DTDState_DOWN) || (dir == DTDState_RIGHT))
	{
		result = 1;
	}

	return result;
}

uint8_t returnArrTwoDimShftMagnitudeFromKnightMove(uint8_t moveSelect)
{
	return U8_STD_ARR_ONE_DIM_CHESS_MOV_KNIGHT_SHIFTS[moveSelect];
}

int8_t returnChessMovKnightTransitnShiftOneDimV2(std::array<enum dirTwoDimState, 2U> movDirArr, uint8_t u8_movSelect)
{
	return (returnArrTwoDimShftPolartyFromDirTwoDimState(movDirArr[u8_movSelect]) * ((int8_t) returnArrTwoDimShftMagnitudeFromKnightMove(u8_movSelect)));
}

// this might be good to check move 01?
std::array<int8_t, 2> returnChessMovKnightTransitningShiftOneDim(std::array<enum dirTwoDimState, 2U> movDirArr, uint8_t u8_movSelect, uint8_t u8_dimSelect)
{
	std::array<int8_t, 2> result = unassignI8ArrOf02Elems();

	result[u8_dimSelect] = returnChessMovKnightTransitnShiftOneDimV2(movDirArr, u8_movSelect);

	return result;
}

std::array<int8_t, 2> returnChessMovKnightTransitnShiftV2(std::array<enum dirTwoDimState, 2U> movDirArr, uint8_t u8_movSelect)
{
	std::array<int8_t, 2> result = unassignI8ArrOf02Elems();

	uint8_t d = 0U;

	d = returnArrPositnDimFromDirTwoDimState(movDirArr[u8_movSelect]);
	result = returnChessMovKnightTransitningShiftOneDim(movDirArr, u8_movSelect, d);

	return result;
}

// this might be good to check move 1 and move 2?
std::array<std::array<int8_t, 2U>, 2U> returnChessMovKnightTransitnShift(std::array<enum dirTwoDimState, 2U> movDirArr)
{
	std::array<std::array<int8_t, 2U>, 2U> result = unassignI8ArrOf02Of02Elems();

	for (uint8_t m = 0; m < M_LEN; m++)
	{
		result[m] = returnChessMovKnightTransitnShiftV2(movDirArr, m);
	}

	return result;
}

// i suppose at this stage i've figured out / still figuring out how to produce shift arrays, how i am checking move 01 and move 02, and how i am storing them

enum chessMovKnightTransitnValidtyState chkChessMovKnightTransitnValidtyState(std::array<uint8_t, 2> U8StdArr_positnOld, std::array<enum dirTwoDimState, 2U> movDirArr)
{
	enum chessMovKnightTransitnValidtyState result = unassignEnumChessMovKnightTransitnValidtyState();

	std::array<std::array<int8_t, 2U>, 2U> shifts = returnChessMovKnightTransitnShift(movDirArr);

	std::array<std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U>, 2U> chkValidShifts = chkArrTwoDimDrrElemsOneDimSelctdShiftValidityStateMOVE(U8StdArr_positnOld, U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS, shifts);

	bool bo_chkAllMoveShiftTries = chkAllMoveShiftTries(chkValidShifts);

	// want to put case statement here but only boolean selection for now
	if (bo_chkAllMoveShiftTries)
	{
		result = CMKTVState_VALID;
	}
	else if (!bo_chkAllMoveShiftTries)
	{
		result = CMKTVState_INVALID;
	}
	else
	{
		result = CMKTVState_ERROR;
	}

	return result;
}

int8_t calcArrElemPositnNewTry(uint8_t oldPositn, int8_t shift)
{	return ((int8_t) abs(((int) oldPositn) + ((int) shift)));	}

uint8_t calcArrElemPositnNew(uint8_t oldPositn, uint8_t arrLength, int8_t shift)
{
	int8_t tryVal = calcArrElemPositnNewTry(oldPositn, shift);
	return (((tryVal >= 0U) && (tryVal < arrLength)) ? (uint8_t) tryVal : 0U);
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

char returnCharFromKeybrdLayoutStdArr(kPPositnArr keybrdPosition)
{
	char result = '\0';

	if (((keybrdPosition[0] >= 0U) && (keybrdPosition[0] < KEYBRD_LAYOUT_ROW_CNT)) && ((keybrdPosition[1] >= 0U) && (keybrdPosition[1] < KEYBRD_LAYOUT_COLUMN_CNT)))
	{
		result = STD_CHARARR_KEYBRD_LAYOUT[keybrdPosition[0]][keybrdPosition[1]];
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

//int (&foo( int (&a)[5] ))[5] { return a; }
// more like increment key press array position ? no more like increment value in buffer ?
//struct keyPressngCombinatnsTotalRawCalcElem* incrementKeyCombinatn(struct keyPressngCombinatnsTotalRawCalcElem* currentKeyCombinatn)
struct keyPressngCombinatnsTotalRawCalcElem (&incrementKeyCombinatn
(
	struct keyPressngCombinatnsTotalRawCalcElem (&result)[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH],
	struct keyPressngCombinatnsTotalRawCalcElem (&currentKeyCombinatn)[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]
))[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH]
{
	//struct keyPressngCombinatnsTotalRawCalcElem* result = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	//static struct keyPressngCombinatnsTotalRawCalcElem result[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	//result = unassignKeyPressngCombinatnBuffer();
	//unassignKeyPressngCombinatnBuffer() function content:
	for (int j = 0; j < INT_KEY_PRESSNG_CORRECT_SEQUENC_LENGTH; j++)
	{
		result[j] = unassignKeyPressForIncrementCalc();
	}
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

	//delete[] result;
}

void printKeyPressChar(struct arrElemsTwoDim strArrTwoDimElems_InPositn)
{
	cout << returnCharFromKeybrdLayout(strArrTwoDimElems_InPositn);
}

void printKeyPressCharFromStdArr(const std::array<uint8_t, D_LEN>& inPositn)
{
	cout << returnCharFromKeybrdLayoutStdArr(inPositn);
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

void printKPCombination(const KPComboArr& inKPComboArr)
{
	cout << "Print Combination: ";
	for (uint8_t k = 0U; k < K_LEN; k++)
	{
		printKeyPressCharFromStdArr(inKPComboArr[k]);
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

std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN> returnChessMoveKnightPositnNewPossibltiesArr(const std::array<uint8_t, 2> &keyPressdArrayPositn) //function with return type std::array
{
    std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN> result; //array declared

	for(uint8_t p = 0; p < P_LEN; p++)
	{
		result[p] = unassignStrChessMoveKnightPositnNewPossiblty();
	}

	std::array<std::array<int8_t, 2U>, 2U> shiftsTemp = unassignI8ArrOf02Of02Elems();

	char tempKey = '\0';

	bool tempKeyChkValid = false;

	//uint8_t tempKeyTransCntVowel = 0U;

	tempKey = returnCharFromKeybrdLayoutStdArr(keyPressdArrayPositn);
			
	tempKeyChkValid = chkKeySelctnValidty(tempKey);

	if (!tempKeyChkValid)
	{
		for(uint8_t p = 0; p < P_LEN; p++)
		{
			result[p].enmCMKTVS_transitnValidtyState = CMKTVState_INVALID;
		}
	}
	else
	{
		for(uint8_t p = 0; p < P_LEN; p++)
		{
			shiftsTemp = unassignI8ArrOf02Of02Elems();
			tempKey = '\0';

			result[p].enmCMKDS_transitnDirState = static_cast<chessMovKnightDirState>(p + 1);
			result[p].transitnmovsDirArr = returnArrStdTwoDimEnumDirTwoDimStateFromChessMovKnightDir(result[p].enmCMKDS_transitnDirState);
			result[p].enmCMKTVS_transitnValidtyState = chkChessMovKnightTransitnValidtyState(keyPressdArrayPositn, result[p].transitnmovsDirArr);
			if (result[p].enmCMKTVS_transitnValidtyState == CMKTVState_VALID)
			{
				shiftsTemp = returnChessMovKnightTransitnShift(result[p].transitnmovsDirArr);

				// shift move 1
				result[p].U8StdArr_positnNew[0] = calcArrElemPositnNew(keyPressdArrayPositn[0], U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS[0], shiftsTemp[0][0]);

				result[p].U8StdArr_positnNew[1] = calcArrElemPositnNew(keyPressdArrayPositn[1], U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS[1], shiftsTemp[0][1]);

				tempKey = returnCharFromKeybrdLayoutStdArr(result[p].U8StdArr_positnNew);
				
				//tempKeyChkValid = chkKeySelctnValidty(tempKey);
				// this is a quick fix to validate 0 and 4 intermediate positions, but in future, I will have to remove the complexity of checking two shifts and moves for each knight move
				tempKeyChkValid = chkKeySelctnOnKeybrd(tempKey);

				if (!tempKeyChkValid)
				{
					result[p].enmCMKTVS_transitnValidtyState = CMKTVState_INVALID;	
				}
				else
				{
					tempKey = '\0';

					// shift move 2
					result[p].U8StdArr_positnNew[0] = calcArrElemPositnNew(result[p].U8StdArr_positnNew[0], U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS[0], shiftsTemp[1][0]);

					result[p].U8StdArr_positnNew[1] = calcArrElemPositnNew(result[p].U8StdArr_positnNew[1], U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS[1], shiftsTemp[1][1]);

					tempKey = returnCharFromKeybrdLayoutStdArr(result[p].U8StdArr_positnNew);
				
					tempKeyChkValid = chkKeySelctnValidty(tempKey);
					if (!tempKeyChkValid)
					{
						result[p].enmCMKTVS_transitnValidtyState = CMKTVState_INVALID;	
					}
				}
			}
		}
	}

    return result;
}

std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN>
unassignAllChessMoveKnightPositnNewPossiblties()
{
	std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN> result;

	for (uint8_t i = 0; i < I_LEN; i++)
	{
		for (uint8_t j = 0; j < J_LEN; j++)
		{
			for (uint8_t p = 0; p < P_LEN; p++)
			{
				result[i][j][p] = unassignStrChessMoveKnightPositnNewPossiblty();
			}
		}
	}

	return result;
}

std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN>
generateAllChessMoveKnightPositnNewPossiblties()
{
	std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN> result = unassignAllChessMoveKnightPositnNewPossiblties();

	std::array<uint8_t, 2> keyPressArrayPositnCurr = unassignU8ArrTwoDim();

	for (uint8_t i = 0; i < I_LEN; i++)
	{
		for (uint8_t j = 0; j < J_LEN; j++)
		{
			keyPressArrayPositnCurr[0] = i;
			keyPressArrayPositnCurr[1] = j;
			result[i][j] = returnChessMoveKnightPositnNewPossibltiesArr(keyPressArrayPositnCurr);
		}
	}

	return result;
}

void runKeybrdKnightsBruteForce()
{
	cout << "\n";
	cout << "C++ Exercise: Keyboard Knights\n";
	cout << "\n";
	
	// attempt to use static? keep in data memory?
	uint64_t l = 0;

	cout << "Declaring Buffer & (Un)assigning Buffer Values...\n";
	// initialise buffer to "AAAAAAAAAA"

	struct arrElemsTwoDim keyPressdArrPositnCombinatnBuffr[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

	//struct keyPressngCombinatnsTotalRawCalcElem* strArrOneDim_keyPressngCombinatnBuffer = new struct keyPressngCombinatnsTotalRawCalcElem[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	struct keyPressngCombinatnsTotalRawCalcElem strArrOneDim_keyPressngCombinatnBuffer[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];
	struct keyPressngCombinatnsTotalRawCalcElem strArrOneDim_keyPressngCombinatnBufferOld[KEY_PRESSNG_CORRECT_SEQUENC_LENGTH];

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

	unassignKeyPressngCombinatnBuffer(strArrOneDim_keyPressngCombinatnBuffer);
	unassignKeyPressngCombinatnBuffer(strArrOneDim_keyPressngCombinatnBufferOld);

	//cout << "loop begin\n";
	l = 0;
	while (l < keyPressngCombinatnsTotalRaw)
	{
		//cout << "l: " << l << "\n";
		str_buffr = unassignStrKeyPressCombinatnBuffr();
		unassignKeyPressngCombinatnBuffer(strArrOneDim_keyPressngCombinatnBuffer);
		unassignKeyPressngCombinatnBuffer(strArrOneDim_keyPressngCombinatnBufferOld);
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

		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			strArrOneDim_keyPressngCombinatnBufferOld[k] = strArrOneDim_keyPressngCombinatnBuffer[k];
		}
		//cout << "Incrementing Combination...\n";
		incrementKeyCombinatn(strArrOneDim_keyPressngCombinatnBuffer, strArrOneDim_keyPressngCombinatnBufferOld);
		for (int k = (KEY_PRESSNG_CORRECT_SEQUENC_LENGTH - 1); k >= 0; k--)
		{
			keyPressdArrPositnCombinatnBuffr[k] = strArrOneDim_keyPressngCombinatnBuffer[k].keybrdLayoutPositn;
		}
		l++;
		//cout << "Incremented Combination, repeating loop...\n";
	}

	cout << "Valid Combinations: " << u64_cntValidCombinations << "\n";

	//delete[] strArrOneDim_keyPressngCombinatnBuffer;
}

KPTransArr calcKPTransArr(const KPTransArr& currKPTransArr)
{
	KPTransArr result;
	return result;
}

KPComboArr firstKPCombo(const KPComboArr& currKPComboArr, const PossibilitiesArr& possibilities)
{
	KPComboArr result = unassignKPComboArr();
	result = currKPComboArr;

	KPTransArr currKPTransArr = unassignKPTransArr();
	uint8_t currI = 0U;
	uint8_t currJ = 0U;
	uint8_t currP = 0U;
	bool chkPossibilityValid = false;

	if (result == unassignKPComboArr())
	{
		for (uint8_t k = 0U; k < (K_LEN - 1U); k++)
		{
			//cout << "k: " << ((int) k) << "\n";
			currI = result[k][0];
			currJ = result[k][1];
			currP = 0U;
			do
			{
				chkPossibilityValid = (possibilities[currI][currJ][currP].enmCMKTVS_transitnValidtyState == CMKTVState_VALID);
				if (chkPossibilityValid)
				{
					result[k + 1] = possibilities[currI][currJ][currP].U8StdArr_positnNew;
				}
				else
				{
					currP++;
				}
			}
			while (!chkPossibilityValid  && (currP < P_LEN));
		}
	}

	return result;
}

struct keyPressComboBuffrElems findNextKPCombo(const KPComboArr& currKPComboArr, const PossibilitiesArr& possibilities, struct keyPressComboBuffrElems currKPComboBuffrElems)
{
	struct keyPressComboBuffrElems result;
	result = currKPComboBuffrElems;

	KPTransArr currKPTransArr = unassignKPTransArr();
	
	kPPositnArr tempPositnArr = unassignU8ArrTwoDim();
	
	bool chkPossibilityValid = false;
	bool chkNextKey = false;
	bool comboIncremented = false;

	if (currKPComboArr != unassignKPComboArr())
	{
		//cout << "yesSir\n";
		do
		{
			//cout << "i: " << ((int) result.i) << "\n";
			do
			{
				//cout << "j: " << ((int) result.j) << "\n";
				do
				{
					//cout << "k: " << ((int) result.k) << "\n";
					//result.i = result[currK][0];
					//currJ = result[currK][1];
					//currP = 0U;
					do
					{
						//cout << "p: " << ((int) result.p) << "\n";
						//cout << "break here?" << "\n";
						if ((result.p < (P_LEN)) && !comboIncremented)
						{
							chkPossibilityValid = (possibilities[result.i][result.j][result.p].enmCMKTVS_transitnValidtyState == CMKTVState_VALID);
							//cout << "break there?" << "\n";
							if (chkPossibilityValid)
							{
								comboIncremented = true;
								//cout << "This possibility good!" << "\n";
							}
							else if (result.p < (P_LEN - 1U) && !chkPossibilityValid)
							{
								result.p++;
								//cout << "Next possibility" << "\n";
							}
						}
					}
					while ((result.p < P_LEN) && !comboIncremented);
					//cout << "herio" << "\n";
					if ((result.k > 0U)  && !comboIncremented)
					{
						//cout << "reduce key" << "\n";
						result.p = 0U;
						result.k--;
						result.j = currKPComboArr[result.k][1];
						result.i = currKPComboArr[result.k][0];
					}
				}
				while ((result.k >= 0U)  && !comboIncremented);
				if ((result.j < (J_LEN - 1U))  && !comboIncremented)
				{
					result.p = 0U;
					result.k = ((K_LEN - 1U) - 1U);
					result.j++;
					//result.i = currKPComboArr[result.k][0];
					if (chkKeySelctnValidty(returnCharFromKeybrdLayoutStdArr({result.i, result.j})))
					{
						comboIncremented = true;
					}
				}
			}
			while ((result.j < J_LEN)  && !comboIncremented);
			if ((result.i < (I_LEN - 1U))  && !comboIncremented)
			{
				result.p = 0U;
				result.k = ((K_LEN - 1U) - 1U);
				result.j = 0U;
				result.i++;
				if (chkKeySelctnValidty(returnCharFromKeybrdLayoutStdArr({result.i, result.j})))
				{
					comboIncremented = true;
				}
			}
		}
		while ((result.i < I_LEN)  && !comboIncremented);
	}

	cout << "i: " << ((int) result.i) << "\n";
	cout << "j: " << ((int) result.j) << "\n";
	cout << "k: " << ((int) result.k) << "\n";				
	cout << "p: " << ((int) result.p) << "\n";

	return result;
}

KPComboArr nextKPCombo2(const KPComboArr& currKPComboArr, const PossibilitiesArr& possibilities, struct keyPressComboBuffrElems currKPComboBuffrElems)
{
	KPComboArr result = unassignKPComboArr();
	result = currKPComboArr;

	KPTransArr currKPTransArr = unassignKPTransArr();
	
	
	bool chkPossibilityValid = false;
	bool chkNextKey = false;
	bool comboIncremented = false;

	if (result != unassignKPComboArr())
	{
		cout << "yes\n";
		do
		{
			do
			{
				do
				{
					//cout << "k: " << ((int) k) << "\n";
					//currI = result[currK][0];
					//currJ = result[currK][1];
					//currP = 0U;
					do
					{
						chkPossibilityValid = (possibilities[currKPComboBuffrElems.i][currKPComboBuffrElems.j][currKPComboBuffrElems.p].enmCMKTVS_transitnValidtyState == CMKTVState_VALID);
						if (chkPossibilityValid)
						{
							result[currKPComboBuffrElems.k + 1] = possibilities[currKPComboBuffrElems.i][currKPComboBuffrElems.j][currKPComboBuffrElems.p].U8StdArr_positnNew;
							comboIncremented = true;
						}
						else
						{
							currKPComboBuffrElems.p++;
						}
					}
					while (!chkPossibilityValid && (currKPComboBuffrElems.p < P_LEN) && !comboIncremented);
					if ((currKPComboBuffrElems.k < K_LEN)  && !comboIncremented)
					{
						currKPComboBuffrElems.k++;
					}
				}
				while ((currKPComboBuffrElems.k >= 0U)  && !comboIncremented);
				if ((currKPComboBuffrElems.j < J_LEN)  && !comboIncremented)
				{
					currKPComboBuffrElems.j++;
				}
			}
			while ((currKPComboBuffrElems.j < J_LEN)  && !comboIncremented);
			if ((currKPComboBuffrElems.i < I_LEN)  && !comboIncremented)
			{
				currKPComboBuffrElems.i++;
			}
		}
		while ((currKPComboBuffrElems.i < I_LEN)  && !comboIncremented);
	}

	return result;
}

KPComboArr nextKPCombo(const KPComboArr& currKPComboArr, const PossibilitiesArr& possibilities, uint8_t currK, uint8_t currP)
{
	KPComboArr result = unassignKPComboArr();
	result = currKPComboArr;

	KPTransArr currKPTransArr = unassignKPTransArr();
	uint8_t currI = 0U;
	uint8_t currJ = 0U;
	
	
	bool chkPossibilityValid = false;
	bool chkNextKey = false;
	bool comboIncremented = false;

	if (result != unassignKPComboArr())
	{
		cout << "yes\n";
		do
		{
			do
			{
				do
				{
					//cout << "k: " << ((int) k) << "\n";
					//currI = result[currK][0];
					//currJ = result[currK][1];
					//currP = 0U;
					do
					{
						chkPossibilityValid = (possibilities[currI][currJ][currP].enmCMKTVS_transitnValidtyState == CMKTVState_VALID);
						if (chkPossibilityValid)
						{
							result[currK + 1] = possibilities[currI][currJ][currP].U8StdArr_positnNew;
							comboIncremented = true;
						}
						else
						{
							currP++;
						}
					}
					while (!chkPossibilityValid && (currP < P_LEN) && !comboIncremented);
					if ((currK < K_LEN)  && !comboIncremented)
					{
						currK++;
					}
				}
				while ((currK >= 0U)  && !comboIncremented);
				if ((currJ < J_LEN)  && !comboIncremented)
				{
					currJ++;
				}
			}
			while ((currJ < J_LEN)  && !comboIncremented);
			if ((currI < I_LEN)  && !comboIncremented)
			{
				currI++;
			}
		}
		while ((currI < I_LEN)  && !comboIncremented);
	}

	return result;
}

void printPossibilities(const PossibilitiesArr& possibilitiesRaw)
{
	std::array<uint8_t, 2> tempKeyPressPositn = unassignU8ArrTwoDim();
	
	uint64_t u64_possibilityCnt = 0;

	cout << "Possibilities:\n";
	for (uint8_t i = 0; i < I_LEN; i++)
	{
		for (uint8_t j = 0; j < J_LEN; j++)
		{
			for (uint8_t p = 0; p < P_LEN; p++)
			{
				if (possibilitiesRaw[i][j][p].enmCMKTVS_transitnValidtyState == CMKTVState_VALID)
				{
					u64_possibilityCnt++;
					tempKeyPressPositn[0] = i;
					tempKeyPressPositn[1] = j;
					printKeyPressCharFromStdArr(tempKeyPressPositn);
					tempKeyPressPositn[0] = possibilitiesRaw[i][j][p].U8StdArr_positnNew[0];
					tempKeyPressPositn[1] = possibilitiesRaw[i][j][p].U8StdArr_positnNew[1];
					printKeyPressCharFromStdArr(tempKeyPressPositn);
					cout << "\n";
				}
			}
		}
	}
	cout << "\n";
	cout << "Possibility Count: " << u64_possibilityCnt << "\n";

	uint64_t quickGuesskeyPressngCombinatnsTotal = pow(u64_possibilityCnt, K_LEN);

	cout << "Quick Guess at Combination Possibility Count: " << quickGuesskeyPressngCombinatnsTotal << "\n";
}

void resizePossibilitiesVector(std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>>& possibilities)
{
	possibilities.resize(I_LEN);

	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		possibilities[i].resize(J_LEN);
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			possibilities[i][j].resize(P_LEN);
		}
	}
}

void unassignPossibilitiesVector(std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>>& possibilities)
{
	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			for (uint8_t p = 0U; p < P_LEN; p++)
			{
				for (uint8_t d = 0U; d < D_LEN; d++)
				{
					possibilities[i][j][p][d] = 0U;
				}
			}
		}
	}
}

void copyFiltrdPossibilitiesVector(std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>>& possibilities, const PossibilitiesArr& possibilitiesRaw)
{
	uint8_t pVctr = 0U;

	cout << "vector copy from array\n";
	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			pVctr = 0U;
			for (uint8_t p = 0U; p < P_LEN; p++)
			{
				if (possibilitiesRaw[i][j][p].enmCMKTVS_transitnValidtyState == CMKTVState_VALID)
				{
					//cout << "copy operation\n";
					possibilities[i][j][pVctr] = possibilitiesRaw[i][j][p].U8StdArr_positnNew;
					pVctr++;
				}
				else
				{
					//cout << "erase operation\n";
					possibilities[i][j].erase (possibilities[i][j].begin() + pVctr);
				}
			}
		}
	}
}

void unassignCombo(std::array<struct keyPressComboCharProc, K_LEN>& unassignedCombo)
{
	for (uint8_t k = 0U; k < K_LEN; k++)
	{
		for (uint8_t d = 0U; d < D_LEN; d++)
		{
			unassignedCombo[k].kPPositnArr[d] = 0U;
		}
		unassignedCombo[k].kPPCCPState = EState_UNASSIGNED;
	}
}

void printPossibilitiesVector(const std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>>& possibilities)
{
	cout << "vector print\n";
	for (uint8_t i = 0U; i < possibilities.size(); i++)
	{
		for (uint8_t j = 0U; j < possibilities[i].size(); j++)
		{
			for (uint8_t p = 0U; p < possibilities[i][j].size(); p++)
			{
				printKeyPressCharFromStdArr({i, j});
				printKeyPressCharFromStdArr(possibilities[i][j][p]);
				cout << "\n";
			}
		}
	}
}

void printComboListVctrLDim(const std::vector<std::array<struct keyPressComboCharProc, K_LEN>>& listVctrLDim)
{
	for (uint8_t l = 0U; l < listVctrLDim.size(); l++)
	{
		for (uint8_t k = 0U; k < K_LEN; k++)
		{
			//printKeyPressCharFromStdArr({i, j});
			printKeyPressCharFromStdArr(listVctrLDim[l][k].kPPositnArr);
		}
		cout << "\n";
	}
}

void resizeListVctrLDim(std::vector<std::array<struct keyPressComboCharProc, K_LEN>>& listVctrLDim, const std::array<std::array<uint64_t, J_LEN>, I_LEN>& listPossibilityCntArr2KPs, const uint8_t& k)
{
	std::array<struct keyPressComboCharProc, K_LEN> unassignedCombo;

	unassignCombo(unassignedCombo);

	uint8_t l = 0U;
	uint8_t tempCntr = 0U;
	//uint8_t lTempCntr = 0U;
	auto lPos = listVctrLDim.begin();
	//bool bo_lNoEnd = false;
	std::size_t oldLSz = listVctrLDim.size();
	std::array<struct keyPressComboCharProc, K_LEN> tempCombo = unassignedCombo;
	for (uint8_t lOld = 0U; lOld < (uint8_t) oldLSz; lOld++)
	{
		//l += lOld;

		//cout << "lOld: " << (int) lOld << "\n";
		//cout << "l: " << (int) l << "\n";
		
		//l = 
		//list[i][j].push_back(unassignedCombo);
		tempCombo = listVctrLDim[l];
		/* for (uint8_t k = 0U; k < K_LEN; k++)
		{
			//printKeyPressCharFromStdArr({i, j});
			printKeyPressCharFromStdArr(tempCombo[k].kPPositnArr);
		}
		cout << "\n";*/
		tempCntr = (listPossibilityCntArr2KPs[listVctrLDim[l][k - 1U].kPPositnArr[0]][listVctrLDim[l][k - 1U].kPPositnArr[1]] - 1U);
		//cout << "Temp Counter: " << (int) tempCntr << "\n";
		
		

		//list[i][j][l][1]
		//tempCntr = listPossibilityCntArr2KPs[list[i][j][l][1].kPPositnArr[0]][list[i][j][l][1].kPPositnArr[1]];

		//l += tempCntr + lOld;
		//lPos = std::next(list[i][j].begin(), l);

		l += tempCntr;
		//cout << "l: " << (int) l << "\n";

		//cout << "Insert New Elements...\n";

		listVctrLDim.insert(lPos, (tempCntr), tempCombo);

		//cout << "Next position...\n";

		
		//l += tempCntr + lOld;
		// increment 1 as lOld increments
		l++;
		lPos = std::next(listVctrLDim.begin(), l);
	}
}

void runKeybrdKnightsTopDown()
{
	cout << "\n";
	cout << "C++ Exercise: Keyboard Knights\n";
	cout << "\n";

	std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN> possibilitiesRaw = generateAllChessMoveKnightPositnNewPossiblties();

	// std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, P_LEN>, J_LEN>, I_LEN> possibilities; vector maybe too hard to implement?	

	uint8_t currK = 0U;
	uint8_t currP = 0U;

	struct keyPressComboBuffrElems currKPComboBuffrElems;

	currKPComboBuffrElems.i = 0U;
	currKPComboBuffrElems.j = 0U;
	currKPComboBuffrElems.p = 0U;
	currKPComboBuffrElems.k = 0U;

	printPossibilities(possibilitiesRaw);

	/* KPComboArr kPComboArr_buffr = unassignKPComboArr();

	cout << "Combo Buffer: ";
	for (uint8_t k = 0; k < K_LEN; k++)
	{
		printKeyPressCharFromStdArr(kPComboArr_buffr[k]);
	}
	cout << "\n";

	kPComboArr_buffr = firstKPCombo(kPComboArr_buffr, possibilitiesRaw);

	cout << "Combo Buffer: ";
	for (uint8_t k = 0; k < K_LEN; k++)
	{
		printKeyPressCharFromStdArr(kPComboArr_buffr[k]);
	}
	cout << "\n";

	currK = 0U;
	//currK = ((K_LEN - 1U) - 1U);
	currP++;

	currKPComboBuffrElems.p++;
	currKPComboBuffrElems.k = ((K_LEN - 1U) - 1U);
	currKPComboBuffrElems.j = kPComboArr_buffr[currKPComboBuffrElems.k][1];
	currKPComboBuffrElems.i = kPComboArr_buffr[currKPComboBuffrElems.k][0];

	kPComboArr_buffr = nextKPCombo(kPComboArr_buffr, possibilitiesRaw, currK, currP);

	cout << "Combo Buffer: ";
	for (uint8_t k = 0; k < K_LEN; k++)
	{
		printKeyPressCharFromStdArr(kPComboArr_buffr[k]);
	}
	cout << "\n";

	cout << "Current P: " << (int) currKPComboBuffrElems.p << "\n";

	currKPComboBuffrElems = findNextKPCombo(kPComboArr_buffr, possibilitiesRaw, currKPComboBuffrElems);

	kPComboArr_buffr[currKPComboBuffrElems.k + 1] = possibilitiesRaw[currKPComboBuffrElems.i][currKPComboBuffrElems.j][currKPComboBuffrElems.p].U8StdArr_positnNew;

	cout << "Current P: " << (int) currKPComboBuffrElems.p << "\n";

	printKeyPressCharFromStdArr(possibilitiesRaw[currKPComboBuffrElems.i][currKPComboBuffrElems.j][currKPComboBuffrElems.p].U8StdArr_positnNew);
	cout << "\n";

	for (uint8_t k = 0; k < K_LEN; k++)
	{
		printKeyPressCharFromStdArr(kPComboArr_buffr[k]);
	}

	do
	{
		do
		{
			do
			{
				while (currKPComboBuffrElems.p < (P_LEN))
				{
					currKPComboBuffrElems = findNextKPCombo(kPComboArr_buffr, possibilitiesRaw, currKPComboBuffrElems);

					kPComboArr_buffr[currKPComboBuffrElems.k + 1] = possibilitiesRaw[currKPComboBuffrElems.i][currKPComboBuffrElems.j][currKPComboBuffrElems.p].U8StdArr_positnNew;

					//cout << "Current P: " << (int) currKPComboBuffrElems.p << "\n";

					//printKeyPressCharFromStdArr(possibilitiesRaw[currKPComboBuffrElems.i][currKPComboBuffrElems.j][currKPComboBuffrElems.p].U8StdArr_positnNew);
					//cout << "\n";

					printKPCombination(kPComboArr_buffr);
					cout << "\n";
					currKPComboBuffrElems.p++;
					
				}
				cout << "get here?\n";
				currKPComboBuffrElems.p = 0U;
				kPComboArr_buffr = nextKPCombo2(kPComboArr_buffr, possibilitiesRaw, currKPComboBuffrElems);
			}
			while(currKPComboBuffrElems.k >= 0U);
		}
		while(currKPComboBuffrElems.j < (J_LEN - 1U));
	}
	while(currKPComboBuffrElems.i < (I_LEN - 1U)); */

	std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>> possibilities;

	resizePossibilitiesVector(possibilities);
	
	unassignPossibilitiesVector(possibilities);

	copyFiltrdPossibilitiesVector(possibilities, possibilitiesRaw);

	printPossibilitiesVector(possibilities);

	cout << "list vector\n";
	
	std::vector<std::vector<std::vector<std::array<struct keyPressComboCharProc, K_LEN>>>> list;

	//cout << "resize list vector i\n";

	list.resize(I_LEN);

	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		//cout << "resize list vector j\n";
		list[i].resize(J_LEN);
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			//cout << "size: " << possibilities[i][j].size() << "\n";
			list[i][j].resize(possibilities[i][j].size());
		}
	}

	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			for (uint8_t l = 0U; l < list[i][j].size(); l++)
			{
				for (uint8_t k = 0U; k < K_LEN; k++)
				{
					for (uint8_t d = 0U; d < D_LEN; d++)
					{
						list[i][j][l][k].kPPositnArr[d] = 0U;
					}
					list[i][j][l][k].kPPCCPState = EState_UNASSIGNED;
				}
			}
		}
	}

	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			for (uint8_t l = 0U; l < list[i][j].size(); l++)
			{
				for (uint8_t k = 0U; k < 1U; k++)
				{
					list[i][j][l][k].kPPositnArr = {i, j};
				}
				for (uint8_t k = 1U; k < 2U; k++)
				{
					list[i][j][l][k].kPPositnArr = possibilities[i][j][l];
					list[i][j][l][k].kPPCCPState = EState_VALID;
				}
			}
		}
	}

	cout << "list vector print\n";
	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			for (uint8_t l = 0U; l < list[i][j].size(); l++)
			{
				for (uint8_t k = 0U; k < K_LEN; k++)
				{
					//printKeyPressCharFromStdArr({i, j});
					printKeyPressCharFromStdArr(list[i][j][l][k].kPPositnArr);
				}
				cout << "\n";
			}
		}
	}

	std:array<std::array<uint64_t, J_LEN>, I_LEN> listPossibilityCntArr;

	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			listPossibilityCntArr[i][j] = list[i][j].size();
		}
	}

	std::array<std::array<uint64_t, J_LEN>, I_LEN> listPossibilityCntArr2KPs = listPossibilityCntArr;

	cout << "list possibility counts per key\n";
	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			printKeyPressCharFromStdArr({i, j});
			cout << ": " << listPossibilityCntArr[i][j] << "\n";
		}
	}

	std::array<uint8_t, D_LEN> tempPos = {0U, 0U};

	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			for (uint8_t l = 0U; l < list[i][j].size(); l++)
			{
				// key press of last checked, how many possibilities? lookup value and return count
				//listPossibilityCntArr[i][j] += 
				//list[i][j][l][1].kPPositnArr == tempPos;
				listPossibilityCntArr[i][j] += (listPossibilityCntArr2KPs[list[i][j][l][1].kPPositnArr[0]][list[i][j][l][1].kPPositnArr[1]] - 1U);
			}
		}
	}

	cout << "list possibility counts per key\n";
	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			printKeyPressCharFromStdArr({i, j});
			cout << ": " << listPossibilityCntArr[i][j] << "\n";
		}
	}

	std::array<struct keyPressComboCharProc, K_LEN> unassignedCombo;

	unassignCombo(unassignedCombo);

	cout << "HERE\n";

	
	/* // resize list for next key using push back
	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		//cout << "i: " << (int) i << "\n";
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			//cout << "j: " << (int) j << "\n";
			std::size_t oldLSz = list[i][j].size();
			for (uint8_t l = ((uint8_t) oldLSz); l < (uint8_t) (listPossibilityCntArr[i][j]); l++)
			{
				list[i][j].push_back(unassignedCombo);
				//list[i][j][l][1]
				//tempCntr = listPossibilityCntArr2KPs[list[i][j][l][1].kPPositnArr[0]][list[i][j][l][1].kPPositnArr[1]];
			}
		}
	} */
	

	/*
	std::array<struct keyPressComboCharProc, K_LEN> tempMovComboA;
	std::array<struct keyPressComboCharProc, K_LEN> tempMovComboB;

	// re sort pushed back vector...
	for (uint8_t i = 0U; i < I_LEN; i++)
	{
		//cout << "i: " << (int) i << "\n";
		for (uint8_t j = 0U; j < J_LEN; j++)
		{
			//cout << "j: " << (int) j << "\n";
			
			for (uint8_t l = ((uint8_t) oldLSz); l < list[i][j].size()); l++)
			{
				list[i][j].push_back(unassignedCombo);
				//list[i][j][l][1]
				//tempCntr = listPossibilityCntArr2KPs[list[i][j][l][1].kPPositnArr[0]][list[i][j][l][1].kPPositnArr[1]];
			}
		}
	}

	*/

	
	for (uint8_t k = 2U; k < K_LEN; k++)
	{
		// resize vector 

		for (uint8_t i = 0U; i < I_LEN; i++)
		{
			cout << "i: " << (int) i << "\n";
			for (uint8_t j = 0U; j < J_LEN; j++)
			{
				cout << "j: " << (int) j << "\n";
				resizeListVctrLDim(list[i][j], listPossibilityCntArr2KPs, k);
			}
		}

		cout << "list vector print\n";
		for (uint8_t i = 0U; i < list.size(); i++)
		{
			for (uint8_t j = 0U; j < list[i].size(); j++)
			{
				printComboListVctrLDim(list[i][j]);
			}
		}

		// the next step is to fill 3rd character, using the possibilities vector to lookup k and fill the transitions for k + 1, the vector has already been resized to accomodate
		// the fill or assign or populate or generate or whatever procedure might be similar to the resize in the way that that the resize l dim looks up the count and resizes accordingly

		// fill next key press (3rd key for now); k = 2
		cout << "fill stage\n";
		for (uint8_t i = 0U; i < I_LEN; i++)
		{
			cout << "i: " << (int) i << "\n";
			for (uint8_t j = 0U; j < J_LEN; j++)
			{
				uint8_t possibilitiesIIndx = 0U;
				uint8_t possibilitiesJIndx = 0U;
				cout << "possibilitiesIIndx: " << (int) possibilitiesIIndx << "\n";
				cout << "possibilitiesJIndx: " << (int) possibilitiesJIndx << "\n";
				uint8_t possibilitiesPIndx = 0U;
				uint8_t possibilitiesIIndxPrev = 0U;
				uint8_t possibilitiesJIndxPrev = 0U;
				// if the L Dim is not empty
				if (list[i][j].size() > 0U)
				{
					possibilitiesIIndx = list[i][j][0][k - 1U].kPPositnArr[0];
					possibilitiesJIndx = list[i][j][0][k - 1U].kPPositnArr[1];
					possibilitiesIIndxPrev = possibilitiesIIndx;
					possibilitiesJIndxPrev = possibilitiesJIndx;
				}
				cout << "j: " << (int) j << "\n";
				for (uint8_t l = 0U; l < list[i][j].size(); l++)
				{
					cout << "l: " << (int) l << "\n";
					//possibilities[i][j];

					possibilitiesIIndxPrev = possibilitiesIIndx;
					possibilitiesJIndxPrev = possibilitiesJIndx;
					
					possibilitiesIIndx = list[i][j][l][k - 1U].kPPositnArr[0];
					possibilitiesJIndx = list[i][j][l][k - 1U].kPPositnArr[1];

					if (possibilitiesIIndx == possibilitiesIIndxPrev && possibilitiesJIndx == possibilitiesJIndxPrev && possibilitiesPIndx < possibilities[possibilitiesIIndx][possibilitiesJIndx].size())
					{
						// already incremented below
						cout << "condition 1st check true no action\n";
					}
					else
					{
						possibilitiesPIndx = 0U;
						possibilitiesIIndxPrev = possibilitiesIIndx;
						possibilitiesJIndxPrev = possibilitiesJIndx;
						cout << "condition 1st check false, reset P Index\n";
					}

					cout << "possibilitiesIIndx: " << (int) possibilitiesIIndx << "\n";
					cout << "possibilitiesJIndx: " << (int) possibilitiesJIndx << "\n";
					cout << "possibilitiesPIndx: " << (int) possibilitiesPIndx << "\n";

					cout << "Possibility: ";
					printKeyPressCharFromStdArr({possibilitiesIIndx, possibilitiesJIndx});
					printKeyPressCharFromStdArr(possibilities[possibilitiesIIndx][possibilitiesJIndx][possibilitiesPIndx]);
					cout << "\n";

					list[i][j][l][k].kPPositnArr = possibilities[possibilitiesIIndx][possibilitiesJIndx][possibilitiesPIndx];
					//l += lOld;

					//cout << "lOld: " << (int) lOld << "\n";
					
					
					//l = 
					//list[i][j].push_back(unassignedCombo);
					//tempCombo = listVctrLDim[l];
					/* for (uint8_t k = 0U; k < K_LEN; k++)
					{
						//printKeyPressCharFromStdArr({i, j});
						printKeyPressCharFromStdArr(tempCombo[k].kPPositnArr);
					}
					cout << "\n";*/
					//tempCntr = (listPossibilityCntArr2KPs[listVctrLDim[l][1].kPPositnArr[0]][listVctrLDim[l][1].kPPositnArr[1]] - 1U);
					//cout << "Temp Counter: " << (int) tempCntr << "\n";
					
					

					//list[i][j][l][1]
					//tempCntr = listPossibilityCntArr2KPs[list[i][j][l][1].kPPositnArr[0]][list[i][j][l][1].kPPositnArr[1]];

					//l += tempCntr + lOld;
					//lPos = std::next(list[i][j].begin(), l);

					//l += tempCntr;
					//cout << "l: " << (int) l << "\n";

					//cout << "Insert New Elements...\n";

					//listVctrLDim.insert(lPos, (tempCntr), tempCombo);

					//cout << "Next position...\n";

					
					//l += tempCntr + lOld;
					// increment 1 as lOld increments
					//l++;
					//lPos = std::next(listVctrLDim.begin(), l);

					if (possibilitiesIIndx == possibilitiesIIndxPrev && possibilitiesJIndx == possibilitiesJIndxPrev && possibilitiesPIndx < possibilities[possibilitiesIIndx][possibilitiesJIndx].size())
					{
						possibilitiesPIndx++;
						cout << "condition 2nd check true, increment p index\n";
					}
					else
					{
						//already done above?
						//possibilitiesPIndx = 0U;
						cout << "condition 2nd check false, no action\n";
					}				
				}
			}
		}

		cout << "list vector print\n";
		for (uint8_t i = 0U; i < list.size(); i++)
		{
			for (uint8_t j = 0U; j < list[i].size(); j++)
			{
				printComboListVctrLDim(list[i][j]);
			}
		}
	}

	cout << "final list vector print\n";
	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			printComboListVctrLDim(list[i][j]);
		}
	}

	cout << endl;
}

int main()
{
	cout << "\n";
	cout << "\n";
	cout << "Program Initialised.\n";

	//runKeybrdKnightsBruteForce();
	runKeybrdKnightsTopDown();

	cout << "Program Complete.\n";
	cout << "\n";
	cout << "\n";

	/* // Close the file
	log.close(); */

	return 0;
}