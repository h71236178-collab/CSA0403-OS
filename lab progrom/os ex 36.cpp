
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a block
struct Block
{
    char data[256];
    struct Block *next;
};

int main()
{
    struct Block *firstBlock = NULL;
    struct Block *lastBlock = NULL;
    int blockCount = 0;
    int blockNumber;
    char data[256];
    char choice;

    printf("Linked Allocation Simulation\n");

    while (1)
    {
        printf("\nEnter 'W' to write, 'R' to read, or 'Q' to quit: ");
        scanf(" %c", &choice);

        if (choice == 'Q' || choice == 'q')
            break;

        if (choice == 'W' || choice == 'w')
        {
            printf("Enter data for the block: ");
            scanf(" %255[^\n]", data);

            struct Block *newBlock =
                (struct Block *)malloc(sizeof(struct Block));

            if (newBlock == NULL)
            {
                printf("Memory allocation failed!\n");
                break;
            }

            strcpy(newBlock->data, data);
            newBlock->next = NULL;

            if (blockCount == 0)
            {
                firstBlock = newBlock;
                lastBlock = newBlock;
            }
            else
            {
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }

            blockCount++;
            printf("Block %d added successfully.\n", blockCount);
        }
        else if (choice == 'R' || choice == 'r')
        {
            if (blockCount == 0)
            {
                printf("No blocks available to read.\n");
                continue;
            }

            printf("Enter block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount)
            {
                printf("Invalid block number. Valid range is 1-%d.\n",
                       blockCount);
            }
            else
            {
                struct Block *currentBlock = firstBlock;

                for (int i = 1; i < blockNumber; i++)
                    currentBlock = currentBlock->next;

                printf("Block %d Data: %s\n",
                       blockNumber, currentBlock->data);
            }
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    // Free allocated memory
    struct Block *currentBlock = firstBlock;

    while (currentBlock != NULL)
    {
        struct Block *nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    printf("Program ended successfully.\n");

    return 0;
}
