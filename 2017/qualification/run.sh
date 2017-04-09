#!/bin/bash -x

dir="${0%/*}"                # Directory where this script is
exe="$dir"/build/"${0##*/}"  # Deduce executable from the script filename

in="${1?1st param is the input filename}"

out="$dir"/"${in##*/}" # Replace directory within input filemane
out="${out%.in}".out   # Replace file extenstion

"$exe" < "$in" > "$out"
head "$out"

