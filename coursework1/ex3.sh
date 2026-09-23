#!/bin/bash
# ex1.sh - XML (students/faculties) -> CSV using basic grep/sed/awk
# Usage: ./ex1.sh input.xml output.csv

if [ $# -ne 2 ]; then
  echo "Usage: $0 input.xml output.csv"
  exit 1
fi

input="$1"
output="$2"

if [ ! -f "$input" ]; then
  echo "File not found: $input"
  exit 1
fi

# Decide which record tag we are using (student or faculty)
if grep -q "<student>" "$input"; then
  rec="student"
elif grep -q "<faculty>" "$input"; then
  rec="faculty"
else
  echo "Could not find <student> or <faculty> records in $input"
  exit 1
fi

# ---- Build header from the FIRST record only (keeps order, avoids junk tags) ----
header=$(
  awk -v rec="$rec" '
    BEGIN { inside=0 }
    $0 ~ "<"rec">" { inside=1; next }
    inside && $0 ~ "</"rec">" { exit }
    inside {
      # get lines like <tag>...</tag> or <tag/>
      if ($0 ~ /^[ \t]*<[^\/!?][^>]*>/) {
        line=$0
        gsub(/^[ \t]*</, "", line)   # remove leading "<"
        gsub(/>.*/, "", line)        # keep only tag name part
        gsub(/\/$/, "", line)        # remove trailing "/" from <tag/>
        if (line != rec && line != "" && !(seen[line]++)) {
          print line
        }
      }
    }
  ' "$input" | paste -sd ","
)

# Write header row
echo "$header" > "$output"

# ---- Extract rows ----
awk -v rec="$rec" -v header="$header" '
BEGIN {
  FS="[<>]"
  OFS=","
  n = split(header, fields, ",")
}

# Start of record
$0 ~ "<"rec">" { inside=1; next }

# End of record -> print row
inside && $0 ~ "</"rec">" {
  for (i=1; i<=n; i++) {
    key = fields[i]
    val = (key in data ? data[key] : "")

    # remove newlines inside fields (just in case)
    gsub(/\r/, "", val)
    gsub(/\n/, " ", val)

    # CSV quote everything, escape quotes
    gsub(/"/, "\"\"", val)
    printf "\"%s\"%s", val, (i<n ? OFS : ORS)
  }
  delete data
  inside=0
  next
}

# Inside record: handle <tag>value</tag>
inside && $2 != "" && $3 != "" {
  tag = $2
  val = $3
  if (tag != rec) data[tag] = val
  next
}

# Inside record: handle empty tag like <lecturer1/>
inside && $0 ~ /^[ \t]*<[^\/!?][^>]*\/>[ \t]*$/ {
  line=$0
  gsub(/^[ \t]*</, "", line)
  gsub(/\/>.*/, "", line)   # remove "/>"
  tag=line
  if (tag != rec) data[tag] = ""
}
' "$input" >> "$output"

echo "Created $output"
