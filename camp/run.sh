#!/usr/bin/env bash
# Usage: ./run.sh [ll|st|qu|LL-6|mock]
set -e
root="$(cd "$(dirname "$0")" && pwd)"
mkdir -p "$root/build"
g++ -std=c++17 -Wall -g -O0 "$root/tests/main.cpp" -o "$root/build/camp" \
  || { echo -e "\nCompile error (see above)."; exit 1; }
"$root/build/camp" "$@"
