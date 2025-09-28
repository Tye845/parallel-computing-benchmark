#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>  // for uint64_t and strtoull

// helper to print unsigned __int128
void print_uint128(unsigned __int128 value) {
    if (value == 0) {
        printf("0");
        return;
    }
    char buf[64];
    int i = 0;

    while (value > 0) {
        buf[i++] = (value % 10) + '0';  
        value /= 10;
    }

    while (i > 0) putchar(buf[--i]);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s lower upper\n", argv[0]);
        return 1;
    }

    uint64_t lower = strtoull(argv[1], NULL, 10); 
    uint64_t upper = strtoull(argv[2], NULL, 10); 
    unsigned __int128 sum = 0;

    for (uint64_t i = lower; i < upper; i++) {
        sum += i;
    }

    print_uint128(sum);
    printf("\n");
    return 0;
}
