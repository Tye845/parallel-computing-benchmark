#include <stdio.h>
#include <stdlib.h>

// convert string to __int128
__int128 str_to_int128(const char *s) {
    __int128 val = 0;
    int i = 0, neg = 0;
    if (s[0] == '-') { neg = 1; i++; }
    for (; s[i] >= '0' && s[i] <= '9'; i++) {
        val = val * 10 + (s[i] - '0');
    }
    return neg ? -val : val;
}

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

// You have a main WORKLOAD, where you have to calculate the sum of variables from 0 up to N (not inclusive).
int main() {
    int N = 1000;
    int NUM_TASKS[] = {2, 4, 8};
    size_t TASKS_ARRAY_LEN = sizeof(NUM_TASKS)/sizeof(NUM_TASKS[0]);
    __int128 total = 0;
    
    for (int i = 0; i < TASKS_ARRAY_LEN; i++) {
        printf("Running with %d tasks:\n", NUM_TASKS[i]);

        // Start all processes
        FILE *fps[NUM_TASKS[i]];
        for (int j = 0; j < NUM_TASKS[i]; j++) {
            long long part = 0;
            long long chunk_size = N / NUM_TASKS[i];
            long long lower = j * chunk_size;
            long long upper = (j + 1) * chunk_size;

            printf("lower=%lld upper=%lld\n", lower, upper);

            char command[128];
            sprintf(command, "./sum %lld %lld", lower, upper);
            fps[j] = popen(command, "r");
        }

        // Collect results
        for (int j = 0; j < NUM_TASKS[i]; j++) {
            char buffer[128];
            if (fgets(buffer, sizeof(buffer), fps[j]) != NULL) {
                __int128 part = str_to_int128(buffer);
                total += part;
            }
            
            pclose(fps[j]);
        }

        printf("Total sum after %d tasks: ", NUM_TASKS[i]);
        print_int128(total);
        printf("\n\n");
        total = 0;
    }

    return 0;
}