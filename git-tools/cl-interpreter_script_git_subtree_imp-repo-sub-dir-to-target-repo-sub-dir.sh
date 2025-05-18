#!/bin/bash

# cl-interpreter_script_git_subtree_imp-repo-sub-dir-to-target-repo-sub-dir.sh
# Command Line Interpreter Script: Git Subtree: Import Repo Sub-Dir to Target Repo Sub-Dir

# File origin
# https://medium.com/@icheko/use-a-subfolder-from-a-remote-repo-in-another-repo-using-git-subtree-98046f33ca40
# https://gist.github.com/icheko/9ff2a0a90ef2b676a5fc8d76f69db1d3
# Author: icheko

IMPORT_GIT_HOSTNG_SERVC_ABBREV="gh"
IMPORT_ENTITY="icheko"
IMPORT_REPO_TITLE="gist/medium-git-subtree"
IMPORT_BRANCH="main"

TARGET_REPO_MAIN_BRANCH="main"
TARGET_REPO_MERGING_BRANCH=""
STAGING_BRANCH="helmcharts-staging"

TARGET_REPO_IMP_BRANCH="imp/${IMPORT_GIT_HOSTNG_SERVC_ABBREV}/${IMPORT_ENTITY}/${IMPORT_REPO_TITLE}/${IMPORT_BRANCH}"

echo -----------------------------------------
echo "Target Repo Import Branch ${TARGET_REPO_IMP_BRANCH}"

#git branch TARGET_REPO_IMP_BRANCH
#git checkout TARGET_REPO_IMP_BRANCH


echo
echo "Fetch new changes from helmcharts"
echo -----------------------------------------
#git fetch helmcharts master

#HELMCHARTS_LATEST_COMMIT=`git ls-remote helmcharts | grep "refs/heads/master" | awk '{ print $1}'`
echo
echo "helmcharts latest commit: ${HELMCHARTS_LATEST_COMMIT}"
echo

# checkout source repo
#git checkout -b ${IMPORT_BRANCH} helmcharts/master

# create new staging branch from all the commits impacting "/my-chart" from source repo
#git subtree split -P my-chart -b ${STAGING_BRANCH}

# checkout master
#git checkout master

# take commits in the staging branch and set "/helm-charts/my-chart" as the commit root
# after you run this script the first time, update the command below to:
# "git subtree merge" with the same parameters
#
echo
echo "Add in changes"
echo -----------------------------------------
#git subtree add -P helm-charts/my-chart ${STAGING_BRANCH} --message "Update helmchart from https://github.com/icheko/helmcharts/commit/${HELMCHARTS_LATEST_COMMIT}"

# clean up
echo
echo
#git branch -D ${STAGING_BRANCH}
#git branch -D ${IMPORT_BRANCH}