#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// https://jvns.ca/blog/2022/03/23/a-toy-version-of-tls/
// https://tls13.xargs.org/
// https://x25519.xargs.org/

const int basepoint = 9;

int main() {
    srand(time(NULL)); // Set the seed for the random number generator

    //
    // Client Key Exchange Generation
    //

    // The private key is 32 bytes of random data
    uint8_t private_key[32];
    for(uint8_t i = 0; i < 32; i++) {
        private_key[i] = ((uint8_t)rand());
    }

    // The public key is... uh... something.
    uint8_t public_key[32]; // I think it's 32 bytes
}
