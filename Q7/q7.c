#include <stdio.h>

unsigned long checks = 0;

/* Original Q5 Implementation: tests all integers 2 .. sqrt(n) */
int is_prime_original(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i <= n / i; i++) {
        checks++;
        if (n % i == 0) return 0;
    }
    return 1;
}

/* Redesigned Q7 Implementation: 6k +/- 1 Wheel Optimization
   Eliminates all multiples of 2 and 3 after initial O(1) checks */
int is_prime_redesigned(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;

    checks++;
    if (n % 2 == 0) return 0;

    checks++;
    if (n % 3 == 0) return 0;

    for (unsigned long i = 5; i <= n / i; i += 6) {
        checks++;
        if (n % i == 0) return 0;

        checks++;
        if (n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main(void)
{
    unsigned long tickets[] = {97, 100, 7919, 1000003, 999983};
    int count = 5;

    printf("=== Q7 Validation: Original vs. Redesigned (6k +/- 1 Wheel) ===\n");
    printf("%-10s | %-9s | %-14s | %-14s | %-10s\n",
           "Ticket", "Result", "Original Divs", "Redesigned Divs", "Reduction");
    printf("--------------------------------------------------------------------\n");

    for (int k = 0; k < count; k++) {
        unsigned long t = tickets[k];
        int r1 = is_prime_original(t);
        unsigned long d1 = checks;

        int r2 = is_prime_redesigned(t);
        unsigned long d2 = checks;

        double pct = (d1 > 0) ? (100.0 * (d1 - d2) / d1) : 0.0;
        printf("%-10lu | %-9s | %-14lu | %-14lu | %8.1f%%\n",
               t, (r1 && r2) ? "PRIME" : "COMPOSITE", d1, d2, pct);
    }

    return 0;
}
