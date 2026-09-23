#include <stdint.h>          // for uint32_t

float Q_rsqrt_union(float number)
{
    union {
        float f;             // float view of the bits
        uint32_t i;          // integer view of the same bits
    } u;                     // the union instance

    u.f = number;            // store input float into union (bits remain same)

    float x2 = number * 0.5f; // precompute number * 0.5 (used in Newton step)

    u.i = 0x5f3759dfu - (u.i >> 1);
    // reinterpret bits as integer
    // apply the "magic constant"
    // this gives an approximation of 1/sqrt(number)

    float y = u.f;           // reinterpret integer bits back as float

    y = y * (1.5f - (x2 * y * y));
    // one iteration of Newton–Raphson refinement
    // improves accuracy significantly

    return y;                // result: fast inverse square root
}
