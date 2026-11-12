\# Q4 – `else–if` Ladder or `switch`?



\## 1. Boundary Analysis \& Fall-Through Behaviour

\* \*\*Boundary Values (`100, 90, 89, 0, -1, 101`):\*\* Both versions handle all valid boundaries identically once `-1` and `101` are rejected upfront (`if (marks < 0 || marks > 100)`). Without that upfront check, `-5 / 10 == 0` in C would fall into `default:` and wrongly return `'F'` instead of `'?'`!

\* \*\*Effect of Missing `break` / `return`:\*\* If `return 'A';` (or `break`) is removed from `case 8:`, execution \*\*falls through\*\* into `case 7:`, causing marks `80–89` (such as `83`) to wrongly receive grade `'B'`.

\* \*\*Why `switch` Cannot Test Ranges like `75–84`:\*\* Standard C `switch` labels require compile-time integer constant expressions (`case 75:` ... `case 84:`), and integer division `marks / 10` only groups multiples of 10 (`70–79`, `80–89`). Thus, an \*\*`else–if` ladder\*\* is far easier to modify when grade cutoffs are non-multiples of 10 (e.g., `75` or `85`).



\## 2. Design Decision for Scholarship Rule

\* \*\*Choice:\*\* \*\*Nested `if` statements\*\* (checking grade eligibility first, then income thresholds).

\* \*\*Defence:\*\* Income bands (`<= 250000`, `<= 600000`) are continuous inequality ranges rather than discrete integers, making `switch` unsuitable. Nested `if` cleanly separates grade qualification from financial need without duplicating income checks.



\## 3. Alternative Concept and Complexity Analysis (Lookup Table)

Using `char grades\[11] = {'F','F','F','F','F','D','C','B','A','S','S'};` indexed by `grades\[marks / 10]`:

\* \*\*Time Complexity:\*\* \*\*$O(1)$\*\* (a single division and array offset lookup) compared to up to \*\*$k = 6$\*\* sequential comparisons ($O(k)$) in an `else–if` ladder.

\* \*\*Space Complexity:\*\* \*\*$O(1)$\*\* fixed table of \*\*11 bytes\*\* (`sizeof(grades) == 11`), negligible memory for maximum speed when boundaries align with multiples of 10.



