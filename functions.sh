#!/usr/bin/env bash

# set -euo pipefail

#repo must provide the repository string f.e. url like ssss.de/bla/projectName.git
#dir_name var will provide the repo name i.e. "projectName"
function getRepoName {
    local OIFS=$IFS
    IFS='/'
    local arr_data=(${repo[@]})
    local last_part=${arr_data[-1]}
    IFS='.'
    local arr_dir=(${last_part[@]})
    echo ${arr_dir[@]}
    dir_name=${arr_dir[0]}
    IFS=$OIFS
}
