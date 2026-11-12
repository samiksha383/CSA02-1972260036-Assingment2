#include <stdio.h>

int main(void) {
    /* Three test bills: (price, qty, senior) */
    int prices[]  = {200, 120, 500};
    int qtys[]    = {3,   10,  2};
    int seniors[] = {1,   0,   1};

    printf("=== Buggy Expression vs Corrected Calculation ===\n\n");

    for (int i = 0; i < 3; i++) {
        int price = prices[i];
        int qty = qtys[i];
        int senior = seniors[i];

        /* Buggy expression from prompt (integer division + wrong GST base) */
        int buggy_total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
        int buggy_net   = buggy_total > 1000 ? buggy_total - 50 : buggy_total;

        /* Corrected calculation using integer paise (exact to the paisa) */
        long gross_paise    = (long)price * qty * 100L;
        long discount_paise = senior ? (gross_paise * 15L) / 100L : 0L;
        long taxable_paise  = gross_paise - discount_paise;
        long gst_paise      = (taxable_paise * 5L + 50L) / 100L; /* rounded half-up */
        long exact_total    = taxable_paise + gst_paise;
        long exact_net      = (exact_total > 100000L) ? (exact_total - 5000L) : exact_total;

        printf("Bill %d (Price=Rs %d, Qty=%d, Senior=%d):\n", i + 1, price, qty, senior);
        printf("  Buggy Output     : Total = Rs %d | Net = Rs %d\n", buggy_total, buggy_net);
        printf("  Corrected Output : Total = Rs %ld.%02ld | Net = Rs %ld.%02ld\n\n",
               exact_total / 100, exact_total % 100, exact_net / 100, exact_net % 100);
    }

    return 0;
}
