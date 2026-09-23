#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

unsigned toggle_case(char *str) {
	unsigned count;

	for (int i = 0; str[i] != '\0'; i++) {
		// Only altering charcters (not digits!)
		if (isalpha(str[i])){
			// Convert uppercase to lowecase
			if (isupper(str[i])) {
				str[i] = tolower(str[i]);		
			}
			// Convert lowercase ->upper
			else {
				str[i] = toupper(str[i]);
			}
			count++;
		} 
	}
	return count;
}

int main(void) {
	char str[] = "1a2B3c";
	toggle_case(str);
	printf("%s", str);
	return 0;
}
