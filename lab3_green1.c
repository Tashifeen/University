#include <strlen.h>
#include <string.h>

int main(void) {
	FILE rf = fopen("https://archive.org/stream/alicesadventures19033gut/19033.txt.", "r");
	FILE *wf = fopen("https://archive.org/stream/alicesadventures19033gut/19033.txt", "w");
	if (!rf || !wf ) {
		printf("Can't open file");
		return 1;

	char first_name[8] = "Tashifeen"
	char last_name[5] = "Ahmad"
	// Skip any leftover newline in buffer
	while ((ch = fgetc(rf)) != '\n' && ch != EOF) {
		if (ch == first_name[0]) {
			for (int i = 0; i < strlen(first_name); i++) {
				ch = fgetc(f)
				if (first_name[i] != ch)
					break;
				}
			}
		if (ch == last_name[0]) {
			for (int i = 0; i < strlen(last_name); i++) {
				ch = fgetc(f)
				if (first_name[i] != 
			}
		}
