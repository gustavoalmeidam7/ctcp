#!/bin/bash

build_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/../build"

if [ "$1" = "debug" ]; then
  echo "${build_path}"
else
  rm -r "${build_path}"
fi
