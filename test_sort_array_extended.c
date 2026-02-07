#include "unity.h"

/* This file is obviously poorly-written - there is so much duplicated code! A
 * better way to construct all of these test functions is to generate them
 * using the preprocessor. I want to distribute this test file to our students
 * and, as we haven't covered the preprocessor in much detail yet, I thought it
 * would be a nice case study on how not to write tests. */

/* Student's function */
void sort_amber(float* values, size_t count, int(*comp)(float, float));
void setUp(void){}
void tearDown(void){}

/* Comparison functions we're going to play with */
int lt(float a, float b){return a <= b;}
int gt(float a, float b){return a >= b;}
/* Ternary operators, for the uninitiated - reading! */
int abs_lt(float a, float b){return (a < 0 ? -a : a) <= (b < 0 ? -b : b);}

/* lt */
void test_sort_example_lt(void)
{
    float fs[] = {1.5, -2.6, 4.3, 99462};
    float fsExpect[] = {-2.6, 1.5, 4.3, 99462};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch - this is the example in the notes.");
}

void test_sort_reverse_lt(void)
{
    float fs[] = {1., .8, .6, .4, .2, 0, -.2, -.4, -.6, -.8, -1.};
    float fsExpect[] = {-1., -.8, -.6, -.4, -.2, 0, .2, .4, .6, .8, 1.};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch.");
}

void test_sort_end_swap_lt(void)
{
    float fs[] = {34, 43, 45, 52, -68};
    float fsExpect[] = {-68, 34, 43, 45, 52};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

void test_sort_with_a_duplicate_lt(void)
{
    float fs[] = {194, -396, 4.9, -396};
    float fsExpect[] = {-396, -396, 4.9, 194};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

/* gt */
void test_sort_example_gt(void)
{
    float fs[] = {1.5, -2.6, 4.3, 99462};
    float fsExpect[] = {99462, 4.3, 1.5, -2.6};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, gt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch.");
}

void test_sort_reverse_gt(void)
{
    float fs[] = {-1., -.8, -.6, -.4, -.2, 0, .2, .4, .6, .8, 1.};
    float fsExpect[] = {1., .8, .6, .4, .2, 0, -.2, -.4, -.6, -.8, -1.};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, gt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch.");
}

void test_sort_end_swap_gt(void)
{
    float fs[] = {45, 43, 34, -68, 52};
    float fsExpect[] = {52, 45, 43, 34, -68};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, gt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

void test_sort_with_a_duplicate_gt(void)
{
    float fs[] = {194, -396, 4.9, -396};
    float fsExpect[] = {194, 4.9, -396, -396};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, gt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

/* abs_lt */
void test_sort_example_abs_lt(void)
{
    float fs[] = {1.5, -2.6, 4.3, 99462};
    float fsExpect[] = {1.5, -2.6, 4.3, 99462};  /* Unchanged */
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, abs_lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch.");
}

void test_sort_reverse_abs_lt(void)
{
    /* I'm avoiding the duplicates here, because the output order is
     * ill-defined (both abs_lt(-1, 1) and abs_lt(1, -1) are 0). */
    float fs[] = {-1., -.8, -.6, -.4, -.2, 0};
    float fsExpect[] = {0, -.2, -.4, -.6, -.8, -1.};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, abs_lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch.");
}

void test_sort_end_swap_abs_lt(void)
{
    float fs[] = {45, 43, 34, -68, 52};
    float fsExpect[] = {34, 43, 45, 52, -68};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, abs_lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

void test_sort_with_a_duplicate_abs_lt(void)
{
    float fs[] = {194, -396, 4.9, -396};
    float fsExpect[] = {4.9, 194, -396, -396};
    size_t length = sizeof(fs) / sizeof(float);
    sort_amber(fs, length, abs_lt);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sort_example_lt);
    RUN_TEST(test_sort_reverse_lt);
    RUN_TEST(test_sort_end_swap_lt);
    RUN_TEST(test_sort_with_a_duplicate_lt);
    RUN_TEST(test_sort_example_gt);
    RUN_TEST(test_sort_reverse_gt);
    RUN_TEST(test_sort_end_swap_gt);
    RUN_TEST(test_sort_with_a_duplicate_gt);
    RUN_TEST(test_sort_example_abs_lt);
    RUN_TEST(test_sort_reverse_abs_lt);
    RUN_TEST(test_sort_end_swap_abs_lt);
    RUN_TEST(test_sort_with_a_duplicate_abs_lt);
    return UNITY_END();
}
