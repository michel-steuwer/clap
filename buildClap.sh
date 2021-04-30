#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

function check_command() {
  echo -ne "Checking for ${1}... "
  if ! type "$1" > /dev/null; then
    echo "[failed]"
    echo "Missing command $1" >&2
    exit -1
  fi
  echo "[ok]"
}

function configure() {
  check_command "cmake"
  check_command "c++"

  mkdir -p $DIR/build
  (cd $DIR/build && cmake -DTRACK_EVENTS=ON ..)
}

function build() {
  check_command "cmake"
  check_command "c++"

  (cd $DIR/build &&  make -j 8)
}

echo "Configure clap"
configure

echo "Build clap"
build
