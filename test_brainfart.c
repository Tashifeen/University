#include "unity.h"

int brainfart_red(char const *commands);  /* Student's function */
void setUp(void){}
void tearDown(void){}

void test_zero_stop(void)
{
    char command[3] = {'+', 0, '-'};
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, brainfart_red(command),
        "Output mismatch: should stop at \0.");
}

void test_empty(void)
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, brainfart_red(""),
        "Output mismatch: empty command list case.");
}

void test_example_no_ignores(void)
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, brainfart_red("+++>--<+<>"),
        "Output mismatch: example in the lab brief.");
}

void test_ignored_chars(void)
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, brainfart_red("+++>--<+<octopus>"),
        "Output mismatch: example in the lab brief.");
}

void test_negative_return(void)
{
    TEST_ASSERT_EQUAL_INT_MESSAGE(-3, brainfart_red("-<+>->+<-<>><"),
        "Output mismatch: can you return negative numbers?");
}

void test_wrap(void)
{
    /* I mean, I can't explicitly test this, but I can give it a good go!
     * Memcheck will yell if we write to data we don't own... */
    char commands[500];
    for (size_t i = 0; i < 498; commands[i++] = '>');
    commands[498] = '+';
    commands[499] = 0;
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, brainfart_red(commands),
        "Output mismatch: does > wrap around?");
    for (size_t i = 0; i < 498; commands[i++] = '<');
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, brainfart_red(commands),
        "Output mismatch: does < wrap around?");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_zero_stop);
    RUN_TEST(test_empty);
    RUN_TEST(test_example_no_ignores);
    RUN_TEST(test_ignored_chars);
    RUN_TEST(test_negative_return);
    RUN_TEST(test_wrap);
    return UNITY_END();
}
