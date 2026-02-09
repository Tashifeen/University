#!/bin/bash

# Check for input file
if [[ -z "$1" ]]; then
    echo "Usage: $0 <input.xml> [output.csv]"
    exit 1
fi

input_xml="$1"
output_csv="${2:-${input_xml%.xml}.csv}"

# Extract unique tags (excluding XML declaration and root tags)
tags=$(grep -oP '<\K[^/>]+(?=>[^<]+</[^>]+>)' "$input_xml" | grep -vP '^(faculties|students|\?xml)' | sort | uniq | tr '\n' ',' | sed 's/,$//')

# Create CSV header
echo "$tags" > "$output_csv"

# Process data records
awk -v tags="$tags" '
    BEGIN {
        FS="[<>]"
        OFS=","
        split(tags, header, /,/)
        gsub(/ /, "", header[1])  # Remove any accidental spaces
    }
    /<faculty>/,/<\/faculty>/ || /<student>/,/<\/student>/ {
        if ($2 in header) values[$2] = $3
        if ($0 ~ /<\/faculty>|<\/student>/) {
            for (i=1; i<=length(header); i++) {
                printf "%s%s", (header[i] in values ? values[header[i]] : ""), (i<length(header) ? OFS : ORS)
            }
            delete values
        }
    }
' "$input_xml" >> "$output_csv"

echo "CSV generated: $output_csv"
