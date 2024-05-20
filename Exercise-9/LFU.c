#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Struct to represent a page
typedef struct {
    int pageNumber;
    int frequency;
    int lastUsed;
} Page;

// Function to find page faults using LFU algorithm
int pageFaults(int n, int c, int pages[])
{
    // Initialize count to 0
    int count = 0;

    // Create an array of Page structs to represent memory
    Page* memory = (Page*)malloc(c * sizeof(Page));

    int i;
    for (i = 0; i < c; i++) {
        // Set initial values for each page in memory
        memory[i].pageNumber = -1;  // -1 represents an empty page
        memory[i].frequency = 0;
        memory[i].lastUsed = -1;  // -1 represents not yet used
    }

    for (i = 0; i < n; i++) {
        // Find if the page is present in memory
        int j;
        bool found = false;
        for (j = 0; j < c; j++) {
            if (memory[j].pageNumber == pages[i]) {
                found = true;
                break;
            }
        }

        // If the page is not present in memory
        if (!found) {
            int leastFrequent = 0;

            // Find the least frequently used page in memory
            for (j = 1; j < c; j++) {
                if (memory[j].frequency < memory[leastFrequent].frequency ||
                    (memory[j].frequency == memory[leastFrequent].frequency &&
                     memory[j].lastUsed < memory[leastFrequent].lastUsed)) {
                    leastFrequent = j;
                }
            }

            // Replace the least frequently used page with the new page
            memory[leastFrequent].pageNumber = pages[i];
            memory[leastFrequent].frequency = 1;
            memory[leastFrequent].lastUsed = i;

            // Increment the count
            count++;
        } else {
            // If the page is already present in memory, update its frequency and last used index
            memory[j].frequency++;
            memory[j].lastUsed = i;
        }
    }

    // Free the allocated memory
    free(memory);

    // Return the total page faults
    return count;
}

// Driver program to test pageFaults function
int main()
{
    int pages[] = {1, 2, 3, 4, 2, 1, 5};
    int n = 7, c = 3;

    printf("Page Faults = %d\n", pageFaults(n, c, pages));
    printf("Page Hits = %d\n", n - pageFaults(n, c, pages));

    return 0;
}
