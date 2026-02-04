#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _WIN32
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif

// https://jvns.ca/blog/2022/03/23/a-toy-version-of-tls/
// https://tls13.xargs.org/
// https://x25519.xargs.org/

int main(int argc, char** argv) {
    srand(time(NULL)); // Set the seed for the random number generator

    //
    // Client Key Exchange Generation
    //

    // The private key is 32 bytes of random data
    uint8_t private_key[32];
    for(uint8_t i = 0; i < 32; i++) {
        private_key[i] = ((uint8_t)rand());
    }
}
