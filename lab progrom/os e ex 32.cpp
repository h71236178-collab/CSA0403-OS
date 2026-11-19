
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

int main()
{
    int frames[MAX_FRAMES];
    int usageHistory[MAX_FRAMES];

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;
        usageHistory[i] = 0;
    }

    int pageFaults = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    printf("Reference String: ");

    for (int i = 0; i < n; i++)
        printf("%d ", referenceString[i]);

    printf("\n\nPage Replacement Order:\n");

    for (int i = 0; i < n; i++)
    {
        int page = referenceString[i];
        int pageFound = 0;

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == page)
            {
                pageFound = 1;
                usageHistory[j] = 0;

                for (int k = 0; k < MAX_FRAMES; k++)
                {
                    if (k != j && frames[k] != -1)
                        usageHistory[k]++;
                }

                break;
            }
        }

        if (pageFound)
        {
            printf("Page %d (Hit) -> ", page);
            printFrames(frames, MAX_FRAMES);
            continue;
        }

        printf("Page %d (Fault) -> ", page);

        int lruPage = -1;

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == -1)
            {
                lruPage = j;
                break;
            }

            if (lruPage == -1 ||
                usageHistory[j] > usageHistory[lruPage])
            {
                lruPage = j;
            }
        }

        int replacedPage = frames[lruPage];
        frames[lruPage] = page;
        usageHistory[lruPage] = 0;

        if (replacedPage != -1)
            printf("Replace %d with %d: ", replacedPage, page);
        else
            printf("Load into an empty frame: ");

        printFrames(frames, MAX_FRAMES);
        pageFaults++;

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (j != lruPage && frames[j] != -1)
                usageHistory[j]++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
