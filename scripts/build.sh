#!/bin/bash

build_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/../build"

mkdir "${build_path}"

cd "${build_path}"

if [ "$1" = "debug" ]; then
    cmake .. -DDEBUG=on
else
    cmake ..
fi

make

cp -r ../example/* .

if [ "$1" = "run" ] || [ "$2" = "run" ]; then
    "${build_path}"/CTCP
fi
