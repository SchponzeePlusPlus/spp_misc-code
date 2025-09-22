# run.sh

#!/bin/bash

printf "\n"
printf "This is a shell script to run the target program\n"
printf "\n"
printf "\n"

cd "$(dirname "$0")"

printf "Files in Current Dirtectory:"
printf "$(dirname "$0")"
printf "\n"

printf "\n"
printf "\n"

ls

printf "\n"
printf "Running Target Program:\n"
printf "\n"

./build/Program_Main

printf "\n"
printf "Finished Running Target Program:\n"
printf "\n"

printf "\n"
printf "End of shell script\n"
printf "\n"