#!/bin/bash
# ex1.sh – Convert an XML file to CSV using only sed, awk, and grep
# Usage: ./ex1.sh <input.xml> [output.csv]

set -euo pipefail

# --- Command line arguments ---
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

# --- Build the CSV header ---
# 1. Find all lines that look like <tag>text</tag> (leaf elements with simple content)
# 2. Extract the tag name (the part between < and >)
# 3. Remove the XML declaration and the root container tag (if they accidentally slip in)
# 4. Sort, deduplicate, and join with commas
header="$(
    grep -o '<[^/>]\+>[^<]\+</[^/>]\+>' "$input_xml" \
        | sed -e 's/^<\([^/>]\+\)>.*/\1/' \
        | grep -v -E '^(students|\?xml)$' \
        | sort -u \
        | paste -sd ','
)"

if [[ -z "$header" ]]; then
    echo "No simple <tag>text</tag> elements found in $input_xml"
    exit 1
fi

# Write the header to the output file
echo "$header" > "$output_csv"

# --- Extract data rows from each <student> block ---
awk -v tags="$header" '
BEGIN {
    FS = "[<>]"               # split lines at < or >
    OFS = ","
    n = split(tags, header, /,/)
    for (i = 1; i <= n; i++) {
        gsub(/^ +| +$/, "", header[i])   # trim possible spaces in tag names
    }
}

# Inside a <student> block
/<student>/, /<\/student>/ {

    # Lines like: <name>Alice</name>  -> $2 = "name", $3 = "Alice"
    if ($2 ~ /^[A-Za-z0-9_:-]+$/ && $3 != "" && $0 !~ /<\/?student>/) {
        values[$2] = $3
    }

    # At the end of a student, output one CSV row
    if ($0 ~ /<\/student>/) {
        for (i = 1; i <= n; i++) {
            key = header[i]
            out = (key in values ? values[key] : "")

            # Escape double quotes by doubling them; wrap in quotes if field contains comma or quote
            gsub(/"/, "\"\"", out)
            if (out ~ /[,"]/)
                printf "\"%s\"%s", out, (i < n ? OFS : ORS)
            else
                printf "%s%s", out, (i < n ? OFS : ORS)
        }
        delete values
    }
}
' "$input_xml" >> "$output_csv"

echo "CSV generated: $output_csv"
