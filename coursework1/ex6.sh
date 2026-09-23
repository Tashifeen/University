#!/bin/bash

# CW1 - Ex1: Converting XML to CSV using grep, sed and gawk
# How to run: ./ex1.sh input.xml output.csv

## STEP 2: INPUT ERROR HANDLING

xml="$1"
csv="$2"


# Checks if (input) arguments are missing
if [ -z "$xml" ] || [ -z "$csv" ]; then		# -z -> string is empty
    echo "Usage: $0 input.xml output.csv"
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
record=$(sed -n '2p' "$xml" | sed 's/[<>]//g')



## STEP 3: Main Processing with gawk ##

# Passing record tag into gawk
	# Source (gawk): https://medium.com/@redswitches/the-gawk-command-in-linux-with-10-examples-092900b06ca5
gawk -v rec="$record" '

	# gawk processing XML structure and generating CSV
	BEGIN {
    	RS = "<"        # RS = Record Sperator
    	FS = ">"        # FS = Field Seperator - split tag and value
    	depth = 0		# Check nesting level in XML (++ on opening tag, -- on closing tag)
    	in_rec = 0		# Detects if inside a record (e.g. <student>)?
    	first = 0		# Detecs if finished first record? -> builds column headers
    	ncol = 0
    	nrow = 0
	}

	{

		# Remove Windows cr characters
		gsub(/\r/, "", $0)

    	tag = $1	# Tag name (e.g. student name)
    	val = $2	# Tag value (e.g. Michael)

    	# Removing whitespace (leading and trailing) around tag
    	gsub(/^[ \t\n\r]+/, "", tag)
    	gsub(/[ \t\n\r]+$/, "", tag)

		# Remove newlines inside values (relevant for address tag which spans multiple lines)
    	gsub(/\n/, " ", val)
    	gsub(/\r/, "", val)
    	gsub(/^[ \t]+/, "", val)
	    gsub(/[ \t]+$/, "", val)

	    # skip empty tags and XML declaration
	    	# ~ means matches regex
	    if (tag == "" || tag ~ /^\?/) next

	    # Handle self-closing tag (e.g. <lecturer1/>)
	    if (tag ~ /\/$/) {
	    	# if tag (i.e. fieldname) ends with / -> store it as an empty value
	        if (in_rec) {
	            fname = tag
	            sub(/\/$/, "", fname)

				# Add column only when reading first record
	            if (!first && !(fname in idx)) {
	                ncol++
	                order[ncol] = fname
	                idx[fname] = ncol
	            }

				# Store empty value for this column
	            if (fname in idx)
	            	data[idx[fname]] = ""
	        }
	        next
	    }

	    # Handle closing tag (starts with /)
	    if (tag ~ /^\//) {
	        depth--

	        # record ends when depth returns to 1
	        if (depth == 1 && in_rec) {
	            in_rec = 0
	            first = 1
	            nrow++

	            line = ""
	            for (i = 1; i <= ncol; i++) {
	                v = data[i]
	                gsub(/"/, "\"\"", v)   # Escape quotes
	                line = line "\"" v "\""
	                if (i < ncol) line = line ","
	            }
	            rows[nrow] = line

	            for (i = 1; i <= ncol; i++) data[i] = ""
	        }
	        next
	    }

	    # Opening tag
	    curr = depth
	    depth++

	    # Record starts at depth 1
	    if (curr == 1 && tag == rec) {
	        in_rec = 1
	        for (i = 1; i <= ncol; i++) data[i] = ""
	        next
	    }

	    # Fields are depth 2 (inside record)
	    if (curr == 2 && in_rec) {
	        fname = tag

			# Add column names only from first record
	        if (!first && !(fname in idx)) {
	            ncol++
	            order[ncol] = fname
	            idx[fname] = ncol
	        }

	        if (fname in idx)
	        	data[idx[fname]] = val
	    }
	}

	END {
	    # Print header row
	    header = ""
	    for (i = 1; i <= ncol; i++) {
	        col = order[i]

	        if (col == "faculty") col = "name"   # Rename faculty column to name

	        header = header "\"" col "\""
	        if (i < ncol) header = header ","
	    }
	    print header

	    # Print data rows
	    for (r = 1; r <= nrow; r++)
	        print rows[r]
	}
	' > "$csv"

echo "Done. CSV written to $csv"
