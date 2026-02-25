#define _XOPEN_SOURCE  /* for popen and pclose */
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"

unsigned* sieve(size_t const);  /* Student's function */

void setUp(void){}
void tearDown(void){}

void test_small_sieve(void)
{
    unsigned *const primes = sieve(30);
    unsigned *p = primes;
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 0 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 1 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 2 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 3 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 4 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 5 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 6 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 7 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 8 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 9 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 10 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 11 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 12 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 13 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 14 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 15 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 16 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 17 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 18 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 19 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 20 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 21 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 22 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 23 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 24 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 25 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 26 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 27 */
	TEST_ASSERT_EQUAL_UINT(0, *p++);  /* 28 */
	TEST_ASSERT_EQUAL_UINT(1, *p++);  /* 29 */
    free(primes);
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
    RUN_TEST(test_small_sieve);
    RUN_TEST(test_similarity);
    return UNITY_END();
}
