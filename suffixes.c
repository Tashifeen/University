/* When compiling include -lm like this:
	gcc suffixes.c -lm
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
	int base;
	char suffix[3];		// enough for "da" + '\0'
	int power;			// power of 10 result

	printf("Type a number and suffix: ");

	scanf("%d %s", &base, suffix);

	// https://people.bath.ac.uk/ensdasr/SI.prefixes.pdf

	// Handle 2-letter prefix first: "da" (deka)
	if (strcmp(suffix, "da") == 0) {
		power = 1;	// 10^1
	}
	else {
		// Use first character for switch

		switch (suffix[0]) {
            case 'Y': power = 24; break;    // yotta
            case 'Z': power = 21; break;    // zetta
            case 'E': power = 18; break;    // exa
            case 'P': power = 15; break;    // peta
            case 'T': power = 12; break;    // tera
            case 'G': power = 9;  break;    // giga
            case 'M': power = 6;  break;    // mega
            case 'k': power = 3;  break;    // kilo
            case 'h': power = 2;  break;    // hecto

            case 'd': power = -1; break;    // deci
            case 'c': power = -2; break;    // centi
            case 'm': power = -3; break;    // milli
            case 'u': power = -6; break;    // micro (ASCII version of μ)
            case 'n': power = -9; break;    // nano
            case 'p': power = -12; break;   // pico
            case 'f': power = -15; break;   // femto
            case 'a': power = -18; break;   // atto
            case 'z': power = -21; break;   // zepto
            case 'y': power = -24; break;   // yocto

			default:
				printf("Unknown suffix\n");
				return 1;
		}
	}
	double output = base * pow(10, power);
	printf("%f", output);
}
