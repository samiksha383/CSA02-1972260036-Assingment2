#include <stdio.h>

unsigned long checks = 0; /* number of divisions performed by the last call */

/* Complete the Code: Improved for-loop (i <= n / i avoids i*i overflow) */
int is_prime(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i <= n / i; i++) {
        checks++;
        if (n % i == 0) return 0;
    }
    return 1;
}

/* Naive version: tests 2 to n - 1 */
int is_prime_naive(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i < n; i++) {
        checks++;
        if (n % i == 0) return 0;
    }
    return 1;
}

/* Improved while-loop version */
int is_prime_while(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    unsigned long i = 2;
    while (i <= n / i) {
        checks++;
        if (n % i == 0) return 0;
        i++;
    }
    return 1;
}

/* Improved do-while version (requires early exit for n == 2 and n == 3) */
int is_prime_dowhile(unsigned long n)
{
    checks = 0;
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1; /* prevents executing body when i=2 > sqrt(n) */
    unsigned long i = 2;
    do {
        checks++;
        if (n % i == 0) return 0;
        i++;
    } while (i <= n / i);
    return 1;
}

int main(void)
{
    unsigned long tickets[] = {97, 100, 7919, 1000003};

    printf("=== Improved for-loop (i <= n / i) ===\n");
    for (int k = 0; k < 4; k++) {
        int p = is_prime(tickets[k]);
        printf("%8lu %-9s divisions = %lu\n", tickets[k], p ? "prime" : "not prime", checks);
    }

    printf("\n=== Naive for-loop (i < n) ===\n");
    for (int k = 0; k < 4; k++) {
        int p = is_prime_naive(tickets[k]);
        printf("%8lu %-9s divisions = %lu\n", tickets[k], p ? "prime" : "not prime", checks);
    }

    printf("\n=== Verification of while & do-while (including n=2, n=3) ===\n");
    unsigned long edge[] = {2, 3, 97, 1000003};
    for (int k = 0; k < 4; k++) {
        int pw = is_prime_while(edge[k]);
        unsigned long cw = checks;
        int pd = is_prime_dowhile(edge[k]);
        unsigned long cd = checks;
        printf("%8lu -> while: %s (%lu divs) | do-while: %s (%lu divs)\n",
               edge[k], pw ? "prime" : "not", cw, pd ? "prime" : "not", cd);
    }
    return 0;
}
