#!/usr/bin/env bash
# Usage: ./run.sh L01 [L01-B] [--solution]
set -e
root="$(cd "$(dirname "$0")" && pwd)"
lab="" only="" solution=0
for a in "$@"; do
  case "$a" in
    --solution) solution=1 ;;
    *) if [ -z "$lab" ]; then lab="$a"; else only="$a"; fi ;;
  esac
done
if [ -z "$lab" ]; then
  echo "Labs:"; for d in "$root"/week*/[LCP][0-9][0-9]-*/; do echo "  $(basename "$d")"; done; exit 0
fi
prefix=L; case "$lab" in [cC]*) prefix=C;; [pP]*) prefix=P;; esac
num=$(echo "$lab" | tr -cd '0-9'); id=$(printf "%s%02d" "$prefix" "$((10#$num))")
dir=$(ls -d "$root"/week*/"$id"-*/ 2>/dev/null | head -1)
[ -n "$dir" ] || { echo "No lab named $id"; exit 1; }
srcs=()
for f in "$dir"*.cpp; do
  name=$(basename "$f"); [[ "$name" == warmup* || "$name" == main* ]] && continue
  if [ $solution = 1 ] && [ -f "$root/solutions/$id/$name" ]; then srcs+=("$root/solutions/$id/$name"); else srcs+=("$f"); fi
done
srcs+=("$dir"tests/*.cpp "$root/framework/main.cpp")
mkdir -p "$root/build"
exe="$root/build/$id$([ $solution = 1 ] && echo -solution)"
solinc=(); [ $solution = 1 ] && solinc=(-I"$root/solutions/$id")
g++ -std=c++17 -Wall -Wextra -Wno-unused-parameter -g -O0 "${solinc[@]}" -I"$dir" -I"$root/framework" "${srcs[@]}" -o "$exe" \
  || { echo -e "\nCompile error (see above)."; exit 1; }
"$exe" $only
