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

# Exercise author/s requested -Wpedantic and using as recent a version of C++ as desired
g++ -o ./build/Program_Main main.cpp -Wpedantic -std='c++23'

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