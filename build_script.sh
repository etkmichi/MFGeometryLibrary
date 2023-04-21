#!/bin/bash

#Debug or Release
build_target=$1

#download and build other libraries found in git_repos variable
build_others=$2
project_name="MFGeometryLibrary"

#other libraries which are needed for this project
git_repos=(
    "https://github.com/etkmichi/MFBasics.git"
)
if [ "$build_others" == "yes" ]; then
    #iterate over others provided by git_repos clone them and execute the build_script
    echo "This build script will download and build other git repositiories!"

fi
#get directory of build script
directory=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

#Set environment variables
source $directory/setup_environment.sh

# echo $MF_PROJECTS_DIR
# echo $BULLET_PHYSICS_HEADERS

cd $directory
if [ "$build_target" == "h" -o "$build_target" == "help" -o "$build_target" == "-h" -o "$build_target" == "--help" ]; then
    echo "r|R|release|Release - create release build target"
    echo "d|D|debug|Debug - create debug build target"
    echo "c|C|clean|Clean - clean debug and release builds"
    exit 0
fi
case $build_target in
"r"|"R"|"release")build_target="Release";;
"d"|"D"|"debug")build_target="Debug";;
"c"|"C"|"clean")build_target="Clean";;
esac
while [ "$build_target" != "Debug" -a "$build_target" != "Release" -a "$build_target" != "Clean" ]
do
    echo "No build target defined!"
    echo "1==Debug  2==Release  3==clean  4==exit"
    read -p "" input_v
    case $input_v in
        "1")build_target="Debug";;
        "2")build_target="Release";;
        "3")build_target="Clean";;
        "4")exit 0;;
        *)
            echo "Invalid input!"
            $build_target="";;
    esac
done
if [ "$build_target" == "Clean" ]; then
    cd $directory/$project_name/Debug
    make clean
    cd $directory/$project_name/Release
    make clean
else
    echo "build target set to $build_target"
    cd $directory/$project_name/$build_target
    make all
fi