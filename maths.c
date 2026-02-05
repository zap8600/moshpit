// Complicated math

#include <stdint.h>

// https://martin.kleppmann.com/papers/curve25519.pdf

// Math notes:
// Weird ∈ symbol: https://en.wikipedia.org/wiki/Element_of_a_set
//

// This is used for handling arithmetic with the big numbers.
// They only need to be 16-bit, but since they are signed 64-bit, we won't have to worry about overflow and underflow or propigating carries.
// It is 128 bytes, though. 8 of these would take up 1KB.
typedef int64_t field_element_t[16];

// Convert a 32-byte number into our field element format
static void unpack_25519(field_element_t out, const uint8_t* in) {
    for(uint8_t i = 0; i < 16; i++) {
        // The array is in little-endian order. 2 bytes are combined to make 16-bit value for the field element.
        // TODO: Figure out what to do if signed 64-bit integers are not an option.
        out[i] = in[2 * i] + (((int64_t)in[(2 * i) + 1]) << 8);
    }
    out[15] &= 0x7fff;
}

static void field_add(field_element_t out, field_element_t a, field_element_t b) {
    //
}
