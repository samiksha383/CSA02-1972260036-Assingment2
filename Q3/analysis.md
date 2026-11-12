\# Q3 – Engineer a Device-Status Register with Bitwise Operators



\## 1. Pre-Execution Trace of `main()`

1\. `unsigned char reg = 0;` $\\rightarrow$ `00000000` (`0`)

2\. `reg = switch\_on(reg, LIGHT);` (sets bit 0) $\\rightarrow$ `00000001` (`1`)

3\. `reg = switch\_on(reg, AC);` (sets bit 2) $\\rightarrow$ `00000101` (`5`) $\\rightarrow$ \*\*First `show(reg)` prints `00000101`\*\*.

4\. `reg = toggle(reg, FAN);` (flips bit 1) $\\rightarrow$ `00000111` (`7`)

5\. `reg = switch\_off(reg, LIGHT);` (clears bit 0) $\\rightarrow$ `00000110` (`6`) $\\rightarrow$ \*\*Second `show(reg)` prints `00000110`\*\*.

6\. `is\_on(reg, AC)` returns `1` (`ON`), `is\_on(reg, PUMP)` returns `0` (`OFF`).



\## 2. Inquiry: Operator Precedence \& Signedness

\* \*\*`reg \& 1 << dev` vs. `(reg \& 1) << dev`:\*\* Because `<<` has higher precedence than `\&`, `reg \& 1 << dev` parses as `reg \& (1 << dev)` (testing bit `dev`), whereas `(reg \& 1) << dev` masks bit 0 first and then shifts it left, completely ignoring bit `dev`!

\* \*\*Signed `char` with Bit 7 Set:\*\* On two's-complement systems, bit 7 is the sign bit (`-128`). Right-shifting (`reg >> bit`) a negative `signed char` performs an \*\*arithmetic shift\*\* (sign-extending with `1`s instead of `0`s), and shifting `1 << 7` into a signed char causes signed overflow. Always use `unsigned char` and `1u`.



\## 3. Alternative Concept and Complexity Analysis (`char state\[8]` vs. Bitmask)



| Operation / Metric | Bitwise Register (`unsigned char`) | Boolean Array (`char state\[8]`) |

| :--- | :--- | :--- |

| \*\*On / Off / Toggle / Test\*\* | \*\*$O(1)$\*\* (Single bitwise instruction) | \*\*$O(1)$\*\* (Single array index lookup) |

| \*\*Space for 1,000,000 Homes\*\* | \*\*1 MB\*\* (`1 byte × 1,000,000`) | \*\*8 MB\*\* (`8 bytes × 1,000,000` — \*\*8× memory\*\*) |

| \*\*Count Devices ON\*\* | \*\*$O(b)$\*\* where $b=8$ bits (or $O(1)$ via Kernighan's `reg \&= reg - 1` / `\_\_builtin\_popcount`) | \*\*$O(d)$\*\* where $d=8$ array elements (requires 8 separate memory reads) |



