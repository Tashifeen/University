#!/bin/bash
# ex1.sh
# Convert students.xml OR faculties.xml to CSV
# Usage: ./ex1.sh input.xml output.csv

if [ $# -ne 2 ]; then
    echo "Usage: $0 input.xml output.csv"
    exit 1
fi

input="$1"
output="$2"

if [ ! -f "$input" ]; then
    echo "File not found!"
    exit 1
fi

# Detect record type
if grep -q "<student>" "$input"; then
    record="student"
elif grep -q "<faculty>" "$input"; then
    record="faculty"
else
    echo "No student or faculty records found."
    exit 1
fi

# -------------------------
# Step 1: Build header
# -------------------------
header=$(grep -o "<[^/][^>]*>[^<]*</[^>]*>" "$input" \
    | sed 's/^<\([^>]*\)>.*$/\1/' \
    | grep -v -E "students|faculties" \
    | paste -sd ",")

# -------------------------
# Step 2: Extract records
# -------------------------
gawk -v rec="$record" -v header="$header"
BEGIN {
    FS="[<>]"
    OFS=","
    n=split(header, fields, ",")
}

# Start of record
$0 ~ "<"rec">" {
    inside=1
    next
}

# End of record -> print row
$0 ~ "</"rec">" {
    for(i=1;i<=n;i++){
        key=fields[i]
        val = (key in data ? data[key] : "")

        # remove newlines
        gsub(/\r/,"",val)
        gsub(/\n/," ",val)

        # quote everything
        gsub(/"/,"\"\"",val)
        printf "\"%s\"%s", val, (i<n?OFS:ORS)
    }
    delete data
    inside=0
    next
}

# ----------------------------
# MULTI-LINE ADDRESS HANDLING
# ----------------------------
inside && $0 ~ "<address>" {

    tag="address"
    val=""

    # remove opening tag
    sub(/.*<address>/,"",$0)
    val=$0

    # keep reading until closing tag
    while ($0 !~ "</address>") {
        getline
        val = val " " $0
    }

    # remove closing tag
    sub("</address>.*","",val)

    data[tag]=val
    next
}

# ----------------------------
# Normal one-line tags
# ----------------------------
inside && $0 ~ "<[^/].*</" {
    tag=$2
    val=$3
    data[tag]=val
    next
}

# ----------------------------
# Empty tags like <contact/>
# ----------------------------
inside && $0 ~ "/>" {
    tag=$2
    data[tag]=""
}
' "$input" >> "$output"
