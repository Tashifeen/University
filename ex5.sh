#!/bin/bash

# Ex1: Convert XML file to CSV using grep, sed, and awk
# Usage: ./ex1.sh input.xml output.csv

XML_FILE="$1"
CSV_FILE="$2"

if [ -z "$XML_FILE" ] || [ -z "$CSV_FILE" ]; then
    echo "Usage: $0 <input.xml> <output.csv>"
    exit 1
fi

if [ ! -f "$XML_FILE" ]; then
    echo "Error: File '$XML_FILE' not found."
    exit 1
fi

# Detect record tag (student or faculty)
if grep -q "<student>" "$XML_FILE"; then
    RECORD_TAG="student"
else
    RECORD_TAG="faculty"
fi

# By setting RS="<" awk splits the file on every "<" character.
# Each record then looks like one of:
#   "tag>value"        (opening tag with value)
#   "/tag>..."         (closing tag)
#   "tag/>..."         (self-closing tag)
# FS=">" splits each token into $1 (tag name or "tag/") and $2 (value after ">" )
#
# Pass 1: scan the FIRST record block to get the ordered field list.
# Pass 2: extract values for every record and write CSV rows.

awk -v record_tag="$RECORD_TAG" '
BEGIN {
    RS = "<"
    FS = ">"
    in_record  = 0
    first_done = 0   # have we finished scanning the first record?
    n_fields   = 0
    n_records  = 0
}

{
    tag = $1
    val = $2

    # Strip any trailing whitespace/newlines from tag and val
    gsub(/^[ \t\n\r]+/, "", tag)
    gsub(/[ \t\n\r]+$/, "", tag)
    gsub(/^[ \t\n\r]+/, "", val)
    gsub(/[ \t\n\r]+$/, "", val)

    # --- detect record boundaries ---
    if (tag == record_tag) {
        in_record = 1
        # initialise per-record value storage
        for (i = 1; i <= n_fields; i++) vals[i] = ""
        next
    }

    if (tag == "/" record_tag) {
        if (in_record) {
            in_record  = 0
            first_done = 1
            n_records++
            # store this record row for later printing
            row = ""
            for (i = 1; i <= n_fields; i++) {
                v = vals[i]
                gsub(/"/, "\"\"", v)   # escape double quotes
                row = row "\"" v "\""
                if (i < n_fields) row = row ","
            }
            rows[n_records] = row
            for (i = 1; i <= n_fields; i++) vals[i] = ""
        }
        next
    }

    if (!in_record) next

    # --- inside a record ---

    # Self-closing tag: ends with "/"  e.g. tag = "lecturer1/"
    if (tag ~ /\/$/) {
        field_name = tag
        gsub(/\/$/, "", field_name)   # strip trailing /
        # register field if not seen before (and still in first record)
        if (!first_done && !(field_name in field_index)) {
            n_fields++
            field_order[n_fields] = field_name
            field_index[field_name] = n_fields
        }
        # value is empty for self-closing
        if (field_name in field_index) vals[field_index[field_name]] = ""
        next
    }

    # Closing tag: starts with "/"  e.g. tag = "/student_name"
    if (tag ~ /^\//) next

    # Opening tag with value
    field_name = tag
    if (!first_done && !(field_name in field_index)) {
        n_fields++
        field_order[n_fields] = field_name
        field_index[field_name] = n_fields
    }
    if (field_name in field_index) vals[field_index[field_name]] = val
}

END {
    # Print header
    header = ""
    for (i = 1; i <= n_fields; i++) {
        header = header field_order[i]
        if (i < n_fields) header = header ","
    }
    print header

    # Print all rows
    for (r = 1; r <= n_records; r++) print rows[r]
}
' "$XML_FILE" > "$CSV_FILE"

echo "Done. Output written to $CSV_FILE"
