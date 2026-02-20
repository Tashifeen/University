#include <stdio.h>
#include <string.h>

void replace_alice(const char *infile, const char *outfile, const char *fullname) {
	FILE *in = fopen(infile, "r");
	FILE *out = fopen(outfile, "w");

	if (!in || !out) {
		fprintf(stderr, "File error\n");
		return;
	}

	const char *target = "Alice";
	size_t tlen = strlen(target);
	size_t nlen = strlen(fullname);

	char line[4096];

	while (fgets(line, sizeof(line), in)) {
		char *p = line;

		while ((p = strstr(p, target))) {
			// Write everything BEFORE "Alice"
            fwrite(line, 1, p - line, out);

            // Write your full name
            fwrite(fullname, 1, nlen, out);

            // Move past "Alice"
            p += tlen;

            // Shift remainder of line to the front
            memmove(line, p, strlen(p) + 1);

            // Restart scanning from beginning of modified line
            p = line;
        }

        // Write whatever remains of the line
        fputs(line, out);
    }

    fclose(in);
    fclose(out);
}

int main(void) {
    replace_alice("alice.txt",
                  "alice_replaced.txt",
                  "Tashifeen Ahmad");
    return 0;
}
