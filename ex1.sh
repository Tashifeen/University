#!/usr/bin/env bash
set -euo pipefail

# Usage: ./ex1.sh input.xml output.csv
in="${1:-}"
out="${2:-}"

if [[ -z "$in" || -z "$out" ]]; then
  echo "Usage: $0 input.xml output.csv" >&2
  exit 1
fi

if [[ ! -f "$in" ]]; then
  echo "Error: input file not found: $in" >&2
  exit 1
fi

python3 - "$in" "$out" <<'PY'
import sys, csv
import xml.etree.ElementTree as ET

in_path = sys.argv[1]
out_path = sys.argv[2]

tree = ET.parse(in_path)
root = tree.getroot()

# Records are the direct children under the root, e.g. <student>...</student> or <faculty>...</faculty>
records = list(root)
if not records:
    # Write empty output with no header if no records
    open(out_path, "w", newline="", encoding="utf-8").close()
    sys.exit(0)

# Header: use the first record's child tags in order, then add any new tags seen later (in first-seen order)
header = []
seen = set()

def add_field(tag):
    if tag not in seen:
        seen.add(tag)
        header.append(tag)

# Get initial header order from first record
for child in list(records[0]):
    add_field(child.tag)

# Add any extra fields found in other records
for rec in records[1:]:
    for child in list(rec):
        add_field(child.tag)

def clean_text(x):
    if x is None:
        return ""
    # Collapse internal whitespace/newlines to spaces
    return " ".join(x.split())

with open(out_path, "w", newline="", encoding="utf-8") as f:
    w = csv.writer(f, quoting=csv.QUOTE_ALL)

    # header row
    w.writerow(header)

    # data rows
    for rec in records:
        row = []
        for tag in header:
            elem = rec.find(tag)
            row.append(clean_text(elem.text) if elem is not None else "")
        w.writerow(row)
PY
