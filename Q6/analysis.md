\# Q6 – Loops That Must Terminate: Loan Repayment Schedule



\## 1. Loop Choice \& Termination Safety

\* \*\*Why `while (balance > EPSILON)`:\*\* The exact number of months is unknown before execution, and if `principal == 0`, zero iterations should run (`while` checks before executing).

\* \*\*Why `balance != 0` is Dangerous:\*\* IEEE 754 binary floating-point subtraction rarely hits exact `0.0` (leaving dust like `1.8e-12`), causing an infinite loop. Using `balance > 1e-6` guarantees clean termination.

\* \*\*Last-Month Adjustment:\*\* When `open\_bal + interest < emi`, the borrower pays only `open\_bal + interest` so the closing balance never goes negative.

\* \*\*Underpayment Trap (`emi <= principal \* r`):\*\* If repayment is less than or equal to the first month's interest (`Rs 200`), the balance grows or stays constant forever, causing an infinite loop without a guard.



\## 2. Hand-Verified Correctness Check (`Rs 10,000` at `2%/mo`, `Rs 2,000` EMI)



| Month | Opening Balance | Interest (2%) | Repayment | Closing Balance |

| :--- | :--- | :--- | :--- | :--- |

| 1 | `10,000.00` | `200.00` | `2,000.00` | `8,200.00` |

| 2 | `8,200.00` | `164.00` | `2,000.00` | `6,364.00` |

| 3 | `6,364.00` | `127.28` | `2,000.00` | `4,491.28` |

| 4 | `4,491.28` | `89.83` | `2,000.00` | `2,581.11` |

| 5 | `2,581.11` | `51.62` | `2,000.00` | `632.73` |

| 6 | `632.73` | `12.65` | `645.38` | `0.00` |



\* \*\*Total Months:\*\* `6` | \*\*Total Interest:\*\* `Rs 645.38` (Matches program output to the paisa).



\## 3. Growth Investigation \& Deployment Decision

\* As EMI drops from `Rs 2,000` $\\rightarrow$ `Rs 500` $\\rightarrow$ `Rs 210` $\\rightarrow$ `Rs 201`, iterations grow nonlinearly: `6` $\\rightarrow$ `26` $\\rightarrow$ `154` $\\rightarrow$ `269` months. At `Rs 190` (`< Rs 200` interest), it never terminates.

\* \*\*Deployment Decision:\*\* Enforce `MAX\_MONTHS = 360` (30-year ceiling) with `break`/`return` and display an actionable message stating the minimum monthly interest required so the SHG officer can adjust the EMI immediately.



\## 4. Alternative Concept and Complexity Analysis (Closed-Form Formula)

\* \*\*Formula:\*\* $n = \\lceil -\\log(1 - r \\cdot P / E) / \\log(1 + r) \\rceil$ computes total months in \*\*$O(1)$\*\* time and \*\*$O(1)$\*\* space, versus \*\*$O(n)$\*\* iterations for month-by-month simulation.

\* \*\*Trade-Off:\*\* When $E \\approx r \\cdot P$, $1 - r \\cdot P / E$ suffers catastrophic cancellation in floating point, and the closed-form formula cannot print a month-by-month passbook schedule with exact paise rounding at each step.



