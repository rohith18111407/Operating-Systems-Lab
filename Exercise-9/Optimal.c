#include <stdio.h>
#include <stdbool.h>

// Function to check whether a page exists
// in a frame or not
bool search(int key, int fr[], int fn)
{
    for (int i = 0; i < fn; i++)
    {
        if (fr[i] == key)
            return true;
    }
    return false;
}

// Function to find the frame that will not be used
// recently in the future after the given index in pg[0..pn-1]
int predict(int pg[], int fr[], int pn, int fn, int index)
{
    // Store the index of pages which are going
    // to be used recently in the future
    int res = -1, farthest = index;
    for (int i = 0; i < fn; i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in the future,
        // return it.
        if (j == pn)
            return i;
    }

    // If all of the frames were not in the future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    // Create an array for the given number of
    // frames and initialize it as empty.
    int fr[fn];

    // Initialize all frames as empty (-1)
    for (int i = 0; i < fn; i++)
    {
        fr[i] = -1;
    }

    // Traverse through the page reference array
    // and check for hits and misses.
    int hit = 0;
    for (int i = 0; i < pn; i++)
    {
        // Page found in a frame: HIT
        if (search(pg[i], fr, fn))
        {
            hit++;
            continue;
        }

        // Page not found in a frame: MISS

        // If there is space available in frames.
        int j;
        for (j = 0; j < fn; j++)
        {
            if (fr[j] == -1)
            {
                fr[j] = pg[i];
                break;
            }
        }

        // If all frames are occupied, find the page to be replaced.
        if (j == fn)
        {
            int k = predict(pg, fr, pn, fn, i + 1);
            fr[k] = pg[i];
        }
    }

    printf("No. of hits = %d\n", hit);
    printf("No. of misses = %d\n", pn - hit);
}

// Driver Function
int main()
{
    int pg[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
    int pn = sizeof(pg) / sizeof(pg[0]);
    int fn = 4;
    optimalPage(pg, pn, fn);
    return 0;
}
