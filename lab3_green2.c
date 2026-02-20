#include <stdio.h>
#include <string.h>

static char whichanimal[50];

#define FN_NAME(SUFFIX) fn_##SUFFIX
/* Your PRINT_HANDLE macro definition goes here. */
#define PRINT_HANDLE(ANIMAL)			\
	void FN_NAME(ANIMAL)(void) {		\
		strcpy(whichanimal, #ANIMAL);	\
	}

PRINT_HANDLE(robin)
PRINT_HANDLE(tortoise)
PRINT_HANDLE(flying_pig)
int main(void)
{
    fn_robin();
    printf("%s\n", whichanimal);  /* robin */
    fn_tortoise();
    printf("%s\n", whichanimal);  /* tortoise */
    fn_flying_pig();
    printf("%s\n", whichanimal);  /* flying_pig */
}
