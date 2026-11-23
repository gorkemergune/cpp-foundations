#!/usr/bin/env bash
# Usage: ./run.sh [ll|st|qu|LL-6|mock] [--solution]
set -e
root="$(cd "$(dirname "$0")" && pwd)"
main="$root/tests/main.cpp"; exe="$root/build/camp"; filter=""
for a in "$@"; do
  if [ "$a" = "--solution" ]; then main="$root/solutions/main.cpp"; exe="$root/build/camp-solution"; else filter="$a"; fi
done
mkdir -p "$root/build"
g++ -std=c++17 -Wall -g -O0 "$main" -o "$exe" || { echo -e "\nCompile error (see above)."; exit 1; }
"$exe" $filter
