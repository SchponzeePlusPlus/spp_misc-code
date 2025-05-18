#!/bin/bash
SOURCE_BRANCH="helmcharts-source"
STAGING_BRANCH="helmcharts-staging"

echo
echo "Fetch new changes from helmcharts"
echo -----------------------------------------
git fetch helmcharts master

HELMCHARTS_LATEST_COMMIT=`git ls-remote helmcharts | grep "refs/heads/master" | awk '{ print $1}'`
echo
echo "helmcharts latest commit: ${HELMCHARTS_LATEST_COMMIT}"
echo

# checkout source repo
git checkout -b ${SOURCE_BRANCH} helmcharts/master

# create new staging branch from all the commits impacting "/my-chart" from source repo
git subtree split -P my-chart -b ${STAGING_BRANCH}

# checkout master
git checkout master

# take commits in the staging branch and set "/helm-charts/my-chart" as the commit root
# after you run this script the first time, update the command below to:
# "git subtree merge" with the same parameters
#
echo
echo "Add in changes"
echo -----------------------------------------
git subtree add -P helm-charts/my-chart ${STAGING_BRANCH} --message "Update helmchart from https://github.com/icheko/helmcharts/commit/${HELMCHARTS_LATEST_COMMIT}"

# clean up
echo
echo
git branch -D ${STAGING_BRANCH}
git branch -D ${SOURCE_BRANCH}