#include <stdio.h>

int sum_up_to(int N);

// You have a main WORKLOAD, where you have to calculate the sum of variables from 0 up to N (not inclusive).
int main() {
    int N = 5;
    printf("Sum of 0 up to %d: %d\n", N, sum_up_to(N));
    return 0;
}

int sum_up_to(int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += i;
    }
    return sum;
}