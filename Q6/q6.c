#include <stdio.h>

#define MAX_MONTHS 360
#define EPSILON 1e-6

void simulate_loan(double principal, double monthly_rate_pct, double emi, int print_schedule)
{
    double balance = principal;
    double r = monthly_rate_pct / 100.0;
    double total_interest = 0.0;
    int month = 0;

    if (print_schedule) {
        printf("=== Loan Schedule: Principal = Rs %.2f | Rate = %.2f%%/mo | EMI = Rs %.2f ===\n",
               principal, monthly_rate_pct, emi);
        printf("%-6s | %-12s | %-10s | %-12s | %-12s\n",
               "Month", "Open Bal", "Interest", "Repayment", "Close Bal");
    }

    while (balance > EPSILON) {
        if (month >= MAX_MONTHS) {
            printf("ABORTED at %d months: Loan cannot be repaid within 30 years (EMI Rs %.2f is too low vs initial interest Rs %.2f).\n\n",
                   MAX_MONTHS, emi, principal * r);
            return;
        }

        month++;
        double open_bal = balance;
        double interest = open_bal * r;
        double due = open_bal + interest;
        double payment = (due < emi) ? due : emi; /* Final month cap */

        balance = due - payment;
        total_interest += interest;

        if (print_schedule) {
            printf("%-6d | %12.2f | %10.2f | %12.2f | %12.2f\n",
                   month, open_bal, interest, payment, balance);
        }
    }

    if (print_schedule) {
        printf("Summary: Repaid in %d months | Total Interest Paid = Rs %.2f\n\n",
               month, total_interest);
    } else {
        printf("EMI = Rs %7.2f -> Months = %3d | Total Interest = Rs %9.2f\n",
               emi, month, total_interest);
    }
}

int main(void)
{
    /* 1. Hand-verified correctness check */
    simulate_loan(10000.0, 2.0, 2000.0, 1);

    /* 2. Growth investigation as EMI approaches monthly interest (Rs 200.00) */
    printf("=== Growth Investigation (Principal Rs 10,000 @ 2%%/mo -> Min Interest Rs 200) ===\n");
    double test_emis[] = {2000.0, 1000.0, 500.0, 250.0, 210.0, 201.0, 190.0};
    for (int i = 0; i < 7; i++) {
        simulate_loan(10000.0, 2.0, test_emis[i], 0);
    }

    return 0;
}
