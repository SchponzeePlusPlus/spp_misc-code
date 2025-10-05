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
	valOne = setShiftLeftIntoValUint32(valOne, 1, 0);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 1, 0);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 1, 1);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 1, 1);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 1, 2);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 1, 2);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 2, 3);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 2, 3);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);
	valOne = setShiftLeftIntoValUint32(valOne, 0b1111111111111111111111111111, 5);
	valTwo = clearShiftLeftIntoValUint32(valTwo, 0b1111111111111111111111111111, 5);
	printf("valOne = %lu\n", valOne);
	printf("valTwo = %lu\n", valTwo);

	valOne = 0x00000000U;
	printf("Set Bit Shifting For loop\n");
	for (int16_t i = 0; i < 32; i++)
	{
		printf("valOne = %lu\n", setShiftLeftIntoValUint32(valOne, 1, (uint8_t) i));
	}
	printf("\n");
	valTwo = 0xFFFFFFFFU;
	printf("Clear Bit Shifting For loop\n");
	for (int16_t i = 31; i > -1 ; i--)
	{
		//printf("i = %d\n", i);
		printf("valTwo = %lu\n", clearShiftLeftIntoValUint32(valTwo, 1, (uint8_t) i));
	}

	printf("Program Complete.\n");
	printf("\n");
	printf("\n");

	return 0;
}