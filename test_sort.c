#include "unity.h"

void sort_red(float* values, size_t count);  /* Student's function */
void setUp(void){}
void tearDown(void){}

/* Note there's no +/-0 test here */

void test_sort_example(void)
{
    float fs[] = {1.5, -2.6, 4.3, 99462};
    float fsExpect[] = {-2.6, 1.5, 4.3, 99462};
    size_t length = sizeof(fs) / sizeof(float);
    sort_red(fs, sizeof(fs) / sizeof(float));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch - this is the example in the notes.");
}

void test_sort_reverse(void)
{
    float fs[] = {1., .8, .6, .4, .2, 0, -.2, -.4, -.6, -.8, -1.};
    float fsExpect[] = {-1., -.8, -.6, -.4, -.2, 0, .2, .4, .6, .8, 1.};
    size_t length = sizeof(fs) / sizeof(float);
    sort_red(fs, sizeof(fs) / sizeof(float));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch.");
}

void test_sort_end_swap(void)
{
    float fs[] = {34, 43, 45, 52, -68};
    float fsExpect[] = {-68, 34, 43, 45, 52};
    size_t length = sizeof(fs) / sizeof(float);
    sort_red(fs, sizeof(fs) / sizeof(float));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

void test_sort_with_a_duplicate(void)
{
    float fs[] = {194, -396, 4.9, -396};
    float fsExpect[] = {-396, -396, 4.9, 194};
    size_t length = sizeof(fs) / sizeof(float);
    sort_red(fs, sizeof(fs) / sizeof(float));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(fsExpect, fs, length,
        "Float array mismatch");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sort_example);
    RUN_TEST(test_sort_reverse);
    RUN_TEST(test_sort_end_swap);
    RUN_TEST(test_sort_with_a_duplicate);
    return UNITY_END();
}
