#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Function to find page faults using indexes
int findPageFaults(int pages[], int pageCount, int capacity)
{
    // To represent a set of current pages,
    // we use an array to simulate an unordered_set
    int pageSet[capacity];

    // To store the least recently used indexes of pages
    int recentIndexes[capacity];

    // Start from the initial page
    int pageFaultCount = 0;
    for (int i = 0; i < pageCount; i++)
    {
        // Check if the set can hold more pages
        if (i < capacity)
        {
            // Insert the page into the set if not already present,
            // which represents a page fault
            bool found = false;
            for (int j = 0; j < i; j++)
            {
                if (pageSet[j] == pages[i])
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                pageSet[i] = pages[i];
                pageFaultCount++;
            }

            // Store the recently used index of each page
            recentIndexes[pages[i]] = i;
        }
        // If the set is full, we need to perform LRU
        // i.e., remove the least recently used page
        // and insert the current page
        else
        {
            // Check if the current page is not already present in the set
            bool found = false;
            for (int j = 0; j < capacity; j++)
            {
                if (pageSet[j] == pages[i])
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                // Find the least recently used page in the set
                int leastRecentlyUsed = INT_MAX, value;
                for (int j = 0; j < capacity; j++)
                {
                    if (recentIndexes[pageSet[j]] < leastRecentlyUsed)
                    {
                        leastRecentlyUsed = recentIndexes[pageSet[j]];
                        value = pageSet[j];
                    }
                }

                // Remove the least recently used page
                for (int j = 0; j < capacity; j++)
                {
                    if (pageSet[j] == value)
                    {
                        pageSet[j] = pages[i];
                        break;
                    }
                }

                // Increment page fault count
                pageFaultCount++;
            }

            // Update the current page index
            recentIndexes[pages[i]] = i;
        }
    }

    return pageFaultCount;
}

// Driver code
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int pageCount = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    printf("Page Faults: %d\n", findPageFaults(pages, pageCount, capacity));
    return 0;
}
