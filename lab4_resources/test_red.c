#define _XOPEN_SOURCE  /* for popen and pclose */
#include <stdio.h>
#include "unity.h"
unsigned fib(unsigned n)
{
	unsigned fib[3] = {0, 1, 1};
	if (!n) return 0;
	while (n--)
	{
		fib[2] = fib[0] + fib[1];
		fib[0] = fib[1];
		fib[1] = fib[2];
	}
	return fib[1];
}

void setUp(void){}
void tearDown(void){}

void test_small_fibs(void)
{
    TEST_ASSERT_EQUAL_UINT(0, fib(0x0));
    TEST_ASSERT_EQUAL_UINT(1, fib(0x1));
    TEST_ASSERT_EQUAL_UINT(1, fib(0x2));
    TEST_ASSERT_EQUAL_UINT(2, fib(0x3));
    TEST_ASSERT_EQUAL_UINT(3, fib(0x4));
    TEST_ASSERT_EQUAL_UINT(5, fib(0x5));
    TEST_ASSERT_EQUAL_UINT(8, fib(0x6));
    TEST_ASSERT_EQUAL_UINT(13, fib(0x7));
    TEST_ASSERT_EQUAL_UINT(21, fib(0x8));
    TEST_ASSERT_EQUAL_UINT(34, fib(0x9));
    TEST_ASSERT_EQUAL_UINT(55, fib(0xA));
}

void test_similarity(void)
{
    FILE *s =
        popen("diff -Bwy --suppress-common-lines *.c *.c_old | wc -l", "r");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('1', fgetc(s),
        "Submission appears dissimilar to example - did you change more than "
        "one line?");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('\n', fgetc(s),
        "Submission appears dissimilar to example - did you change more than "
        "one line?");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE(EOF, fgetc(s),
        "Submission appears dissimilar to example - did you change more than "
        "one line?");
    pclose(s);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_small_fibs);
    RUN_TEST(test_similarity);
    return UNITY_END();
}
