#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resources

    int allocation[5][3] = {
        {0, 1, 0}, // P0 // Allocation Matrix
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    int max[5][3] = {
        {7, 5, 3}, // P0 // MAX Matrix
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    int available[3] = {3, 3, 2}; // Available Resources

    int finish[n], safeSequence[n], index = 0;

    for (k = 0; k < n; k++) {
        finish[k] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int isSafe = 0;

    for (k = 0; k < n; k++) {           // iterate through each process in the system.
        for (i = 0; i < n; i++) {       //to find a process that is not finished (finish[i] == 0) and check if its resource needs can be satisfied with the available resources.
            if (finish[i] == 0) {
                int isPossible = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        isPossible = 0;
                        break;
                    }
                }
                if (isPossible) {
                    safeSequence[index++] = i;
                    for (int y = 0; y < m; y++) {
                        available[y] += allocation[i][y];
                    }
                    finish[i] = 1;
                    isSafe = 1;
                }
            }
        }
    }

    if (!isSafe) {
        printf("The system is not safe.\n");
    } else {
        printf("Following is the SAFE Sequence:\n");
        for (i = 0; i < n - 1; i++) {
            printf(" P%d ->", safeSequence[i]);
        }
        printf(" P%d\n", safeSequence[n - 1]);
    }

    return 0;
}
