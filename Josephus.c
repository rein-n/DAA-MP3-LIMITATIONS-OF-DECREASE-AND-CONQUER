#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Standard Josephus with fixed k 
int josephus_fixed_k(int n, int k) {
    int people[MAX];
    for (int i = 0; i < n; i++) {
        people[i] = 1;  // 1 means alive
    }

    int alive = n;
    int index = 0;
    int round = 1;

    printf("\n===| Standard Josephus (Fixed k = %d) |===\n", k);
    while (alive > 1) {
        int count = 0;
        while (count < k) {
            if (people[index] == 1) {
                count++;
            }
            if (count == k) break;
            index = (index + 1) % n;
        }

        people[index] = 0;
        alive--;
        printf("ROUND %d: Eliminated person at position %d\n", round, index + 1);

        do {
            index = (index + 1) % n;
        } while (people[index] == 0);

        round++;
    }

    for (int i = 0; i < n; i++) {
        if (people[i] == 1) {
            return i + 1;
        }
    }

    return -1;
}

// Dynamic Josephus with alternating k 
int josephus_dynamic_k(int n, int k1, int k2) {
    int people[MAX];
    for (int i = 0; i < n; i++) {
        people[i] = 1;
    }

    int alive = n;
    int index = 0;
    int round = 1;

    printf("\n===| Dynamic Josephus (k alternates %d and %d) |===\n", k1, k2);
    while (alive > 1) {
        int k = (round % 2 == 0) ? k2 : k1;

        int count = 0;
        while (count < k) {
            if (people[index] == 1) {
                count++;
            }
            if (count == k) break;
            index = (index + 1) % n;
        }

        people[index] = 0;
        alive--;
        printf("ROUND %d: Eliminated person at position %d (k = %d)\n", round, index + 1, k);

        do {
            index = (index + 1) % n;
        } while (people[index] == 0);

        round++;
    }

    for (int i = 0; i < n; i++) {
        if (people[i] == 1) {
            return i + 1;
        }
    }

    return -1;
}

// Main function 
int main() {
    int n, fixed_k, k1, k2;

    printf("Enter number of people: ");
    scanf("%d", &n);
    if (n <= 1 || n > MAX) {
        printf("Invalid number. Please enter a number between 2 and %d.\n", MAX);
        return 1;
    }

    printf("\n=== FIXED Josephus ===\n");
    printf("Enter value for fixed k: ");
    scanf("%d", &fixed_k);

    printf("\n=== DYNAMIC Josephus ===\n");
    printf("Enter value for k1 (used in ODD rounds): ");
    scanf("%d", &k1);
    printf("Enter value for k2 (used in EVEN rounds): ");
    scanf("%d", &k2);

    int winner_fixed = josephus_fixed_k(n, fixed_k);
    printf("\n>> Winner using fixed k = %d is Person %d\n", fixed_k, winner_fixed);

    int winner_dynamic = josephus_dynamic_k(n, k1, k2);
    printf("\n>> Winner using dynamic k (%d/%d) is Person %d\n", k1, k2, winner_dynamic);

    return 0;
}