\# Q2 – When Does Short-Circuit Evaluation Matter?



\## 1. Short-Circuit Rules \& Bitwise Difference

\* \*\*`\&\&` (Logical AND):\*\* If the left operand is `0` (false), the right operand is \*\*not evaluated\*\* because the result is guaranteed to be `0`.

\* \*\*`||` (Logical OR):\*\* If the left operand is non-zero (true), the right operand is \*\*not evaluated\*\* because the result is guaranteed to be `1`.

\* \*\*`\&` and `|` (Bitwise AND / OR):\*\* Evaluate \*\*both\*\* operands unconditionally every single time, and operate bit-by-bit rather than boolean truth values.



\## 2. Experimental Call Counts (1,000 Passengers)

\* \*\*Order 1 (`(is\_senior \&\& valid\_class) || verify\_disability\_card()`):\*\* Calls slow function \*\*700 times\*\* (skips the 300 passengers who already qualify via senior + class).

\* \*\*Order 2 (`verify\_disability\_card() || (is\_senior \&\& valid\_class)`):\*\* Calls slow function \*\*1,000 times\*\* (every passenger hits the slow server first).

\* \*\*Order 3 (Bitwise `\&` and `|`):\*\* Calls slow function \*\*1,000 times\*\* (short-circuiting disabled).



\## 3. Ordering Guidelines \& Changed Condition (Audit Log)

\* \*\*When to order carefully:\*\* For `\&\&`, place the \*\*cheapest and most-likely-false\*\* condition first. For `||`, place the \*\*cheapest and most-likely-true\*\* condition first. Order is irrelevant only when all operands are pure, side-effect-free variables with equal $O(1)$ cost.

\* \*\*Changed Condition (Audit Log Side Effect):\*\* Because `verify\_disability\_card()` now writes to a mandatory audit log, relying on short-circuiting causes \*\*incomplete audit logs\*\* (skipping 300 passengers). If every passenger must be logged, the verification function must be called explicitly before the `if` condition rather than hidden behind `||`.



\## 4. Alternative Concept and Complexity Analysis ($n$ Passengers)

\* \*\*Nested `if` Statements:\*\* Behave identically to short-circuit `\&\&` / `||`, making \*\*$O(n)$\*\* calls with the exact same reduced count ($700$ calls in our test).

\* \*\*Bitwise `\&` and `|`:\*\* Always executes \*\*$n$\*\* calls ($1,000$ calls), losing all best-case $O(1)$-per-passenger early-exit savings.



