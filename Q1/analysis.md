\# Q1 – Precedence, Associativity and the Discount Bug



\## 1. Pre-Execution Predictions \& Operator-by-Operator Order

In C, `\*`, `/`, and `%` have higher precedence than `+` and `-`, and associate \*\*left-to-right\*\*.

In `total = price \* qty - price \* qty \* 15 / 100 \* senior + price \* qty \* 5 / 100;`:

1\. `price \* qty` is evaluated first (left-to-right).

2\. `price \* qty \* 15` is multiplied, then integer-divided by `100` (truncating decimals!), then multiplied by `senior`.

3\. `price \* qty \* 5` is multiplied, then integer-divided by `100` (GST is computed on the \*\*undiscounted\*\* gross amount instead of the discounted amount!).

4\. Finally, subtraction (`-`) and addition (`+`) run left-to-right.



\### Predicted vs. Observed Values

\* \*\*Bill 1 (`price=200, qty=3, senior=1`):\*\*

&#x20; \* Gross = `600`. Discount = `600 \* 15 / 100 \* 1 = 90`. Buggy GST = `600 \* 5 / 100 = 30`.

&#x20; \* \*\*Predicted Buggy:\*\* `total = 600 - 90 + 30 = 540`, `net = 540`.

&#x20; \* \*\*Intended Pharmacist Bill:\*\* Taxable = `600 - 90 = 510`. GST (5% of 510) = `Rs 25.50`. \*\*Correct Total = `Rs 535.50`\*\*.

\* \*\*Bill 2 (`price=120, qty=10, senior=0`):\*\*

&#x20; \* Gross = `1200`. Discount = `0`. GST = `1200 \* 5 / 100 = 60`.

&#x20; \* \*\*Predicted Buggy:\*\* `total = 1260`, `net = 1260 - 50 = 1210` (Matches intended because `senior == 0` and numbers are multiples of 100).

\* \*\*Bill 3 (`price=500, qty=2, senior=1`):\*\*

&#x20; \* Gross = `1000`. Discount = `150`. Buggy GST = `50` (on `1000` instead of `850`).

&#x20; \* \*\*Predicted Buggy:\*\* `total = 1000 - 150 + 50 = 900`, `net = 900`.

&#x20; \* \*\*Intended Pharmacist Bill:\*\* Taxable = `850`. GST (5% of 850) = `Rs 42.50`. \*\*Correct Total = `Rs 892.50`\*\*.



\### Bugs Identified

1\. \*\*Tax Base Bug:\*\* GST (`5%`) is calculated on `price \* qty` instead of `(gross - discount)`, overcharging senior citizens.

2\. \*\*Integer Division Truncation:\*\* `15 / 100` in integer arithmetic drops paise (e.g., for `price = 55, qty = 1`, `55 \* 15 / 100 = 8` instead of `8.25`).



\## 2. Inquiry: Why `count = count++ + 1;` is Undefined Behaviour

\* Modifying `count` via post-increment (`count++`) and assigning to `count` (`count = ...`) in the same full expression without an intervening sequence point violates C's evaluation order rules, resulting in \*\*Undefined Behaviour (UB)\*\*.

\* With `gcc -Wall`, the compiler emits: `warning: operation on 'count' may be undefined \[-Wsequence-point]`.



\## 3. Design Decision \& Complexity Analysis

\* \*\*Decision:\*\* Use \*\*both intermediate variables and brackets\*\* in integer paise (`gross\_paise`, `discount\_paise`, `taxable\_paise`, `gst\_paise`). This eliminates repeated `price \* qty` multiplications, guarantees exact rounding, and makes the tax base auditable.

\* \*\*Alternative Concept (Intermediate Variables vs. Single Expression):\*\*

&#x20; \* \*\*Time Complexity:\*\* Both run in \*\*$O(1)$\*\* time, though intermediate variables actually perform \*\*fewer\*\* CPU multiplications (reusing `gross\_paise` instead of recomputing `price \* qty` three times).

&#x20; \* \*\*Space Complexity:\*\* Extra local variables use $O(1)$ stack space (\~32 bytes total), which compilers typically optimize directly into CPU registers with zero RAM overhead.



