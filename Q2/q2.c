#include <stdio.h>

static int slow_api_calls = 0;

int verify_disability_card(int has_card) {
    slow_api_calls++; /* Simulates slow network call + audit logging */
    return has_card;
}

int main(void) {
    /* Generate 1,000 sample passengers:
       60% seniors (age >= 60), 50% eligible class, 10% disability card */
    int is_senior[1000], valid_class[1000], has_card[1000];
    for (int i = 0; i < 1000; i++) {
        is_senior[i]   = (i % 10 < 6) ? 1 : 0;
        valid_class[i] = (i % 2 == 0) ? 1 : 0;
        has_card[i]    = (i % 10 == 0) ? 1 : 0;
    }

    /* Order 1: Cheap checks first -> (is_senior && valid_class) || verify_disability_card() */
    slow_api_calls = 0;
    int granted1 = 0;
    for (int i = 0; i < 1000; i++) {
        if ((is_senior[i] && valid_class[i]) || verify_disability_card(has_card[i])) {
            granted1++;
        }
    }
    printf("Order 1 (Cheap checks first with ||) : Granted = %d | Slow API Calls = %d\n",
           granted1, slow_api_calls);

    /* Order 2: Slow check first -> verify_disability_card() || (is_senior && valid_class) */
    slow_api_calls = 0;
    int granted2 = 0;
    for (int i = 0; i < 1000; i++) {
        if (verify_disability_card(has_card[i]) || (is_senior[i] && valid_class[i])) {
            granted2++;
        }
    }
    printf("Order 2 (Slow check first with ||)   : Granted = %d | Slow API Calls = %d\n",
           granted2, slow_api_calls);

    /* Order 3: Bitwise & and | (No short-circuiting!) */
    slow_api_calls = 0;
    int granted3 = 0;
    for (int i = 0; i < 1000; i++) {
        if ((is_senior[i] & valid_class[i]) | verify_disability_card(has_card[i])) {
            granted3++;
        }
    }
    printf("Order 3 (Bitwise & and | operators)  : Granted = %d | Slow API Calls = %d\n",
           granted3, slow_api_calls);

    return 0;
}
