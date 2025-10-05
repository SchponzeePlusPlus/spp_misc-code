/*
 * exercise_20251005_1541 / main.c
 *
 * Title:
 * 
 * Author: SchponzeePlusPlus
 * 
 * SPP GitHub Link: N/A
 *
 */

// For console printing to work
#include <stdio.h>

#include "dgac_c_lib_data-types\mod_binary-bitwise-ops_gen\dgac_c_lib_data-types_mod_binary-bitwise-ops_gen_gen.h"

int main()
{
	printf("\n");
	printf("\n");
	printf("Program Initialised.\n");

	printf("\n");

	uint32_t valOne = 0x00000000U;
	uint32_t valTwo = 0xFFFFFFFFU;

	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	printf("Set Bit Shifting valOne...\n");
	printf("Clear Bit Shifting valTwo...\n");
	valOne = setShiftLeftIntoValUint32(valOne, 1U, 0U);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 1U, 0U);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 1U, 1U);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 1U, 1U);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 1U, 2U);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 1U, 2U);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 2U, 3U);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 2U, 3U);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 0b1111111111111111111111111111U, 5U);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 0b1111111111111111111111111111U, 5U);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);

	valOne = 0x00000000U;
	printf("Set Bit Shifting For loop no save\n");
	for (int16_t i = 0; i < 32; i++)
	{
		printf("valOne = %lu\n", setShiftLeftIntoValUint32(valOne, 1U, (uint8_t) i));
	}
	printf("\n");
	valOne = 0x00000000U;
	printf("Set Bit Shifting For loop\n");
	for (int16_t i = 0; i < 32; i++)
	{
		valOne = setShiftLeftIntoValUint32(valOne, 1U, (uint8_t) i);
		printf("valOne = %lu\n", valOne);
	}
	printf("\n");
	valOne = 0x00000000U;
	printf("Test Repetitive Set Bit Shifting 0th digit For loop\n");
	for (int16_t i = 0; i < 32; i++)
	{
		valOne = setShiftLeftIntoValUint32(valOne, 1U, 0U);
		printf("valOne = %lu\n", valOne);
	}
	printf("\n");
	valTwo = 0xFFFFFFFFU;
	printf("Clear Bit Shifting For loop but no save\n");
	printf("valTwo = %lu\n", valTwo);
	for (int16_t i = 31; i > -1 ; i--)
	{
		//printf("i = %d\n", i);
		printf("valTwo = %lu\n", clearShiftLeftIntoValUint32(valTwo, 1U, (uint8_t) i));
	}
	printf("\n");
	valTwo = 0xFFFFFFFFU;
	printf("Clear Bit Shifting For loop\n");
	printf("valTwo = %lu\n", valTwo);
	for (int16_t i = 31; i > -1 ; i--)
	{
		//printf("i = %d\n", i);
		valTwo = clearShiftLeftIntoValUint32(valTwo, 1U, (uint8_t) i);
		printf("valTwo = %lu\n", valTwo);
	}

	printf("Program Complete.\n");
	printf("\n");
	printf("\n");

	return 0;
}