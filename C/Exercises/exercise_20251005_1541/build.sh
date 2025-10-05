# build.sh

# Prequisites:
# 	- g++

#!/bin/bash

# printf better than echo ?
printf "\n"
printf "Build shell script: Beginning of script\n"
printf "\n"
printf "\n"

cd "$(dirname "$0")"

printf "Build shell script: Files in Current Dirtectory:"
printf "$(dirname "$0")"
printf "\n"

printf "\n"

ls

printf "\n"
printf "Build shell script: Building program...\n"
printf "\n"

# Don't know how I worked with modules in uni, I don't remember having to include them in the build command
# This is why CMake or Makefile would be good to implement
#gcc main.c -v -Wpedantic -std=c23 -o ./build/Program_Main
gcc main.c dgac_c_lib_data-types/mod_binary-bitwise-ops_gen/dgac_c_lib_data-types_mod_binary-bitwise-ops_gen_gen.c -Wpedantic -std=c23 -o ./build/Program_Main

printf "\n"
printf "Build shell script: If the last message was:\n"
printf "'\n"
printf "Building program...\n"
printf "'\n"
printf ", then the program has built / compiled successfully! \n"
printf "\n"

printf "\n"
printf "Build shell script: End of script\n"
printf "\n"