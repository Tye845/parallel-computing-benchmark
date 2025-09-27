#include <stdio.h>
#include <stdlib.h>

// helper to print __int128
void print_int128(__int128 value) {
    if (value == 0) {
        printf("0");
        return;
    }
    char buf[64];
    int i = 0;
    int neg = value < 0;
    if (neg) value = -value;

    while (value > 0) {
        buf[i++] = (value % 10) + '0';
        value /= 10;
    }
    if (neg) putchar('-');
    while (i > 0) putchar(buf[--i]);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s lower upper\n", argv[0]);
        return 1;
    }

    long long lower = atoll(argv[1]);
    long long upper = atoll(argv[2]);
    __int128 sum = 0;

    for (long long i = lower; i < upper; i++) {
        sum += i;
    }

    print_int128(sum);
    printf("\n");
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// __int128 sum_up_to(long long lower_bound, long long upper_bound);

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <N>\n", argv[0]);
//         return 1;
//     }
    
//     int lower_bound = atoi(argv[1]);
//     int upper_bound = atoi(argv[2]);
//     return 0;
// }

// __int128 sum_up_to(long long lower_bound, long long upper_bound) {
//     __int128 sum = 0;
//     for (long long i = lower_bound; i < upper_bound; i++) {
//         sum += i;
//     }
//     return sum;
// }