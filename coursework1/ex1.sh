#!/bin/bash
# ex1.sh — Convert a simple students.xml -> students.csv
# Usage: ./ex1.sh students.xml [students.csv]

set -euo pipefail

# 1) Args
if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <input.xml> [output.csv]"
  exit 1
fi

input_xml="$1"
output_csv="${2:-${input_xml%.xml}.csv}"

if [[ ! -f "$input_xml" ]]; then
  echo "Input file not found: $input_xml"
  exit 1
fi

# 2) Build a unique, comma-separated header of child tag names that look like <tag>text</tag>
#    - Excludes root/container tags like 'students' and XML declaration
#    - Requires GNU grep (-P)
tags="$(
  grep -oP '<\K[^/][^>]*(?=>[^<]+</[^>]+>)' "$input_xml" \
    | grep -vP '^(students|\?xml)$' \
    | sort -u \
    | paste -sd,
)"

if [[ -z "$tags" ]]; then
  echo "No simple <tag>text</tag> elements found in $input_xml"
  exit 1
fi

# 3) Write header
echo "$tags" > "$output_csv"

# 4) Stream students into rows
#    - Extract values from each <student> ... </student> block
#    - Output columns in the order given by $tags
awk -v tags="$tags" '
BEGIN {
  FS = "[<>]"
  OFS = ","
  n = split(tags, header, /,/)
  for (i=1; i<=n; i++) gsub(/^ +| +$/, "", header[i])   # trim spaces in header names
}

# Process only within <student> ... </student>
/<student>/,/<\/student>/ {

  # For a line like: <name>Alice</name>
  #   $2 = name
  #   $3 = Alice
  # guard against empty $2/$3 and skip container/open/close markers
  if ($2 ~ /^[A-Za-z0-9_:-]+$/ && $3 != "" && $0 !~ /<\/?student>/) {
    values[$2] = $3
  }

  # When we reach the end of a student block, print a row
  if ($0 ~ /<\/student>/) {
    for (i=1; i<=n; i++) {
      key = header[i]
      out = (key in values ? values[key] : "")
      # escape any embedded quotes by doubling them, wrap in quotes if containing comma or quote
      gsub(/"/, "\"\"", out)
      if (out ~ /[,"]/)
        printf "\"%s\"%s", out, (i<n ? OFS : ORS)
      else
        printf "%s%s", out, (i<n ? OFS : ORS)
    }
    delete values
  }
}
' "$input_xml" >> "$output_csv"

echo "CSV generated: $output_csv"
