#!/bin/bash

# How to run: ./ex1.sh input.xml output.csv

# STEP 1: INPUT ERROR HANDLING

xml="$1"
csv="$2"

# Checks if (input) arguments are missing (https://linuxsimply.com/bash-scripting-tutorial/conditional-statements/if-else/if-string-not-empty/)
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
	    in_rec=0        # Are we are inside a record (e.g. <student>)? (0=no, 1=yes)
	    first=1         # First record -> used for header
	}

	{
		# 1. Remove Windows cr characters
	    gsub(/\r/, "", $0)

	    tag=$1		# Tag name (e.g. studnet name)
	    val=$2		# Tag value (e.g. Michael)

		# 2. Remove whitespaces
		# Around tag
	    gsub(/^[ \t\n]+/, "", tag)
	    gsub(/[ \t\n]+$/, "", tag)
	    # Remove newlines (relevant for address tag which spans multiple lines)
	    gsub(/\n/, " ", val)

	    # 3. Detecting start of record (e.g. <student>)
	    if (tag == rec) {
	        in_rec=1
	        row=""
	        next # https://opensource.com/article/19/12/control-awk-script
	    }

	    # 4. Detecting end of record (e.g. </student>)
	    if (tag == "/"rec) {
	        if (first) {
	            print header
	            first=0
	        }
	        print row
	        in_rec=0
	        next
	    }

	    # 5. Field inside record
	    if (in_rec && tag != "" && tag !~ /^\//) { # ~ -> Source: https://man7.org/linux/man-pages/man1/gawk.1.html#:~:text=The%20basic%20idea%20is%20that,assigned%20have%20regular%20expression%20type.

	        # Building header from first record only
	        if (first) {
	            if (header == "") # First header (e.g. student_name)
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
