# git_submodules_update.sh

# Prequisites:
# 	- Bash

#!/bin/bash

# printf better than echo ?
printf "\n"
printf "git_submodules_update script: Beginning of script\n"
printf "\n"
printf "\n"

cd "$(dirname "$0")"

printf "git_submodules_update script: Files in Current Dirtectory:"
printf "$(dirname "$0")"
printf "\n"

printf "\n"

ls

printf "\n"
printf "git_submodules_update script: Updating submodules...\n"
printf "\n"

git submodule update --recursive --remote

printf "\n"
printf "git_submodules_updatel script: If the last message was:\n"
printf "'\n"
printf "...\n"
printf "'\n"
printf ", then the _ has _ successfully! \n"
printf "\n"

printf "\n"
printf "git_submodules_update script: End of script\n"
printf "\n"