# run.sh

#!/bin/bash

printf "\n"
printf "Run shell script: Beginning of script\n"
printf "This script shall run the target program.\n"
printf "\n"
printf "\n"

cd "$(dirname "$0")"

printf "Run shell script: Files in Current Dirtectory:"
printf "$(dirname "$0")"
printf "\n"

printf "\n"
printf "\n"

ls

printf "\n"
printf "Run shell script: Running Target Program:\n"
printf "\n"

./build/Program_Main

printf "\n"
printf "Run shell script: Finished Running Target Program:\n"
printf "\n"

printf "\n"
printf "Run shell script: End of script\n"
printf "\n"