\# Q5 – Count the Work Done by a Loop



\## 1. Loop Design \& Division Count Comparison



| Ticket `n` | Status | Improved (`i <= n/i`) | Naive (`i < n`) | Speedup Factor |

| :--- | :--- | :--- | :--- | :--- |

| `97` | Prime | \*\*8\*\* | \*\*95\*\* | `11.9×` |

| `100` | Composite | \*\*1\*\* | \*\*1\*\* | `1.0×` (early `return 0` at `i=2`) |

| `7919` | Prime | \*\*87\*\* | \*\*7,917\*\* | `91.0×` |

| `1000003` | Prime | \*\*999\*\* | \*\*1,000,001\*\* | `1,001.0×` |



\* \*\*Loop Condition Without `sqrt()`:\*\* Testing `i \* i <= n` (or `i <= n / i`) checks divisors strictly up to $\\lfloor\\sqrt{n}\\rfloor$ using integer arithmetic only.

\* \*\*Early Termination:\*\* `return 0` exits the function immediately on the first `n % i == 0`, avoiding wasted checks once a factor is found.



\## 2. Inquiry: `do-while` Edge Cases \& `i \* i` Overflow

\* \*\*Why `do-while` needs special care for `n = 2` and `n = 3`:\*\* A `do-while` loop always executes its body \*\*at least once\*\* before checking the condition. For `n = 2` or `n = 3`, `i = 2` is already greater than $\\sqrt{n}$; without an explicit `if (n == 2 || n == 3) return 1;`, `n = 2` executes `2 % 2 == 0` and falsely reports `2` as \*\*not prime\*\*.

\* \*\*Why `i \* i <= n` can overflow:\*\* If `n` is near `ULONG\_MAX` (e.g., `4,294,967,291` on a 32-bit `unsigned long`), when `i = 65536`, `i \* i` wraps around modulo $2^{32}$ to `0`, creating an infinite loop. Writing `i <= n / i` prevents overflow completely.



\## 3. Alternative Concept and Complexity Analysis (Sieve of Eratosthenes)

\* \*\*Sieve Approach:\*\* Precomputes primality for all integers up to $N$ in a boolean array `is\_composite\[N + 1]`.

\* \*\*Time Complexity:\*\* \*\*$O(N \\log \\log N)$\*\* one-time preprocessing, followed by \*\*$O(1)$\*\* per ticket query (versus \*\*$O(\\sqrt{n})$\*\* per query for trial division).

\* \*\*Space Complexity:\*\* \*\*$O(N)$\*\* memory (`1 MB` for $N = 1,000,003$ bytes), whereas trial division uses \*\*$O(1)$\*\* space. For verifying a few tickets, trial division is better; for verifying hundreds of thousands of tickets, the Sieve is far faster.



