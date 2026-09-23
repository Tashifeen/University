#include <stdio.h>
#include <ctype.h>

struct result
{
    unsigned hits;
    unsigned misses;
    int rc;
};

struct result find_words_with_chars(char const *const path, char const search) {
        struct result r1 = {0, 0, 0};
        FILE *f = fopen(path, "r");

        // If 'path' cannot be opened
        if (!f) {
        r1.rc = 1;
        return r1;
        }

        int c;
        int in_word = 0; // Bool
        int found = 0; // Bool -  if letter found set to 1
        while ((c = fgetc(f)) != EOF) {
                printf("%d", c);
        if (isalpha(c)) {
                // New word
            if (!in_word) {
                in_word = 1;
                found = 0;
            }
            // Found letter
            if (c == search) {
                printf("%d", found);
                found = 1;
            }
        } else {
            if (in_word) {
                if (found)
                    r1.hits++;
                else
                    r1.misses++;
            }
            in_word = 0;
        }
    }

        // Handling last word if file doesn't end with space
    if (in_word) {
        if (found)
            r1.hits++;
        else
            r1.misses++;
    }
    fclose(f);
        return r1;
}

int main(void)
{
    struct result r;
    r = find_words_with_chars("lab3.txt" /* This document! */, 'o');
    printf("%u:%u, ret: %d\n", r.hits, r.misses, r.rc);
    /* Prints "242:707 ret: 0" */

    r = find_words_with_chars("lab3.txt", 'j');
    printf("%u:%u, ret: %d\n", r.hits, r.misses, r.rc);
    /* Prints "1:948 ret: 0" */

    r = find_words_with_chars("this_file_does_not_exist", 'e');
    printf("%u:%u, ret: %d\n", r.hits, r.misses, r.rc);
    /* Prints "0:0 ret: 1" */

    return 0;
}
