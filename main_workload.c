#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>   // for PRIu64
#include <time.h>

// convert string to unsigned __int128
unsigned __int128 str_to_uint128(const char *s) {
    unsigned __int128 val = 0;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
        val = val * 10 + (s[i] - '0');
    }
    return val;
}

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

// helper: difference in seconds (as double)
double time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) / 1e9;
}

// main WORKLOAD driver
int main() {
    uint64_t N_OPTIONS[] = {100000000ULL, 1000000000ULL, 10000000000ULL};
    size_t N_OPTIONS_LEN = sizeof(N_OPTIONS) / sizeof(N_OPTIONS[0]);

    int NUM_TASKS[] = {2, 4, 8};
    size_t TASKS_ARRAY_LEN = sizeof(NUM_TASKS) / sizeof(NUM_TASKS[0]);

    unsigned __int128 total = 0;
    
    for (size_t i = 0; i < N_OPTIONS_LEN; i++) {
        uint64_t N = N_OPTIONS[i];
        printf("N = %" PRIu64 ":\n", N);
        
        for (int j = 0; j < TASKS_ARRAY_LEN; j++) {
            struct timespec start, end;

            // start timer
            clock_gettime(CLOCK_MONOTONIC, &start);

            // Start all processes
            FILE *fps[NUM_TASKS[j]];
            for (int k = 0; k < NUM_TASKS[j]; k++) {
                uint64_t chunk_size = N / NUM_TASKS[j];
                uint64_t lower = k * chunk_size;
                uint64_t upper = (k + 1) * chunk_size;

                char command[128];
                sprintf(command, "./sum %" PRIu64 " %" PRIu64, lower, upper);

                fps[k] = popen(command, "r");
                if (!fps[k]) {
                    perror("popen failed");
                    exit(1);
                }
            }

            // Collect results with fscanf
            for (int k = 0; k < NUM_TASKS[j]; k++) {
                char buffer[128];
                if (fscanf(fps[k], "%127s", buffer) == 1) {
                    unsigned __int128 part = str_to_uint128(buffer);
                    total += part;
                }
                pclose(fps[k]);
            }

            // stop timer
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsed = time_diff(start, end);

            // Closed-form reference using 128-bit
            unsigned __int128 expected = (unsigned __int128)N * (N - 1) / 2;

            printf("Total sum after %d tasks: ", NUM_TASKS[j]);
            print_uint128(total);
            printf("\n");

            printf("Closed-form result: ");
            print_uint128(expected);
            printf("\n");

            if (total == expected) {
                printf("Check: OK\n");
            } else {
                printf("Check: MISMATCH!\n");
            }

            printf("Elapsed time: %.6f seconds\n\n", elapsed);

            total = 0;
        }
    }
    return 0;
}
