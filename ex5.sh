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

# Detect record tag (second opening tag = what sits directly inside the outer container).
# We use grep with [a-zA-Z] so the <?xml ...?> declaration is automatically skipped.
RECORD_TAG=$(grep -oE '<[a-zA-Z][a-zA-Z0-9_]*>' "$XML_FILE" | sed -n '2p' | sed 's/[<>]//g')

# Strip Windows \r\n line endings to \n before passing to awk,
# then pass to awk which splits on "<" (RS="<").
# Each token is then: tag>value  or  /tag>  or  tag/>
# FS=">" splits into $1=tag and $2=value.
#
# Pure numeric depth tracking:
#   depth 1 = inside outer container
#   depth 2 = inside a record       (fields collected here)
# This correctly handles faculties.xml where <faculty> is both
# the record tag and a field name inside the record.

sed 's/\r//' "$XML_FILE" | awk -v record_tag="$RECORD_TAG" '
BEGIN {
    RS         = "<"
    FS         = ">"
    depth      = 0
    in_record  = 0
    first_done = 0
    n_fields   = 0
    n_records  = 0
}

{
    tag = $1
    val = $2

    # Strip leading/trailing whitespace and newlines from tag
    gsub(/^[ \t\n\r]+/, "", tag)
    gsub(/[ \t\n\r]+$/, "", tag)

    # Strip newlines from val immediately (handles multiline values e.g. address)
    gsub(/\n/, " ", val)
    gsub(/\r/, "",  val)
    gsub(/^[ \t]+/, "", val)
    gsub(/[ \t]+$/, "", val)

    # Skip empty tokens and XML declaration <?xml ... ?>
    if (tag == "" || tag ~ /^\?/) next

    # Self-closing tag e.g. <lecturer1/> - no depth change
    if (tag ~ /\/$/) {
        if (in_record) {
            field_name = tag
            gsub(/\/$/, "", field_name)
            if (!first_done && !(field_name in field_index)) {
                n_fields++
                field_order[n_fields] = field_name
                field_index[field_name] = n_fields
            }
            if (field_name in field_index) vals[field_index[field_name]] = ""
        }
        next
    }

    # Closing tag - decrement depth
    if (tag ~ /^\//) {
        depth--
        # Record ends when depth drops back to 1
        if (depth == 1 && in_record) {
            in_record  = 0
            first_done = 1
            n_records++
            row = ""
            for (i = 1; i <= n_fields; i++) {
                v = vals[i]
                gsub(/"/, "\"\"", v)
                row = row "\"" v "\""
                if (i < n_fields) row = row ","
            }
            rows[n_records] = row
            for (i = 1; i <= n_fields; i++) vals[i] = ""
        }
        next
    }

    # Opening tag - check depth BEFORE incrementing
    current_depth = depth
    depth++

    # Record opens at depth 1 (directly inside outer container)
    if (current_depth == 1 && tag == record_tag) {
        in_record = 1
        for (i = 1; i <= n_fields; i++) vals[i] = ""
        next
    }

    # Fields are at depth 2 (directly inside a record)
    if (current_depth == 2 && in_record) {
        field_name = tag
        if (!first_done && !(field_name in field_index)) {
            n_fields++
            field_order[n_fields] = field_name
            field_index[field_name] = n_fields
        }
        if (field_name in field_index) vals[field_index[field_name]] = val
    }
}

END {
    # Print header - quoted, rename "faculty" field to "name"
    header = ""
    for (i = 1; i <= n_fields; i++) {
        col = field_order[i]
        if (col == "faculty") col = "name"
        header = header "\"" col "\""
        if (i < n_fields) header = header ","
    }
    print header

    # Print all data rows
    for (r = 1; r <= n_records; r++) print rows[r]
}
' > "$CSV_FILE"

echo "Done. Output written to $CSV_FILE"
