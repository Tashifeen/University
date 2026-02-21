#include <stdio.h>
#include <stdint.h>

/*
 * invert_farbfeld:
 * Reads a farbfeld image from 'in', writes the colour‑inverted image to 'out'.
 * Farbfeld format:
 *   - 8 bytes:  "farbfeld"
 *   - 4 bytes:  width  (big‑endian)
 *   - 4 bytes:  height (big‑endian)
 *   - For each pixel: 8 bytes = R G B A (each 16‑bit, big‑endian)
 *
 * We invert only R, G, B. Alpha stays the same.
 */
void invert_farbfeld(FILE *in, FILE *out)
{
    unsigned char header[16];

    /* Read and immediately write the 16‑byte header */
    fread(header, 1, 16, in);
    fwrite(header, 1, 16, out);

    /* Buffer for one pixel: 8 bytes = R G B A */
    unsigned char p[8];

    /* Process each pixel until EOF */
    while (fread(p, 1, 8, in) == 8) {

        /* Combine two bytes into a 16‑bit value (big‑endian) */
        uint16_t r = (p[0] << 8) | p[1];
        uint16_t g = (p[2] << 8) | p[3];
        uint16_t b = (p[4] << 8) | p[5];
        uint16_t a = (p[6] << 8) | p[7];   /* alpha unchanged */

        /* Invert RGB using bitwise NOT */
        r = ~r;
        g = ~g;
        b = ~b;

        /* Write the 16‑bit values back in big‑endian order */
        p[0] = r >> 8; p[1] = r & 0xFF;
        p[2] = g >> 8; p[3] = g & 0xFF;
        p[4] = b >> 8; p[5] = b & 0xFF;
        p[6] = a >> 8; p[7] = a & 0xFF;

        fwrite(p, 1, 8, out);
    }
}

/* Standard farbfeld filter style: read from stdin, write to stdout */
int main(void)
{
    invert_farbfeld(stdin, stdout);
    return 0;
}
