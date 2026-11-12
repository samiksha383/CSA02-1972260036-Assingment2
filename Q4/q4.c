#include <stdio.h>

/* Version 1: switch on marks / 10 */
char grade_switch(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    switch (marks / 10) {
        case 10:
        case 9:  return 'S';
        case 8:  return 'A';
        case 7:  return 'B';
        case 6:  return 'C';
        case 5:  return 'D';
        default: return 'F';
    }
}

/* Version 2: else-if ladder */
char grade_ifelse(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    else if (marks >= 90) return 'S';
    else if (marks >= 80) return 'A';
    else if (marks >= 70) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 50) return 'D';
    else return 'F';
}

/* Scholarship classifier: nested if on grade + annual family income (Rs) */
const char* scholarship(char grd, long income)
{
    if (grd == '?' || grd == 'F' || grd == 'D') {
        return "None";
    }
    if (grd == 'S' || grd == 'A') {
        if (income <= 250000L) return "Full Tuition Waiver (100%)";
        if (income <= 600000L) return "Half Tuition Waiver (50%)";
        return "Merit Certificate Only";
    }
    /* Grades B and C */
    if (income <= 250000L) return "Need-Based Grant (25%)";
    return "None";
}

int main(void)
{
    /* Prompt expected output test */
    int marks[] = {100, 95, 83, 50, 49, -5};
    printf("Prompt Test: ");
    for (int i = 0; i < 6; i++) printf("%d:%c ", marks[i], grade_switch(marks[i]));
    printf("\n\n");

    /* Full boundary-exposing test set */
    int boundary_tests[] = {-1, 0, 49, 50, 59, 60, 69, 70, 79, 80, 89, 90, 99, 100, 101};
    int n = sizeof(boundary_tests) / sizeof(boundary_tests[0]);
    printf("=== Boundary Comparison (switch vs else-if) ===\n");
    for (int i = 0; i < n; i++) {
        int m = boundary_tests[i];
        printf("Marks %3d -> switch: %c | else-if: %c\n",
               m, grade_switch(m), grade_ifelse(m));
    }

    printf("\n=== Scholarship Decision Examples ===\n");
    printf("Grade S, Income Rs 2,00,000 -> %s\n", scholarship('S', 200000L));
    printf("Grade A, Income Rs 4,50,000 -> %s\n", scholarship('A', 450000L));
    printf("Grade B, Income Rs 1,80,000 -> %s\n", scholarship('B', 180000L));
    return 0;
}
