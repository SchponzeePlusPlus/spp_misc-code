/*
 * C/Cpp/Exercises/exercise_20250922_1314/main.cpp
 * Keyboard Knights Coding Challenge
 * 
 * Author: SchponzeePlusPlus
 * 
 * Version: V0.0.0.2
 * 
 * Solution Attempt: No. 3
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

#define DIM_CNT_2D ((uint8_t) 2U) // position in a 2-dim array(i,j), 2 dimensions
#define POSITN_TRANSITN_POSITN_CNT ((uint8_t) 2U) // transition betwen old position and new position

#define KEYBRD_ROW_LENGTH ((uint8_t) 4U)
#define KEYBRD_COLMN_LENGTH ((uint8_t) 5U)
#define KNIGHT_MOVE_01_SHIFT_ELEMS ((uint8_t) 2U)
#define KNIGHT_MOVE_02_SHIFT_ELEMS ((uint8_t) 1U)
// p for chess move possibilities of current position
#define MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW ((uint8_t) 8U)
// m: chess move for knight
#define MOV_KNIGHT_LINEAR_MOVS_CNT ((uint8_t) 2U)

#define KEY_PRESSNG_CHAR_COMBO_LENGTH ((uint8_t) 10U) // modify to change length of sequence

// L is reserved for combination list, which doesn't have a constant value

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

struct chessMoveKnightPositnNewPossiblty
{
	// old -> new position direction
	enum chessMovKnightDirState enmCMKDS_transitnDirState;
	std::array<enum dirTwoDimState, 2U> transitnmovsDirArr;
	enum chessMovKnightTransitnValidtyState enmCMKTVS_transitnValidtyState;
	std::array<uint8_t, 2> U8StdArr_positnNew;
};

struct keyPressComboCharProc
{
	std::array<uint8_t, DIM_CNT_2D> kPPositnArr;
	enum keyPressComboCharProcState kPPCCPState;
};

typedef std::array<uint8_t, DIM_CNT_2D> U8ArrStdOf02;
typedef std::array<std::array<uint8_t, DIM_CNT_2D>, KEY_PRESSNG_CHAR_COMBO_LENGTH> U8ArrStdOf10Of02;
typedef std::array<std::array<uint8_t, DIM_CNT_2D>, POSITN_TRANSITN_POSITN_CNT> U8ArrStdOf02Of02;
typedef U8ArrStdOf02 kPPositnArr;
typedef std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW>, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> PossibilitiesArr;
typedef U8ArrStdOf10Of02 KPComboArr;
typedef U8ArrStdOf02Of02 KPTransArr; //old position and new position

// I'm replacing '\0' with '0' and '4', there aren't supposed to be anything in those positions anyway
const std::array<std::array<char, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> STD_CHARARR_KEYBRD_LAYOUT
{{
	{'A', 'B', 'C', 'D', 'E'},
	{'F', 'G', 'H', 'I', 'J'},
	{'K', 'L', 'M', 'N', 'O'},
	{'0', '1', '2', '3', '4'},
}};

const std::array<uint8_t, DIM_CNT_2D>
	U8_STD_ARR_ONE_DIM_KEYBRD_LENGTHS 
{{
	KEYBRD_ROW_LENGTH,
	KEYBRD_COLMN_LENGTH
}};

const std::array<uint8_t, MOV_KNIGHT_LINEAR_MOVS_CNT>
	U8_STD_ARR_ONE_DIM_CHESS_MOV_KNIGHT_SHIFTS 
{{
	KNIGHT_MOVE_01_SHIFT_ELEMS,
	KNIGHT_MOVE_02_SHIFT_ELEMS
}};

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
	for (uint8_t m = 0; m < MOV_KNIGHT_LINEAR_MOVS_CNT; m++)
	{
		result[m] = unassignEnumDirTwoDimState();
	}
	return result;
}

std::array<uint8_t, 2> unassignU8ArrTwoDim()
{
	std::array<uint8_t,2> result;
	for (uint8_t arrIndx = 0U; arrIndx < 2; arrIndx++)
	{
		result[arrIndx] = 0U;
	}
	return result;
}

std::array<int8_t, 2> unassignI8ArrOf02Elems()
{
	std::array<int8_t, 2> result;
	for (uint8_t arrIndx = 0U; arrIndx < 2; arrIndx++)
	{
		result[arrIndx] = 0;
	}
	return result;
}

std::array<std::array<int8_t, 2U>, 2U> unassignI8ArrOf02Of02Elems()
{
	std::array<std::array<int8_t, 2U>, 2U> result;
	for (uint8_t arrIndx = 0U; arrIndx < 2; arrIndx++)
	{
		result[arrIndx] = unassignI8ArrOf02Elems();
	}
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
	enum arrElemsOneDimSelctdShiftValidityState result = AEODSSVState_UNASSIGNED;

	int int_proposdElemPositn = (u8_arrOneDimElemInPositn + elemDimOneShift);

	if ((int_proposdElemPositn >= 0) && (int_proposdElemPositn < u8_arrOneDimLengthIn))
	{
		result = AEODSSVState_ALLOWED;	
	}
	else if ((int_proposdElemPositn == -1))
	{
		result = AEODSSVState_DISALLOWED_PRECEDNG_INIT_ELEM;
	}
	else if ((int_proposdElemPositn == (u8_arrOneDimLengthIn)))
	{
		result = AEODSSVState_DISALLOWED_SUCCEEDNG_FINAL_ELEM;
	}
	else
	{
		result = AEODSSVState_DISALLOWED_MISC;
	}

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

	for (uint8_t d = 0; d < DIM_CNT_2D; d++)
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

	for (uint8_t m = 0; m < MOV_KNIGHT_LINEAR_MOVS_CNT; m++)
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
	for (uint8_t d = 0; d < DIM_CNT_2D; d++)
	{
		chkTrueCntr = ((chkMoveShiftOneDimTries(moveShiftTries[d])) ? chkTrueCntr + 1 : chkTrueCntr);
	}
	return (chkTrueCntr == DIM_CNT_2D);
}

bool chkAllMoveShiftTries
(
	const std::array<std::array<enum arrElemsOneDimSelctdShiftValidityState, 2U>, 2U>& allMovesShiftTries
)
{
	uint8_t chkTrueCntr = 0U;

	for (uint8_t m = 0; m < MOV_KNIGHT_LINEAR_MOVS_CNT; m++)
	{
		chkTrueCntr = ((chkMoveShiftTwoDimTries(allMovesShiftTries[m])) ? chkTrueCntr + 1 : chkTrueCntr);
	}
	return (chkTrueCntr == MOV_KNIGHT_LINEAR_MOVS_CNT);
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

	for (uint8_t m = 0; m < MOV_KNIGHT_LINEAR_MOVS_CNT; m++)
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

char returnCharFromKeybrdLayoutStdArr(kPPositnArr keybrdPosition)
{
	char result = '\0';

	if (((keybrdPosition[0] >= 0U) && (keybrdPosition[0] < KEYBRD_ROW_LENGTH)) && ((keybrdPosition[1] >= 0U) && (keybrdPosition[1] < KEYBRD_COLMN_LENGTH)))
	{
		result = STD_CHARARR_KEYBRD_LAYOUT[keybrdPosition[0]][keybrdPosition[1]];
	}
	else
	{
		result = '!'; // not sure what else i could use to return an error
	}
	return result;
}

void printKeyPressCharFromStdArr(const std::array<uint8_t, DIM_CNT_2D>& inPositn)
{
	cout << returnCharFromKeybrdLayoutStdArr(inPositn);
}

std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW> returnChessMoveKnightPositnNewPossibltiesArr(const std::array<uint8_t, 2> &keyPressdArrayPositn) //function with return type std::array
{
    std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW> result; //array declared

	for(uint8_t p = 0; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
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
		for(uint8_t p = 0; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
		{
			result[p].enmCMKTVS_transitnValidtyState = CMKTVState_INVALID;
		}
	}
	else
	{
		for(uint8_t p = 0; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
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

std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW>, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH>
unassignAllChessMoveKnightPositnNewPossiblties()
{
	std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW>, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> result;

	for (uint8_t i = 0; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0; j < KEYBRD_COLMN_LENGTH; j++)
		{
			for (uint8_t p = 0; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
			{
				result[i][j][p] = unassignStrChessMoveKnightPositnNewPossiblty();
			}
		}
	}

	return result;
}

std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW>, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH>
generateAllChessMoveKnightPositnNewPossiblties()
{
	std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW>, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> result = unassignAllChessMoveKnightPositnNewPossiblties();

	std::array<uint8_t, 2> keyPressArrayPositnCurr = unassignU8ArrTwoDim();

	for (uint8_t i = 0; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0; j < KEYBRD_COLMN_LENGTH; j++)
		{
			keyPressArrayPositnCurr[0] = i;
			keyPressArrayPositnCurr[1] = j;
			result[i][j] = returnChessMoveKnightPositnNewPossibltiesArr(keyPressArrayPositnCurr);
		}
	}

	return result;
}

void printPossibilities(const PossibilitiesArr& possibilitiesRaw)
{
	std::array<uint8_t, 2> tempKeyPressPositn = unassignU8ArrTwoDim();
	
	uint64_t u64_possibilityCnt = 0;

	cout << "Possibilities:\n";
	for (uint8_t i = 0; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0; j < KEYBRD_COLMN_LENGTH; j++)
		{
			for (uint8_t p = 0; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
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
}

void resizePossibilitiesVector(std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>>& possibilities)
{
	possibilities.resize(KEYBRD_ROW_LENGTH);

	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		possibilities[i].resize(KEYBRD_COLMN_LENGTH);
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			possibilities[i][j].resize(MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW);
		}
	}
}

void unassignPossibilitiesVector(std::vector<std::vector<std::vector<std::array<uint8_t, 2>>>>& possibilities)
{
	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			for (uint8_t p = 0U; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
			{
				for (uint8_t d = 0U; d < DIM_CNT_2D; d++)
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
	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			pVctr = 0U;
			for (uint8_t p = 0U; p < MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW; p++)
			{
				if (possibilitiesRaw[i][j][p].enmCMKTVS_transitnValidtyState == CMKTVState_VALID)
				{
					possibilities[i][j][pVctr] = possibilitiesRaw[i][j][p].U8StdArr_positnNew;
					pVctr++;
				}
				else
				{
					possibilities[i][j].erase (possibilities[i][j].begin() + pVctr);
				}
			}
		}
	}
}

std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH> unassignCombo()
{
	std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH> result;
	for (uint8_t k = 0U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
	{
		for (uint8_t d = 0U; d < DIM_CNT_2D; d++)
		{
			result[k].kPPositnArr[d] = 0U;
		}
		result[k].kPPCCPState = EState_UNASSIGNED;
	}
	return result;
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

void printComboListVctrLDim(const std::vector<std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH>>& listVctrLDim)
{
	for (uint64_t l = 0U; l < (uint64_t) listVctrLDim.size(); l++)
	{
		for (uint8_t k = 0U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
		{
			//printKeyPressCharFromStdArr({i, j});
			printKeyPressCharFromStdArr(listVctrLDim[l][k].kPPositnArr);
		}
		cout << "\n";
	}
}

void printComboListVctr(const std::vector<std::vector<std::vector<std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH>>>>& comboListVctr)
{
	cout << "list vector print\n";
	for (uint8_t i = 0U; i < comboListVctr.size(); i++)
	{
		for (uint8_t j = 0U; j < comboListVctr[i].size(); j++)
		{
			printComboListVctrLDim(comboListVctr[i][j]);
		}
	}
}

void resizeListVctrLDim(std::vector<std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH>>& listVctrLDim, const std::array<std::array<uint64_t, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH>& listPossibilityCntArr2KPs, const uint8_t& k)
{
	uint64_t l = 0U;
	uint64_t tempCntr = 0U;
	auto lPos = listVctrLDim.begin();
	std::size_t oldLSz = listVctrLDim.size();
	std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH> tempCombo = unassignCombo();
	for (uint64_t lOld = 0U; lOld < (uint64_t) oldLSz; lOld++)
	{
		tempCombo = listVctrLDim[l];
		/* for (uint8_t k = 0U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
		{
			//printKeyPressCharFromStdArr({i, j});
			printKeyPressCharFromStdArr(tempCombo[k].kPPositnArr);
		}
		cout << "\n";*/
		tempCntr = (listPossibilityCntArr2KPs[listVctrLDim[l][k - 1U].kPPositnArr[0]][listVctrLDim[l][k - 1U].kPPositnArr[1]] - 1U);
		l += tempCntr;
		listVctrLDim.insert(lPos, (tempCntr), tempCombo);
		l++;
		lPos = std::next(listVctrLDim.begin(), l);
	}
}

void removeListVctrLDimVowelChk(std::vector<std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH>>& listVctrLDim, const uint8_t& k)
{
	uint64_t l = 0U;
	uint64_t lOldSz = (uint64_t) listVctrLDim.size();
	for (uint64_t lOld = 0U; lOld < lOldSz; lOld++)
	{
		//cout << "Target Combo: ";
		// remove for() loop print below this comment from this procedure, but maybe make it its own procedure for reference?
		/* for (uint8_t kPrint = 0U; kPrint < KEY_PRESSNG_CHAR_COMBO_LENGTH; kPrint++)
		{
			//printKeyPressCharFromStdArr({i, j});
			printKeyPressCharFromStdArr(listVctrLDim[l][kPrint].kPPositnArr);
		} */
		//cout << "\n";
		//cout << "lOld: " << (int) lOld << "\n";
		uint8_t cntVowels = 0U;
		if (listVctrLDim.size() > 0U)
		{
			for (uint8_t kVowelChk = 0U; kVowelChk < k + 1; kVowelChk++)
			{
				cntVowels = (chkCharIsVowel(returnCharFromKeybrdLayoutStdArr(listVctrLDim[l][kVowelChk].kPPositnArr))) ? cntVowels + 1U : cntVowels;
			}
		}
		//cout << "cntVowels: " << (int) cntVowels << "\n";
		if (cntVowels > 2U)
		{
			//cout << "Erasing (due to containing 3 + vowels): ";
			// remove for() loop print below this comment from this procedure, but maybe make it its own procedure for reference?
			/* for (uint8_t kPrint = 0U; kPrint < KEY_PRESSNG_CHAR_COMBO_LENGTH; kPrint++)
			{
				//printKeyPressCharFromStdArr({i, j});
				printKeyPressCharFromStdArr(listVctrLDim[l][kPrint].kPPositnArr);
			}
			cout << "\n"; */
			listVctrLDim.erase(listVctrLDim.begin() + l);
		}
		else
		{
			l++;
		}
	}
}

int main()
{
	std::array<std::array<std::array<struct chessMoveKnightPositnNewPossiblty, MOV_KNIGHT_POSITN_SHFT_POSSIBILITIES_RAW>, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> possibilitiesRaw = generateAllChessMoveKnightPositnNewPossiblties();

	//printPossibilities(possibilitiesRaw);

	std::vector<std::vector<std::vector<std::array<uint8_t, 2U>>>> possibilities;

	resizePossibilitiesVector(possibilities);
	
	unassignPossibilitiesVector(possibilities);

	copyFiltrdPossibilitiesVector(possibilities, possibilitiesRaw);

	//printPossibilitiesVector(possibilities);

	cout << "list vector\n";
	
	std::vector<std::vector<std::vector<std::array<struct keyPressComboCharProc, KEY_PRESSNG_CHAR_COMBO_LENGTH>>>> list;

	//cout << "resize list vector i\n";

	list.resize(KEYBRD_ROW_LENGTH);

	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		//cout << "resize list vector j\n";
		list[i].resize(KEYBRD_COLMN_LENGTH);
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			//cout << "size: " << possibilities[i][j].size() << "\n";
			list[i][j].resize(possibilities[i][j].size());
		}
	}

	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			for (uint64_t l = 0U; l < (uint64_t) list[i][j].size(); l++)
			{
				for (uint8_t k = 0U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
				{
					for (uint8_t d = 0U; d < DIM_CNT_2D; d++)
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
			for (uint64_t l = 0U; l < (uint64_t) list[i][j].size(); l++)
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

	// remove for() loop print below this comment from this procedure, but maybe make it its own procedure for reference?
	/* cout << "list vector print\n";
	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			for (uint64_t l = 0U; l < (uint64_t) list[i][j].size(); l++)
			{
				for (uint8_t k = 0U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
				{
					//printKeyPressCharFromStdArr({i, j});
					printKeyPressCharFromStdArr(list[i][j][l][k].kPPositnArr);
				}
				cout << "\n";
			}
		}
	} */

	std:array<std::array<uint64_t, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> listPossibilityCntArr;

	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			listPossibilityCntArr[i][j] = list[i][j].size();
		}
	}

	std::array<std::array<uint64_t, KEYBRD_COLMN_LENGTH>, KEYBRD_ROW_LENGTH> listPossibilityCntArr2KPs = listPossibilityCntArr;

	// remove for() loop print below this comment from this procedure, but maybe make it its own procedure for reference?
	/* cout << "list possibility counts per key\n";
	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			printKeyPressCharFromStdArr({i, j});
			cout << ": " << listPossibilityCntArr[i][j] << "\n";
		}
	} */

	std::array<uint8_t, DIM_CNT_2D> tempPos = {0U, 0U};

	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			for (uint64_t l = 0U; l < (uint64_t) list[i][j].size(); l++)
			{
				// key press of last checked, how many possibilities? lookup value and return count
				//listPossibilityCntArr[i][j] += 
				//list[i][j][l][1].kPPositnArr == tempPos;
				listPossibilityCntArr[i][j] += (listPossibilityCntArr2KPs[list[i][j][l][1].kPPositnArr[0]][list[i][j][l][1].kPPositnArr[1]] - 1U);
			}
		}
	}

	// remove for() loop print below this comment from this procedure, but maybe make it its own procedure for reference?
	/* cout << "list possibility counts per key\n";
	for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
	{
		for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
		{
			printKeyPressCharFromStdArr({i, j});
			cout << ": " << listPossibilityCntArr[i][j] << "\n";
		}
	} */

	cout << "HERE\n";
	
	for (uint8_t k = 2U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
	{
		// resize vector
		for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
		{
			//cout << "i: " << (int) i << "\n";
			for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
			{
				//cout << "j: " << (int) j << "\n";
				resizeListVctrLDim(list[i][j], listPossibilityCntArr2KPs, k);
			}
		}

		//printComboListVctr(list);

		// the next step is to fill 3rd character, using the possibilities vector to lookup k and fill the transitions for k + 1, the vector has already been resized to accomodate
		// the fill or assign or populate or generate or whatever procedure might be similar to the resize in the way that that the resize l dim looks up the count and resizes accordingly

		// fill next key press (3rd key for now); k = 2
		cout << "fill stage\n";
		for (uint8_t i = 0U; i < KEYBRD_ROW_LENGTH; i++)
		{
			//cout << "i: " << (int) i << "\n";
			for (uint8_t j = 0U; j < KEYBRD_COLMN_LENGTH; j++)
			{
				uint8_t possibilitiesIIndx = 0U;
				uint8_t possibilitiesJIndx = 0U;
				//cout << "possibilitiesIIndx: " << (int) possibilitiesIIndx << "\n";
				//cout << "possibilitiesJIndx: " << (int) possibilitiesJIndx << "\n";
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
				//cout << "j: " << (int) j << "\n";
				for (uint64_t l = 0U; l < (uint64_t) list[i][j].size(); l++)
				{
					//cout << "l: " << (int) l << "\n";
					//possibilities[i][j];

					possibilitiesIIndxPrev = possibilitiesIIndx;
					possibilitiesJIndxPrev = possibilitiesJIndx;
					
					possibilitiesIIndx = list[i][j][l][k - 1U].kPPositnArr[0];
					possibilitiesJIndx = list[i][j][l][k - 1U].kPPositnArr[1];

					if (possibilitiesIIndx == possibilitiesIIndxPrev && possibilitiesJIndx == possibilitiesJIndxPrev && possibilitiesPIndx < possibilities[possibilitiesIIndx][possibilitiesJIndx].size())
					{
						// already incremented below
						//cout << "condition 1st check true no action\n";
					}
					else
					{
						possibilitiesPIndx = 0U;
						possibilitiesIIndxPrev = possibilitiesIIndx;
						possibilitiesJIndxPrev = possibilitiesJIndx;
						//cout << "condition 1st check false, reset P Index\n";
					}

					//cout << "Possibility: ";
					//printKeyPressCharFromStdArr({possibilitiesIIndx, possibilitiesJIndx});
					//printKeyPressCharFromStdArr(possibilities[possibilitiesIIndx][possibilitiesJIndx][possibilitiesPIndx]);
					//cout << "\n";

					list[i][j][l][k].kPPositnArr = possibilities[possibilitiesIIndx][possibilitiesJIndx][possibilitiesPIndx];
					
					//list[i][j].push_back(unassignedCombo);
					//tempCombo = listVctrLDim[l];
					/* for (uint8_t k = 0U; k < KEY_PRESSNG_CHAR_COMBO_LENGTH; k++)
					{
						//printKeyPressCharFromStdArr({i, j});
						printKeyPressCharFromStdArr(tempCombo[k].kPPositnArr);
					}
					cout << "\n";*/
					
					if (possibilitiesIIndx == possibilitiesIIndxPrev && possibilitiesJIndx == possibilitiesJIndxPrev && possibilitiesPIndx < possibilities[possibilitiesIIndx][possibilitiesJIndx].size())
					{
						possibilitiesPIndx++;
						//cout << "condition 2nd check true, increment p index\n";
					}
					else
					{
						//already done above?
						//possibilitiesPIndx = 0U;
						//cout << "condition 2nd check false, no action\n";
					}				
				}
			}
		}

		// remove combinations with more than 2 vowels
		cout << "vowel check stage\n";
		for (uint8_t i = 0U; i < list.size(); i++)
		{
			for (uint8_t j = 0U; j < list[i].size(); j++)
			{
				removeListVctrLDimVowelChk(list[i][j], k);
			}
		}

		//printComboListVctr(list);
	}

	cout << "final list vector print\n";
	printComboListVctr(list);

	uint64_t cntKPCombos = 0U;
	for (uint8_t i = 0U; i < list.size(); i++)
	{
		for (uint8_t j = 0U; j < list[i].size(); j++)
		{
			cntKPCombos += (uint64_t) list[i][j].size();
		}
	}
	cout << "list vector total count: " << (long long int) cntKPCombos << "\n";

	cout << endl;
	return 0;
}