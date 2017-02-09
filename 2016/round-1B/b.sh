#!/bin/bash -x

dir="${0%/*}"

in="${1?1st param is the input filename}"

out="$dir"/"${in##*/}" # Replace directory within input filemane
out="${out%.in}".out   # Replace file extenstion

exe="$dir"/build/b

"$exe" < "$in" > "$out"
head "$out"

