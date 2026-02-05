#include <stdint.h>

// https://martin.kleppmann.com/papers/curve25519.pdf

typedef int64_t field_element[16];

// Turns a byte array into our element
static void unpack_25519(field_element out, const uint8_t* in) {
    for(uint8_t i = 0; i < 16; i++) {
        out[i] = in[2 * i] + (((int64_t)in[(2*i) + 1]) << 8);
    }
    out[15] &= 0x7fff;
}

// Carry flag kinda thing
static void carry_25519(field_element element) {
    int64_t carry;
    for(uint8_t i = 0; i < 16; i++) {
        carry = element[i] >> 16;
        element[i] -= carry << 16;
        if(i < 15) {
            element[i + 1] += carry;
        } else {
            element[0] += 38 * carry;
        }
    }
}

// Adds field elements
static void field_add(field_element out, const field_element a, const field_element b) {
    for(uint8_t i = 0; i < 16; i++) {
        out[i] = a[i] + b[i];
    }
}

// Subtracts field elements
static void field_sub(field_element out, const field_element a, const field_element b) {
    for(uint8_t i = 0; i < 16; i++) {
        out[i] = a[i] - b[i];
    }
}

static void field_mul(field_element out, const field_element a, const field_element b) {
    uint8_t i;
    uint8_t j;
    int64_t product[31];

    for(i = 0; i < 31; i++) {
        product[i] = 0;
    }

    for(i = 0; i < 16; i++) {
        for(j = 0; j < 16; j++) {
            product[i + j] += a[i] * b[j];
        }
    }

    for(i = 0; i < 15; i++) {
        product[i] += 38 * product[i + 16];
    }
    for(i = 0; i < 16; i++) {
        out[i] = product[i];
    }

    carry_25519(out);
    carry_25519(out);
}

static void field_inverse(field_element out, const field_element in) {
    field_element c;
    uint8_t i;
    for(i = 0; i < 16; i++) {
        c[i] = in[i];
    }
    for(i = 253; i >= 0; i--) {
        field_mul(c, c, c);
        if((i != 2) && (i != 4)) {
            field_mul(c, c, in);
        }
    }
}
