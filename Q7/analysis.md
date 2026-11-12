\# Q7 – Day-4 Design Challenge: Diagnose, Redesign and Validate



\## A. Diagnose the Bottleneck

\* \*\*Selected Program:\*\* \*\*Q5 (Lucky-Draw Ticket Prime Verification)\*\*.

\* \*\*Diagnosis:\*\* Even after bounding the loop to \\(\\lfloor\\sqrt{n}\\rfloor\\), profiling `is\_prime(1000003)` reveals \*\*999 modulo (`%`) divisions\*\*. Every integer modulo operation is a multi-cycle hardware division instruction, and \*\*66.7% of those divisions are completely wasted\*\* testing multiples of `2` (`4, 6, 8, ...`) and multiples of `3` (`9, 15, 21, ...`) even after `n % 2` and `n % 3` have already failed.



\## B. Define the Design Objective

\* \*\*Measurable Objective:\*\* Reduce the number of modulo divisions required to verify large prime tickets by \*\*at least 65%\*\* while maintaining \*\*O(1) auxiliary memory\*\* and \*\*zero integer overflow risk\*\*.



\## C. Design the Revised Solution (6k ± 1 Wheel Factorization)

\* \*\*Mathematical Property Exploited:\*\* Every integer greater than `3` can be written as 6k + r where \\(r \\in \\{0, 1, 2, 3, 4, 5\\}\\).

&#x20; \* 6k, 6k+2, 6k+4 are divisible by `2`.

&#x20; \* 6k+3 is divisible by `3`.

&#x20; \* Therefore, \*\*all prime numbers > 3 must be of the form 6k - 1 or 6k + 1\*\* (`5, 7, 11, 13, 17, 19, ...`).

\* \*\*Design Changes:\*\* Check `n % 2 == 0` and `n % 3 == 0` once upfront, then step `i` by `6` starting at `5` (`i += 6`), testing only `i` and `i + 2` up to `n / i`.

\* \*\*Memory \& Trade-Off:\*\* Requires \*\*0 bytes\*\* of extra memory (O(1) space). The trade-off is slightly more complex loop control (two `if` checks per iteration) compared to the simple `i++` loop.



```text

PSEUDOCODE: is\_prime\_redesigned(n)

1\. if n < 2 return FALSE

2\. if n == 2 or n == 3 return TRUE

3\. if (n mod 2 == 0) or (n mod 3 == 0) return FALSE

4\. i <- 5

5\. while i <= n / i:

&#x20;      if (n mod i == 0) or (n mod (i + 2) == 0) return FALSE

&#x20;      i <- i + 6

6\. return TRUE

```



\## D. Predict Before Implementing

\* \*\*Prediction:\*\* Because stepping by `6` tests `2` candidates out of every `6` integers ($\\frac{2}{6} = \\frac{1}{3}$), divisions for large primes should drop to roughly \*\*$\\frac{1}{3}\\sqrt{n} + 2$\*\*:

&#x20; \* For `n = 1,000,003` ($\\sqrt{n} \\approx 1000$): predicted divisions $\\approx 333 + 2 = \\mathbf{335}$ (down from `999`, a \*\*\~66.5% reduction\*\*).

&#x20; \* For `n = 7,919` ($\\sqrt{n} \\approx 88$): predicted divisions $\\approx 28 + 2 = \\mathbf{30}$ (down from `87`, a \*\*\~65.5% reduction\*\*).



\## E. Implement and Validate the Redesign



| Ticket `n` | Status | Original Divisions | Redesigned Divisions | Measured Reduction |

| :--- | :--- | :--- | :--- | :--- |

| `97` | Prime | `8` | `4` | \*\*50.0%\*\* |

| `100` | Composite | `1` | `1` | \*\*0.0%\*\* |

| `7919` | Prime | `87` | `30` | \*\*65.5%\*\* |

| `1000003` | Prime | `999` | `334` | \*\*66.6%\*\* |

| `999983` | Prime | `998` | `334` | \*\*66.5%\*\* |



\* Observed counts (`334` and `30`) match our pre-execution predictions (`335` and `30`) within 1 division.



\## F. Defend the Final Design

\* \*\*Objective Achieved:\*\* Yes — achieved a \*\*66.6% reduction\*\* in divisions on large primes (exceeding our 65% target) with \*\*$O(1)$ space\*\*.

\* \*\*When Original or Sieve is Preferable:\*\*

&#x20; \* For tiny inputs (`n < 25`), the original `i++` loop has simpler branch logic and nearly identical division counts.

&#x20; \* If the college fest verifies \*\*all 1,000,000 tickets in a single batch\*\*, a \*\*Sieve of Eratosthenes\*\* ($O(N \\log \\log N)$ time, $1\\text{ MB}$ RAM) outperforms per-ticket wheel division ($O(N\\sqrt{N})$ total), whereas `is\_prime\_redesigned` is optimal when memory is constrained or queries are sparse.



