#include <stdio.h>
#include <stdlib.h>

// Function to find page faults using FIFO
int pageFaults(int pages[], int n, int capacity)
{
    // To represent set of current pages. We use
    // an array to simulate the unordered_set
    int *s = (int *)malloc(capacity * sizeof(int));
    for (int i = 0; i < capacity; i++) {
        s[i] = -1;  // Initialize all elements as invalid
    }

    // To store the pages in FIFO manner, we use two pointers
    int front = 0;
    int rear = 0;

    // Start from initial page
    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        // Check if the set can hold more pages
        if (rear < capacity)
        {
            int found = 0;
            // Check if the page is already in the set
            for (int j = 0; j < capacity; j++)
            {
                if (s[j] == pages[i])
                {
                    found = 1;
                    break;
                }
            }

            // If page is not present, insert it into the set
            if (found == 0)
            {
                s[rear] = pages[i];
                rear++;
                page_faults++;
            }
        }
        // If the set is full, replace the page using FIFO
        else
        {
            int found = 0;
            // Check if the page is already in the set
            for (int j = 0; j < capacity; j++)
            {
                if (s[j] == pages[i])
                {
                    found = 1;
                    break;
                }
            }

            // If page is not present, replace the first page
            // in the set with the current page
            if (found == 0)
            {
                s[front] = pages[i];
                front = (front + 1) % capacity;
                rear = (rear + 1) % capacity;
                page_faults++;
            }
        }
    }

    free(s);  // Free dynamically allocated memory
    return page_faults;
}

// Driver code
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;
    printf("Page Faults: %d\n", pageFaults(pages, n, capacity));
    return 0;
}
