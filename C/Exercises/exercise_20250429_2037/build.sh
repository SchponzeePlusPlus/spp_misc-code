# build.sh

# Prequisites:
# 	- g++

#!/bin/bash

# printf better than echo ?
printf "\n"
printf "This is a build shell script\n"
printf "\n"
printf "\n"

cd "$(dirname "$0")"

printf "Files in Current Dirtectory:"
printf "$(dirname "$0")"
printf "\n"

printf "\n"

ls

g++ -o ./build/Program_Main main.cpp

printf "\n"
printf "End of shell script\n"
printf "\n"