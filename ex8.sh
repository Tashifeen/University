#!/bin/bash
# How to run: ./ex1.sh input.xml output.csv
# STEP 1: INPUT ERROR HANDLING
xml="$1"
csv="$2"
# Checks if (input) arguments are missing
if [ -z "$xml" ] || [ -z "$csv" ]; then
    echo "Usage: $0 input.xml output.csv"	# -z -> string is empty
    exit 1
fi
# Check if (input) XML file exists
if [ ! -f "$xml" ]; then
    echo "Error: File not found."
    exit 1
fi
## STEP 2: Detecting the Record Tag ##
# Finding record (<student> or <faculty>) tag
#	i.e. 2nd opening tag in file
record=$(grep -oE '<[a-zA-Z][a-zA-Z0-9_]*>' "$xml" \
         | sed -n '2p' \
         | sed 's/[<>]//g')
## STEP 3: Main Processing with gawk ##
# Passing record tag into gawk
        # Source: https://medium.com/@redswitches/the-gawk-command-in-linux-with-10-examples-092900b06ca5
gawk -v rec="$record" '
	# gawk being used for processing XML structure and generating CSV
	BEGIN {
	    RS="<"          # RS = Record Seperator, "<" starts a new chunk
	    FS=">"          # FS = Field Seperator, Splitting tag and value at ">"
	    in_rec=0        # Are we inside a record? (0=no, 1=yes)
	    first=1         # First record -> used for header
	    depth=0         # FIX: nesting level so <faculty> field inside <faculty>
	                    # record does not confuse record start/end detection
	}
	{
		# 1. Remove Windows cr characters
	    gsub(/\r/, "", $0)
	    tag=$1		# Tag name
	    val=$2		# Tag value
		# 2. Remove whitespaces around tag
	    gsub(/^[ \t\n]+/, "", tag)
	    gsub(/[ \t\n]+$/, "", tag)
	    # Remove newlines inside value (relevant for address spanning multiple lines)
	    gsub(/\n/, " ", val)
	    # Skip empty tokens and XML declaration
	    if (tag == "" || tag ~ /^\?/) next
	    # FIX: self-closing tag e.g. <lecturer1/> -> empty field, no depth change
	    if (tag ~ /\/$/) {
	        if (in_rec) {
	            field=tag; gsub(/\/$/, "", field)
	            if (first) header = (header=="" ? "\"" field "\"" : header ",\"" field "\"")
	            row = (row=="" ? "\"\"" : row ",\"\"")
	        }
	        next
	    }
	    # FIX: closing tag -> decrement depth, only end record when back at depth 1
	    if (tag ~ /^\//) {
	        depth--
	        if (tag == "/"rec && depth == 1) {
	            if (first) { print header; first=0 }
	            print row
	            in_rec=0
	        }
	        next
	    }
	    # FIX: opening tag -> only start record at depth 1
	    if (tag == rec && depth == 1) {
	        in_rec=1; row=""; depth++; next
	    }
	    depth++
	    # 5. Field inside record
	    if (in_rec && tag != "" && tag !~ /^\//) {
	        # Building header from first record only
	        if (first) {
	            if (header == "")
	                header="\"" tag "\""
	            else
	                header=header ",\"" tag "\""
	        }
	        val="\"" val "\""
	        if (row == "")
	            row=val
	        else
	            row=row "," val
	    }
	}
	' "$xml" > "$csv"
echo "Let's go! Output has been written to $csv"
