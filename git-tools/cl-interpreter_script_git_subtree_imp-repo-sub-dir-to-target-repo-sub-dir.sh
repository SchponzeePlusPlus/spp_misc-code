#!/bin/bash

# cl-interpreter_script_git_subtree_imp-repo-sub-dir-to-target-repo-sub-dir.sh
# Command Line Interpreter Script: Git Subtree: Import Repo Sub-Dir to Target Repo Sub-Dir
# Using the subtree function, this script pulls from an import remote and 

# File origin
# https://medium.com/@icheko/use-a-subfolder-from-a-remote-repo-in-another-repo-using-git-subtree-98046f33ca40
# https://gist.github.com/icheko/9ff2a0a90ef2b676a5fc8d76f69db1d3
# Author: icheko

echo
echo -----------------------------------------
echo -----------------------------------------
echo

IMPORT_GIT_HOSTNG_SERVC_ABBREV="gh"
IMPORT_ENTITY="SchponzeePlusPlus"
IMPORT_REPO_TITLE="test-repo-02"
#echo "What is the import repo's remote location (HTTPS)?:"
IMPORT_REPO_REMOTE_HTTPS="https://github.com/SchponzeePlusPlus/test-repo-02.git"
#read IMPORT_REPO_REMOTE_HTTPS
IMPORT_REPO_BRANCH="main"
IMPORT_REPO_CONTENT_SUB_DIR="test-00"

TARGET_REPO_TITLE="test-repo-01"
TARGET_REPO_MAIN_BRANCH="main"
TARGET_REPO_REMOTE="origin"
TARGET_REPO_REMOTE_MAIN_BRANCH="origin/main"
#echo "What is the target repo's merging branch name?:"
TARGET_REPO_MERGING_BRANCH="feature/imp-spp-test-repo-02-000"
TARGET_REPO_IMPORTED_CONTENT_SUB_DIR="imprtd/test-repo-02-000"

IMPORT_REPO_REMOTE="origin_${IMPORT_GIT_HOSTNG_SERVC_ABBREV}_${IMPORT_ENTITY}_${IMPORT_REPO_TITLE}"

echo
echo "IMPORT_REPO_REMOTE : ${IMPORT_REPO_REMOTE}"
echo

# The imp_raw branch is not intended for being pushed back to the target repo
# I want to squash the commits first
TARGET_REPO_IMP_RAW_BRANCH_TITLE="imp_raw/${IMPORT_GIT_HOSTNG_SERVC_ABBREV}/${IMPORT_ENTITY}/${IMPORT_REPO_TITLE}/${IMPORT_REPO_BRANCH}"

TARGET_REPO_IMP_BRANCH_TITLE="imp/${IMPORT_GIT_HOSTNG_SERVC_ABBREV}/${IMPORT_ENTITY}/${IMPORT_REPO_TITLE}/${IMPORT_REPO_BRANCH}"

echo
echo "Target Repo Import Branch ${TARGET_REPO_IMP_RAW_BRANCH_TITLE}"
echo

git status
git checkout ${TARGET_REPO_MAIN_BRANCH}

git fetch --all
git pull ${TARGET_REPO_REMOTE}

# checkout source repo
#git checkout -b ${IMPORT_REPO_BRANCH} helmcharts/master
git switch --orphan ${TARGET_REPO_IMP_RAW_BRANCH_TITLE}

git remote add -f ${IMPORT_REPO_REMOTE} ${IMPORT_REPO_REMOTE_HTTPS}
echo
echo "Fetch new changes from import repo"
echo -----------------------------------------

#git fetch helmcharts master
git fetch ${IMPORT_REPO_REMOTE}

IMPORT_REPO_LATEST_COMMIT=`git ls-remote ${IMPORT_REPO_REMOTE} | grep "refs/heads/${IMPORT_REPO_BRANCH}" | awk '{ print $1}'`

echo
echo "import repo latest commit: ${IMPORT_REPO_LATEST_COMMIT}"
echo

git pull --squash ${IMPORT_REPO_REMOTE} ${IMPORT_REPO_BRANCH}
# dedicated branch for squashed import
#git switch --orphan ${TARGET_REPO_IMP_BRANCH_TITLE}

# Squash imported commits
# --message "Squash Import"
# create new staging branch from all the commits impacting "/${IMPORT_REPO_CONTENT_SUB_DIR}" from source repo
git subtree split -P ${IMPORT_REPO_CONTENT_SUB_DIR} -b ${TARGET_REPO_IMP_BRANCH_TITLE}

# Rebase interactively to squash commits
git checkout ${TARGET_REPO_IMP_BRANCH_TITLE}
git reset --soft $(git rev-list --max-parents=0 HEAD)  # Reset to the root commit
git commit --amend --no-edit --message "Squashed commits from ${IMPORT_REPO_REMOTE_HTTPS}, Directory: ${IMPORT_REPO_CONTENT_SUB_DIR}"

# set up-stream
#git push -u ${TARGET_REPO_REMOTE} ${TARGET_REPO_IMP_BRANCH_TITLE}

# checkout main
git checkout ${TARGET_REPO_MAIN_BRANCH}

git fetch --all
git pull ${TARGET_REPO_REMOTE}

git checkout -b ${TARGET_REPO_MERGING_BRANCH}

# take commits in the staging branch and set "/helm-charts/${IMPORT_REPO_CONTENT_SUB_DIR}" as the commit root
# after you run this script the first time, update the command below to:
# "git subtree merge" with the same parameters
#

echo
echo "Add in changes"
echo -----------------------------------------
#git subtree add -P helm-charts/${IMPORT_REPO_CONTENT_SUB_DIR} ${TARGET_REPO_IMP_BRANCH_TITLE}

echo "${TARGET_REPO_IMPORTED_CONTENT_SUB_DIR}/${IMPORT_REPO_CONTENT_SUB_DIR}"

git subtree add -P "${TARGET_REPO_IMPORTED_CONTENT_SUB_DIR}/${IMPORT_REPO_CONTENT_SUB_DIR}" ${TARGET_REPO_IMP_BRANCH_TITLE} --message "Git Subtree Import from ${IMPORT_REPO_REMOTE_HTTPS} , Directory: ${IMPORT_REPO_CONTENT_SUB_DIR} , As per commit: ${IMPORT_REPO_LATEST_COMMIT}"

# clean up
echo
echo
#git branch -D ${TARGET_REPO_IMP_RAW_BRANCH_TITLE}
#git branch -D ${TARGET_REPO_IMP_BRANCH_TITLE}
#git branch -D ${IMPORT_REPO_BRANCH}

echo
echo -----------------------------------------
echo -----------------------------------------
echo